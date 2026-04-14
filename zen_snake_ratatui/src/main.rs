use std::{
    collections::{HashSet, VecDeque},
    io,
    time::{Duration, Instant},
};

use crossterm::{
    event::{self, Event, KeyCode, KeyEventKind},
    execute,
    terminal::{disable_raw_mode, enable_raw_mode, EnterAlternateScreen, LeaveAlternateScreen},
};
use rand::{prelude::IndexedRandom, rng};
use ratatui::{
    backend::CrosstermBackend,
    layout::Rect,
    style::{Color, Modifier, Style},
    text::{Line, Span},
    widgets::{Block, Borders, Paragraph},
    Terminal,
};

const BASE_TICK: Duration = Duration::from_millis(120);
const MIN_TICK: Duration = Duration::from_millis(85);
const GHOST_TTL: Duration = Duration::from_secs(5);
const RIPPLE_PERIOD: Duration = Duration::from_secs(2);
const TUNNEL_DIM: Duration = Duration::from_millis(400);
const FLASH_DURATION: Duration = Duration::from_millis(200);

#[derive(Clone, Copy, Debug, Eq, PartialEq, Hash)]
struct Pos {
    x: i16,
    y: i16,
}

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
enum Dir {
    Up,
    Down,
    Left,
    Right,
}

impl Dir {
    fn opposite(self, other: Dir) -> bool {
        matches!(
            (self, other),
            (Dir::Up, Dir::Down)
                | (Dir::Down, Dir::Up)
                | (Dir::Left, Dir::Right)
                | (Dir::Right, Dir::Left)
        )
    }

    fn step(self, pos: Pos) -> Pos {
        match self {
            Dir::Up => Pos { x: pos.x, y: pos.y - 1 },
            Dir::Down => Pos { x: pos.x, y: pos.y + 1 },
            Dir::Left => Pos { x: pos.x - 1, y: pos.y },
            Dir::Right => Pos { x: pos.x + 1, y: pos.y },
        }
    }
}

#[derive(Clone, Copy)]
enum FoodKind {
    RippleSeed,
    PrismPetal,
}

#[derive(Clone, Copy)]
struct Food {
    pos: Pos,
    kind: FoodKind,
    next_ripple: Instant,
}

#[derive(Clone, Copy)]
enum ParticleKind {
    Ghost,
    Spark,
    Ripple,
}

#[derive(Clone, Copy)]
struct Particle {
    pos: Pos,
    glyph: char,
    kind: ParticleKind,
    expires: Instant,
}

#[derive(Clone, Copy)]
struct Theme {
    bg: Color,
    fg: Color,
    accent: Color,
}

const THEMES: [Theme; 4] = [
    Theme { bg: Color::Black, fg: Color::Green, accent: Color::LightGreen },
    Theme { bg: Color::Rgb(6, 18, 28), fg: Color::Cyan, accent: Color::LightCyan },
    Theme { bg: Color::Rgb(25, 15, 35), fg: Color::Magenta, accent: Color::LightMagenta },
    Theme { bg: Color::Black, fg: Color::White, accent: Color::Gray },
];

struct Game {
    snake: VecDeque<Pos>,
    dir: Dir,
    pending_growth: usize,
    tunnel_dim_until: Option<Instant>,
    flash_until: Option<Instant>,
    foods: Vec<Food>,
    particles: Vec<Particle>,
    dir_queue: VecDeque<Dir>,
    paint_cells: HashSet<Pos>,
    theme_index: usize,
    theme_brightness_steps: u8,
    agitation: f32,
    turn_timestamps: VecDeque<Instant>,
    terminal_grid: (i16, i16),
}

impl Game {
    fn new(grid_w: i16, grid_h: i16) -> Self {
        let mut snake = VecDeque::new();
        snake.push_back(Pos { x: grid_w / 2, y: grid_h / 2 });
        snake.push_back(Pos { x: grid_w / 2 - 1, y: grid_h / 2 });
        snake.push_back(Pos { x: grid_w / 2 - 2, y: grid_h / 2 });

        let mut game = Self {
            snake,
            dir: Dir::Right,
            pending_growth: 0,
            tunnel_dim_until: None,
            flash_until: None,
            foods: Vec::new(),
            particles: Vec::new(),
            dir_queue: VecDeque::new(),
            paint_cells: HashSet::new(),
            theme_index: 0,
            theme_brightness_steps: 0,
            agitation: 0.0,
            turn_timestamps: VecDeque::new(),
            terminal_grid: (grid_w, grid_h),
        };
        game.spawn_foods();
        game
    }

    fn spawn_foods(&mut self) {
        while self.foods.len() < 3 {
            if let Some(pos) = self.random_empty_cell() {
                let kind = match self.foods.len() {
                    0 => FoodKind::RippleSeed,
                    _ => FoodKind::PrismPetal,
                };
                self.foods.push(Food {
                    pos,
                    kind,
                    next_ripple: Instant::now() + RIPPLE_PERIOD,
                });
            } else {
                break;
            }
        }
    }

    fn random_empty_cell(&self) -> Option<Pos> {
        let (w, h) = self.terminal_grid;
        let mut cells = Vec::new();
        for y in 0..h {
            for x in 0..w {
                let p = Pos { x, y };
                if !self.snake.contains(&p) && !self.foods.iter().any(|f| f.pos == p) {
                    cells.push(p);
                }
            }
        }
        let mut rng = rng();
        cells.choose(&mut rng).copied()
    }

    fn push_dir(&mut self, dir: Dir) {
        if self.dir_queue.back().is_some_and(|d| *d == dir) {
            return;
        }
        self.dir_queue.push_back(dir);
    }

    fn update(&mut self, now: Instant) {
        while self.turn_timestamps.front().is_some_and(|t| now.duration_since(*t) > Duration::from_secs(4)) {
            self.turn_timestamps.pop_front();
        }

        if let Some(next_dir) = self.dir_queue.pop_front()
            && !self.dir.opposite(next_dir)
        {
            self.dir = next_dir;
            self.turn_timestamps.push_back(now);
            if let Some(head) = self.snake.front().copied() {
                self.spawn_ghost(head, now + GHOST_TTL);
            }
        }

        self.agitation = (self.turn_timestamps.len() as f32 / 4.0).min(2.5);
        let old_head = self.snake.front().copied().expect("snake has head");
        let mut new_head = self.dir.step(old_head);

        let (w, h) = self.terminal_grid;
        let wrapped = new_head.x < 0 || new_head.y < 0 || new_head.x >= w || new_head.y >= h;
        if wrapped {
            self.tunnel_dim_until = Some(now + TUNNEL_DIM);
            new_head.x = (new_head.x + w) % w;
            new_head.y = (new_head.y + h) % h;
        }

        let collision = self
            .snake
            .iter()
            .skip(1)
            .any(|segment| *segment == new_head);

        if collision {
            self.full_circle_reset(now);
            return;
        }

        self.snake.push_front(new_head);
        self.paint_cells.insert(new_head);

        let near_miss = self
            .snake
            .iter()
            .skip(1)
            .any(|p| (p.x - new_head.x).abs() <= 1 && (p.y - new_head.y).abs() <= 1);
        if near_miss {
            self.particles.push(Particle {
                pos: new_head,
                glyph: '░',
                kind: ParticleKind::Spark,
                expires: now + Duration::from_millis(250),
            });
        }

        if self.pending_growth > 0 {
            self.pending_growth -= 1;
        } else {
            self.snake.pop_back();
        }

        self.consume_food(now);
        self.food_ripples(now);
        self.particles.retain(|p| p.expires > now);
        self.spawn_foods();
    }

    fn full_circle_reset(&mut self, now: Instant) {
        for segment in &self.snake {
            self.particles.push(Particle {
                pos: *segment,
                glyph: '░',
                kind: ParticleKind::Ripple,
                expires: now + Duration::from_millis(500),
            });
        }
        let (w, h) = self.terminal_grid;
        self.snake.clear();
        self.snake.push_back(Pos { x: w / 2, y: h / 2 });
        self.snake.push_back(Pos { x: w / 2 - 1, y: h / 2 });
        self.snake.push_back(Pos { x: w / 2 - 2, y: h / 2 });
        self.pending_growth = 0;
        self.dir = Dir::Right;
        self.theme_brightness_steps = self.theme_brightness_steps.saturating_add(1);
    }

    fn consume_food(&mut self, now: Instant) {
        let head = self.snake.front().copied().expect("snake has head");
        if let Some(idx) = self.foods.iter().position(|f| f.pos == head) {
            let food = self.foods.remove(idx);
            self.pending_growth += 3;
            match food.kind {
                FoodKind::RippleSeed => {
                    self.flash_until = Some(now + FLASH_DURATION);
                    for p in &mut self.particles {
                        p.pos = head;
                        p.expires = now + Duration::from_millis(300);
                    }
                }
                FoodKind::PrismPetal => {
                    self.theme_index = (self.theme_index + 1) % THEMES.len();
                }
            }
        }
    }

    fn food_ripples(&mut self, now: Instant) {
        for food in &mut self.foods {
            if matches!(food.kind, FoodKind::RippleSeed) && now >= food.next_ripple {
                food.next_ripple = now + RIPPLE_PERIOD;
                for (dx, dy) in [(1, 0), (-1, 0), (0, 1), (0, -1)] {
                    self.particles.push(Particle {
                        pos: Pos {
                            x: food.pos.x + dx,
                            y: food.pos.y + dy,
                        },
                        glyph: '◦',
                        kind: ParticleKind::Ripple,
                        expires: now + Duration::from_millis(700),
                    });
                }
            }
        }
    }

    fn spawn_ghost(&mut self, pos: Pos, expires: Instant) {
        self.particles.push(Particle {
            pos,
            glyph: '░',
            kind: ParticleKind::Ghost,
            expires,
        });
    }

    fn current_tick(&self) -> Duration {
        let max = BASE_TICK.as_millis() as f32;
        let min = MIN_TICK.as_millis() as f32;
        let factor = (self.agitation / 2.5).clamp(0.0, 1.0);
        Duration::from_millis((max - (max - min) * factor) as u64)
    }

    fn coverage(&self) -> f32 {
        let total = (self.terminal_grid.0 * self.terminal_grid.1).max(1) as f32;
        self.paint_cells.len() as f32 / total
    }

    fn theme(&self) -> Theme {
        let mut t = THEMES[self.theme_index];
        if self.theme_brightness_steps > 0 {
            t.bg = brighten(t.bg, self.theme_brightness_steps);
        }
        t
    }
}

fn brighten(color: Color, steps: u8) -> Color {
    let delta = (steps as u16 * 4).min(40) as u8;
    match color {
        Color::Rgb(r, g, b) => Color::Rgb(r.saturating_add(delta), g.saturating_add(delta), b.saturating_add(delta)),
        Color::Black => Color::Rgb(delta, delta, delta),
        other => other,
    }
}

fn clamp_to_grid(p: Pos, w: i16, h: i16) -> Option<(usize, usize)> {
    if p.x >= 0 && p.y >= 0 && p.x < w && p.y < h {
        Some((p.x as usize * 2, p.y as usize))
    } else {
        None
    }
}

fn paint_double_cell(
    grid: &mut [Vec<char>],
    styles: &mut [Vec<Style>],
    pos: Pos,
    w: i16,
    h: i16,
    glyphs: [char; 2],
    style: Style,
) {
    if let Some((x, y)) = clamp_to_grid(pos, w, h) {
        for (offset, glyph) in glyphs.into_iter().enumerate() {
            if x + offset < grid[y].len() {
                grid[y][x + offset] = glyph;
                styles[y][x + offset] = style;
            }
        }
    }
}

fn draw(terminal: &mut Terminal<CrosstermBackend<io::Stdout>>, game: &Game) -> io::Result<()> {
    terminal.draw(|frame| {
        let area = frame.area();
        let play = Rect {
            x: 1,
            y: 1,
            width: area.width.saturating_sub(2),
            height: area.height.saturating_sub(3),
        };

        let theme = game.theme();
        let width = (play.width / 2) as i16;
        let height = play.height as i16;

        let mut grid = vec![vec![' '; play.width as usize]; height as usize];
        let mut styles = vec![vec![Style::default().fg(theme.fg).bg(theme.bg); play.width as usize]; height as usize];

        for p in &game.paint_cells {
            paint_double_cell(
                &mut grid,
                &mut styles,
                *p,
                width,
                height,
                ['.', '.'],
                Style::default().bg(theme.bg).fg(theme.fg),
            );
        }

        for particle in &game.particles {
            let color = match particle.kind {
                ParticleKind::Ghost => Color::DarkGray,
                ParticleKind::Spark => theme.accent,
                ParticleKind::Ripple => Color::Blue,
            };
            paint_double_cell(
                &mut grid,
                &mut styles,
                particle.pos,
                width,
                height,
                [particle.glyph, particle.glyph],
                Style::default().fg(color).bg(theme.bg),
            );
        }

        for food in &game.foods {
            let (glyph, color) = match food.kind {
                FoodKind::RippleSeed => ('◎', Color::LightBlue),
                FoodKind::PrismPetal => ('✶', Color::LightMagenta),
            };
            paint_double_cell(
                &mut grid,
                &mut styles,
                food.pos,
                width,
                height,
                [glyph, glyph],
                Style::default().fg(color).bg(theme.bg).add_modifier(Modifier::BOLD),
            );
        }

        let flash_all_solid = game.flash_until.is_some_and(|t| Instant::now() < t);
        for (i, seg) in game.snake.iter().enumerate() {
            let glyphs = if flash_all_solid {
                ['█', '█']
            } else if i <= 3 {
                ['█', '█']
            } else if i <= 8 {
                ['▓', '▓']
            } else if i <= 14 {
                ['▒', '▒']
            } else {
                ['░', '░']
            };

            let mut snake_color = theme.fg;
            if game.tunnel_dim_until.is_some_and(|t| Instant::now() < t) {
                snake_color = Color::DarkGray;
            }

            paint_double_cell(
                &mut grid,
                &mut styles,
                *seg,
                width,
                height,
                glyphs,
                Style::default().fg(snake_color).bg(theme.bg),
            );
        }

        let lines: Vec<Line> = grid
            .iter()
            .zip(styles.iter())
            .map(|(row, style_row)| {
                let spans: Vec<Span> = row
                    .iter()
                    .zip(style_row.iter())
                    .map(|(ch, style)| Span::styled(ch.to_string(), *style))
                    .collect();
                Line::from(spans)
            })
            .collect();

        let body = Paragraph::new(lines).block(Block::default().borders(Borders::ALL).title("Zen Snake"));
        frame.render_widget(body, play);

        let hud = format!(
            "coverage: {:>5.1}% | len: {} | tick: {}ms | q to quit",
            game.coverage() * 100.0,
            game.snake.len(),
            game.current_tick().as_millis()
        );
        let hud_widget = Paragraph::new(hud).style(Style::default().fg(theme.accent).bg(theme.bg));
        frame.render_widget(hud_widget, Rect::new(0, area.height.saturating_sub(1), area.width, 1));
    })?;
    Ok(())
}

fn main() -> io::Result<()> {
    enable_raw_mode()?;
    let mut stdout = io::stdout();
    execute!(stdout, EnterAlternateScreen)?;
    let backend = CrosstermBackend::new(stdout);
    let mut terminal = Terminal::new(backend)?;

    let size = terminal.size()?;
    let mut game = Game::new((size.width.saturating_sub(2) / 2) as i16, size.height.saturating_sub(4) as i16);

    let mut last_update = Instant::now();

    loop {
        while event::poll(Duration::from_millis(5))? {
            if let Event::Key(key) = event::read()?
                && key.kind == KeyEventKind::Press
            {
                match key.code {
                    KeyCode::Char('q') => {
                        disable_raw_mode()?;
                        execute!(terminal.backend_mut(), LeaveAlternateScreen)?;
                        terminal.show_cursor()?;
                        return Ok(());
                    }
                    KeyCode::Up | KeyCode::Char('w') => game.push_dir(Dir::Up),
                    KeyCode::Down | KeyCode::Char('s') => game.push_dir(Dir::Down),
                    KeyCode::Left | KeyCode::Char('a') => game.push_dir(Dir::Left),
                    KeyCode::Right | KeyCode::Char('d') => game.push_dir(Dir::Right),
                    _ => {}
                }
            }
        }

        let tick = game.current_tick();
        if last_update.elapsed() >= tick {
            game.update(Instant::now());
            last_update = Instant::now();
        }
        draw(&mut terminal, &game)?;
    }
}
