use std::{
    collections::{HashMap, HashSet, VecDeque},
    io,
    time::{Duration, Instant},
};

use crossterm::{
    event::{self, Event, KeyCode, KeyEventKind},
    execute,
    terminal::{EnterAlternateScreen, LeaveAlternateScreen, disable_raw_mode, enable_raw_mode},
};
use rand::{prelude::IndexedRandom, rng};
use ratatui::{
    Terminal,
    backend::CrosstermBackend,
    layout::Rect,
    style::{Color, Modifier, Style},
    text::{Line, Span},
    widgets::{Block, Borders, Clear, Paragraph},
};

const BASE_MOVE_INTERVAL: Duration = Duration::from_millis(100);
const SIMULATION_TICK: Duration = Duration::from_nanos(16_666_667);
const RENDER_TICK: Duration = SIMULATION_TICK;
const GHOST_TTL: Duration = Duration::from_secs(5);
const RIPPLE_PERIOD: Duration = Duration::from_secs(2);
const TUNNEL_DIM: Duration = Duration::from_millis(400);
const FLASH_DURATION: Duration = Duration::from_millis(200);
const STAR_DURATION: Duration = Duration::from_secs(6);
const STAR_SPEED_MULTIPLIER: f32 = 1.0 / 0.72;
const MAX_SNAKE_STEPS_PER_TICK: f32 = 1.0;
const STAR_RAINBOW_SPAN_DEGREES: f32 = 360.0;
const STAR_RAINBOW_SCROLL_SEGMENTS_PER_STEP: f32 = 2.0;
const GROW_WITH_TIME_PER_SEC: f32 = 2.0;
const FOOD_MAGNET_STEER_PER_SEC: f32 = 4.5;
const FOOD_MAGNET_MIN_SPEED_MULTIPLIER: f32 = 1.05;
const FOOD_MAGNET_EXP_FACTOR: f32 = 0.10;
const FOOD_MAGNET_MAX_SPEED_MULTIPLIER: f32 = 3.0;
const FOOD_TARGET_COUNT: usize = 6;
const MAX_FOODS_PER_KIND: usize = 3;

#[derive(Clone, Copy, Debug, Eq, PartialEq, Hash)]
struct Pos {
    x: i16,
    y: i16,
}

#[derive(Clone, Copy, Debug)]
struct Vec2 {
    x: f32,
    y: f32,
}

impl Vec2 {
    fn zero() -> Self {
        Self { x: 0.0, y: 0.0 }
    }

    fn from_pos(pos: Pos) -> Self {
        Self {
            x: pos.x as f32,
            y: pos.y as f32,
        }
    }

    fn length(self) -> f32 {
        (self.x * self.x + self.y * self.y).sqrt()
    }

    fn normalized(self) -> Self {
        let len = self.length();
        if len <= f32::EPSILON {
            Self::zero()
        } else {
            Self {
                x: self.x / len,
                y: self.y / len,
            }
        }
    }
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
            Dir::Up => Pos {
                x: pos.x,
                y: pos.y - 1,
            },
            Dir::Down => Pos {
                x: pos.x,
                y: pos.y + 1,
            },
            Dir::Left => Pos {
                x: pos.x - 1,
                y: pos.y,
            },
            Dir::Right => Pos {
                x: pos.x + 1,
                y: pos.y,
            },
        }
    }
}

#[derive(Clone, Copy, Eq, PartialEq)]
enum FoodKind {
    RippleSeed,
    PrismPetal,
    StarFruit,
}

#[derive(Clone, Copy)]
struct Food {
    position: Vec2,
    velocity: Vec2,
    kind: FoodKind,
    next_ripple: Instant,
}

impl Food {
    fn new(pos: Pos, kind: FoodKind, now: Instant) -> Self {
        Self {
            position: Vec2::from_pos(pos),
            velocity: Vec2::zero(),
            kind,
            next_ripple: now + RIPPLE_PERIOD,
        }
    }

    fn grid_pos(&self, grid: (i16, i16)) -> Pos {
        Pos {
            x: self.position.x.round().clamp(0.0, (grid.0 - 1) as f32) as i16,
            y: self.position.y.round().clamp(0.0, (grid.1 - 1) as f32) as i16,
        }
    }

    fn clamp_position(&mut self, grid: (i16, i16)) {
        self.position.x = self.position.x.clamp(0.0, (grid.0 - 1) as f32);
        self.position.y = self.position.y.clamp(0.0, (grid.1 - 1) as f32);
    }
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

#[derive(Clone, Copy)]
struct StarEffect {
    ends_at: Instant,
    speed_stacks: u8,
}

#[derive(Clone, Copy, Eq, PartialEq)]
enum AppMode {
    StartMenu,
    Playing,
    Paused,
}

#[derive(Clone, Copy, Eq, PartialEq)]
enum PauseMenuFocus {
    Resume,
    StarCheatToggle,
    StarCheatMinus,
    StarCheatPlus,
    GrowWithTimeToggle,
    FoodMagnetToggle,
}

impl PauseMenuFocus {
    fn previous(self) -> Self {
        match self {
            Self::Resume => Self::FoodMagnetToggle,
            Self::StarCheatToggle => Self::Resume,
            Self::StarCheatMinus => Self::StarCheatToggle,
            Self::StarCheatPlus => Self::StarCheatMinus,
            Self::GrowWithTimeToggle => Self::StarCheatPlus,
            Self::FoodMagnetToggle => Self::GrowWithTimeToggle,
        }
    }

    fn next(self) -> Self {
        match self {
            Self::Resume => Self::StarCheatToggle,
            Self::StarCheatToggle => Self::StarCheatMinus,
            Self::StarCheatMinus => Self::StarCheatPlus,
            Self::StarCheatPlus => Self::GrowWithTimeToggle,
            Self::GrowWithTimeToggle => Self::FoodMagnetToggle,
            Self::FoodMagnetToggle => Self::Resume,
        }
    }
}

const THEMES: [Theme; 4] = [
    Theme {
        bg: Color::Black,
        fg: Color::Green,
        accent: Color::LightGreen,
    },
    Theme {
        bg: Color::Rgb(6, 18, 28),
        fg: Color::Cyan,
        accent: Color::LightCyan,
    },
    Theme {
        bg: Color::Rgb(25, 15, 35),
        fg: Color::Magenta,
        accent: Color::LightMagenta,
    },
    Theme {
        bg: Color::Black,
        fg: Color::White,
        accent: Color::Gray,
    },
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
    star_effect: Option<StarEffect>,
    star_scroll_segments: f32,
    movement_progress: f32,
    last_simulation_at: Instant,
    star_cheat_enabled: bool,
    star_cheat_stacks: u8,
    grow_with_time_enabled: bool,
    grow_with_time_progress: f32,
    food_magnet_enabled: bool,
}

impl Game {
    fn new(grid_w: i16, grid_h: i16) -> Self {
        let mut snake = VecDeque::new();
        snake.push_back(Pos {
            x: grid_w / 2,
            y: grid_h / 2,
        });
        snake.push_back(Pos {
            x: grid_w / 2 - 1,
            y: grid_h / 2,
        });
        snake.push_back(Pos {
            x: grid_w / 2 - 2,
            y: grid_h / 2,
        });

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
            star_effect: None,
            star_scroll_segments: 0.0,
            movement_progress: 0.0,
            last_simulation_at: Instant::now(),
            star_cheat_enabled: false,
            star_cheat_stacks: 1,
            grow_with_time_enabled: false,
            grow_with_time_progress: 0.0,
            food_magnet_enabled: false,
        };
        game.spawn_foods();
        game
    }

    fn resize(&mut self, grid_w: i16, grid_h: i16) {
        let new_grid = (grid_w.max(1), grid_h.max(1));
        if self.terminal_grid == new_grid {
            return;
        }

        let old_grid = self.terminal_grid;
        self.terminal_grid = new_grid;

        let wrap = |pos: Pos, (w, h): (i16, i16)| Pos {
            x: pos.x.rem_euclid(w),
            y: pos.y.rem_euclid(h),
        };

        self.snake = self
            .snake
            .iter()
            .copied()
            .map(|pos| wrap(pos, new_grid))
            .collect();

        self.paint_cells = self
            .paint_cells
            .iter()
            .copied()
            .map(|pos| wrap(pos, new_grid))
            .collect();

        self.particles = self
            .particles
            .iter()
            .copied()
            .map(|mut particle| {
                particle.pos = wrap(particle.pos, new_grid);
                particle
            })
            .collect();

        let mut occupied = HashSet::new();
        for segment in &self.snake {
            occupied.insert(*segment);
        }

        let mut seen_food_positions = HashSet::new();
        self.foods.retain_mut(|food| {
            food.position = Vec2::from_pos(wrap(food.grid_pos(old_grid), new_grid));
            food.velocity = Vec2::zero();
            let grid_pos = food.grid_pos(new_grid);
            !occupied.contains(&grid_pos) && seen_food_positions.insert(grid_pos)
        });
    }

    fn spawn_foods(&mut self) {
        while self.foods.len() < FOOD_TARGET_COUNT {
            if let Some(pos) = self.random_empty_cell() {
                let Some(kind) = self.random_food_kind() else {
                    break;
                };
                self.foods.push(Food::new(pos, kind, Instant::now()));
            } else {
                break;
            }
        }
    }

    fn food_count(&self, kind: FoodKind) -> usize {
        self.foods.iter().filter(|food| food.kind == kind).count()
    }

    fn random_food_kind(&self) -> Option<FoodKind> {
        let available_kinds: Vec<FoodKind> = [
            FoodKind::RippleSeed,
            FoodKind::PrismPetal,
            FoodKind::StarFruit,
        ]
        .into_iter()
        .filter(|kind| self.food_count(*kind) < MAX_FOODS_PER_KIND)
        .collect();
        let mut rng = rng();
        available_kinds.choose(&mut rng).copied()
    }

    fn random_empty_cell(&self) -> Option<Pos> {
        let (w, h) = self.terminal_grid;
        let mut cells = Vec::new();
        for y in 0..h {
            for x in 0..w {
                let p = Pos { x, y };
                if !self.snake.contains(&p)
                    && !self
                        .foods
                        .iter()
                        .any(|f| f.grid_pos(self.terminal_grid) == p)
                {
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
        if self.star_effect.is_some_and(|effect| now >= effect.ends_at) {
            self.star_effect = None;
        }

        if self.grow_with_time_enabled {
            self.grow_with_time_progress += SIMULATION_TICK.as_secs_f32() * GROW_WITH_TIME_PER_SEC;
            let bonus_growth = self.grow_with_time_progress.floor() as usize;
            self.grow_with_time_progress -= bonus_growth as f32;
            self.pending_growth += bonus_growth;
        } else {
            self.grow_with_time_progress = 0.0;
        }

        self.update_food_magnet(now);

        while self
            .turn_timestamps
            .front()
            .is_some_and(|t| now.duration_since(*t) > Duration::from_secs(4))
        {
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
        self.movement_progress += self.movement_steps_per_tick(now);
        let steps = self.movement_progress.floor() as usize;
        self.movement_progress -= steps as f32;

        for _ in 0..steps {
            if !self.step_snake(now) {
                break;
            }
        }

        self.food_ripples(now);
        self.particles.retain(|p| p.expires > now);
        self.spawn_foods();
        self.last_simulation_at = now;
    }

    fn step_snake(&mut self, now: Instant) -> bool {
        let old_head = self.snake.front().copied().expect("snake has head");
        let mut new_head = self.dir.step(old_head);

        let (w, h) = self.terminal_grid;
        let wrapped = new_head.x < 0 || new_head.y < 0 || new_head.x >= w || new_head.y >= h;
        if wrapped {
            self.tunnel_dim_until = Some(now + TUNNEL_DIM);
            new_head.x = (new_head.x + w) % w;
            new_head.y = (new_head.y + h) % h;
        }

        let collision = !self.star_active(now)
            && self
                .snake
                .iter()
                .skip(1)
                .any(|segment| *segment == new_head);

        if collision {
            self.full_circle_reset(now);
            return false;
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

        if self.star_active(now) {
            self.star_scroll_segments += STAR_RAINBOW_SCROLL_SEGMENTS_PER_STEP;
        }
        self.consume_food(now);
        true
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
        self.snake.push_back(Pos {
            x: w / 2 - 1,
            y: h / 2,
        });
        self.snake.push_back(Pos {
            x: w / 2 - 2,
            y: h / 2,
        });
        self.pending_growth = 0;
        self.dir = Dir::Right;
        self.theme_brightness_steps = self.theme_brightness_steps.saturating_add(1);
        self.star_effect = None;
        self.star_scroll_segments = 0.0;
        self.movement_progress = 0.0;
        self.last_simulation_at = now;
    }

    fn consume_food(&mut self, now: Instant) {
        while let Some(idx) = self.foods.iter().position(|f| {
            let food_pos = f.grid_pos(self.terminal_grid);
            self.snake.iter().any(|segment| *segment == food_pos)
        }) {
            let food = self.foods.remove(idx);
            self.pending_growth += 3;
            match food.kind {
                FoodKind::RippleSeed => {
                    let focus = self.snake.front().copied().expect("snake has head");
                    self.flash_until = Some(now + FLASH_DURATION);
                    for p in &mut self.particles {
                        p.pos = focus;
                        p.expires = now + Duration::from_millis(300);
                    }
                }
                FoodKind::PrismPetal => {
                    self.theme_index = (self.theme_index + 1) % THEMES.len();
                }
                FoodKind::StarFruit => {
                    let already_active =
                        self.star_effect.is_some_and(|effect| now < effect.ends_at);
                    let mut speed_stacks = 1;
                    if let Some(effect) = self.star_effect
                        && now < effect.ends_at
                    {
                        speed_stacks = effect.speed_stacks.saturating_add(1);
                    }
                    self.star_effect = Some(StarEffect {
                        ends_at: now + STAR_DURATION,
                        speed_stacks,
                    });
                    if !already_active {
                        self.star_scroll_segments = 0.0;
                        self.movement_progress = 0.0;
                    }
                }
            }
        }
    }

    fn food_ripples(&mut self, now: Instant) {
        for food in &mut self.foods {
            if matches!(food.kind, FoodKind::RippleSeed) && now >= food.next_ripple {
                food.next_ripple = now + RIPPLE_PERIOD;
                let grid_pos = food.grid_pos(self.terminal_grid);
                for (dx, dy) in [(1, 0), (-1, 0), (0, 1), (0, -1)] {
                    self.particles.push(Particle {
                        pos: Pos {
                            x: grid_pos.x + dx,
                            y: grid_pos.y + dy,
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

    fn star_active(&self, now: Instant) -> bool {
        self.effective_star_stacks(now).is_some()
    }

    fn snake_cells_per_second(&self, now: Instant) -> f32 {
        self.movement_steps_per_tick(now) / SIMULATION_TICK.as_secs_f32()
    }

    fn star_remaining(&self, now: Instant) -> Option<Duration> {
        self.star_effect
            .filter(|effect| now < effect.ends_at)
            .map(|effect| effect.ends_at.duration_since(now))
    }

    fn effective_star_stacks(&self, now: Instant) -> Option<u8> {
        let active_stacks = self
            .star_effect
            .filter(|effect| now < effect.ends_at)
            .map(|effect| effect.speed_stacks)
            .unwrap_or(0);
        let cheat_stacks = if self.star_cheat_enabled {
            self.star_cheat_stacks
        } else {
            0
        };
        let stacks = active_stacks.max(cheat_stacks);
        (stacks > 0).then_some(stacks)
    }

    fn movement_steps_per_tick(&self, now: Instant) -> f32 {
        let mut steps = SIMULATION_TICK.as_secs_f32() / BASE_MOVE_INTERVAL.as_secs_f32();
        if let Some(stacks) = self.effective_star_stacks(now) {
            steps *= STAR_SPEED_MULTIPLIER.powi(stacks as i32);
        }
        steps.min(MAX_SNAKE_STEPS_PER_TICK)
    }

    fn star_scroll_segments_at(&self, now: Instant) -> f32 {
        if !self.star_active(now) {
            return self.star_scroll_segments;
        }

        let tick_secs = SIMULATION_TICK.as_secs_f32().max(0.001);
        let tick_progress =
            (now.duration_since(self.last_simulation_at).as_secs_f32() / tick_secs).clamp(0.0, 1.0);
        self.star_scroll_segments
            + (self.movement_progress + tick_progress * self.movement_steps_per_tick(now))
                * STAR_RAINBOW_SCROLL_SEGMENTS_PER_STEP
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

    fn update_food_magnet(&mut self, now: Instant) {
        if !self.food_magnet_enabled {
            for food in &mut self.foods {
                food.velocity = Vec2::zero();
            }
            return;
        }

        let Some(head) = self.snake.front().copied() else {
            return;
        };
        let head_vec = Vec2::from_pos(head);
        let grid = self.terminal_grid;
        let dt = SIMULATION_TICK.as_secs_f32();
        let snake_speed = self.snake_cells_per_second(now);
        let target_idx = self
            .foods
            .iter()
            .enumerate()
            .min_by(|(_, a), (_, b)| {
                board_delta(a.position, head_vec)
                    .length()
                    .partial_cmp(&board_delta(b.position, head_vec).length())
                    .unwrap_or(std::cmp::Ordering::Equal)
            })
            .map(|(idx, _)| idx);

        for (idx, food) in self.foods.iter_mut().enumerate() {
            if Some(idx) != target_idx {
                food.velocity = Vec2::zero();
                continue;
            }

            let delta = board_delta(food.position, head_vec);
            let distance = delta.length();
            if distance <= f32::EPSILON {
                food.position = head_vec;
                food.velocity = Vec2::zero();
                continue;
            }

            let direction = delta.normalized();
            let desired_speed = snake_speed
                * FOOD_MAGNET_MIN_SPEED_MULTIPLIER
                * (FOOD_MAGNET_EXP_FACTOR * distance)
                    .exp()
                    .min(FOOD_MAGNET_MAX_SPEED_MULTIPLIER);
            let desired_velocity = Vec2 {
                x: direction.x * desired_speed,
                y: direction.y * desired_speed,
            };
            let steer = (FOOD_MAGNET_STEER_PER_SEC * dt).clamp(0.0, 1.0);
            food.velocity.x += (desired_velocity.x - food.velocity.x) * steer;
            food.velocity.y += (desired_velocity.y - food.velocity.y) * steer;
            food.position.x += food.velocity.x * dt;
            food.position.y += food.velocity.y * dt;
            food.clamp_position(grid);
        }
    }
}

fn board_delta(from: Vec2, to: Vec2) -> Vec2 {
    Vec2 {
        x: to.x - from.x,
        y: to.y - from.y,
    }
}

fn brighten(color: Color, steps: u8) -> Color {
    let delta = (steps as u16 * 4).min(40) as u8;
    match color {
        Color::Rgb(r, g, b) => Color::Rgb(
            r.saturating_add(delta),
            g.saturating_add(delta),
            b.saturating_add(delta),
        ),
        Color::Black => Color::Rgb(delta, delta, delta),
        other => other,
    }
}

fn segment_glyphs(index: usize, flash_all_solid: bool) -> [char; 2] {
    if flash_all_solid {
        ['█', '█']
    } else if index <= 3 {
        ['█', '█']
    } else if index <= 8 {
        ['▓', '▓']
    } else if index <= 14 {
        ['▒', '▒']
    } else {
        ['░', '░']
    }
}

fn rainbow_color_for_segment(index: usize, len: usize, scroll_segments: f32) -> Color {
    let body_len = len.max(1) as f32;
    let phase = ((index as f32 / body_len) - (scroll_segments / body_len)).rem_euclid(1.0);
    let hue = phase * STAR_RAINBOW_SPAN_DEGREES;
    let (r, g, b) = hsv_to_rgb(hue, 0.9, 1.0);
    Color::Rgb(r, g, b)
}

fn hsv_to_rgb(hue: f32, saturation: f32, value: f32) -> (u8, u8, u8) {
    let chroma = value * saturation;
    let hue_prime = hue / 60.0;
    let x = chroma * (1.0 - ((hue_prime.rem_euclid(2.0)) - 1.0).abs());

    let (r1, g1, b1) = if (0.0..1.0).contains(&hue_prime) {
        (chroma, x, 0.0)
    } else if (1.0..2.0).contains(&hue_prime) {
        (x, chroma, 0.0)
    } else if (2.0..3.0).contains(&hue_prime) {
        (0.0, chroma, x)
    } else if (3.0..4.0).contains(&hue_prime) {
        (0.0, x, chroma)
    } else if (4.0..5.0).contains(&hue_prime) {
        (x, 0.0, chroma)
    } else {
        (chroma, 0.0, x)
    };

    let match_value = value - chroma;
    let to_u8 = |channel: f32| ((channel + match_value) * 255.0).round() as u8;
    (to_u8(r1), to_u8(g1), to_u8(b1))
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

fn board_rect(area: Rect) -> Rect {
    Rect {
        x: 0,
        y: 0,
        width: area.width,
        height: area.height.saturating_sub(1),
    }
}

fn grid_size_from_area(area: Rect) -> (i16, i16) {
    let board = board_rect(area);
    let grid_w = (board.width.saturating_sub(2) / 2).max(1) as i16;
    let grid_h = board.height.saturating_sub(2).max(1) as i16;
    (grid_w, grid_h)
}

fn centered_rect(area: Rect, width: u16, height: u16) -> Rect {
    let popup_width = width.min(area.width.max(1));
    let popup_height = height.min(area.height.max(1));
    Rect {
        x: area.x + area.width.saturating_sub(popup_width) / 2,
        y: area.y + area.height.saturating_sub(popup_height) / 2,
        width: popup_width,
        height: popup_height,
    }
}

fn draw(
    terminal: &mut Terminal<CrosstermBackend<io::Stdout>>,
    game: &Game,
    now: Instant,
    mode: AppMode,
    start_menu_selection: usize,
    pause_focus: PauseMenuFocus,
) -> io::Result<()> {
    terminal.draw(|frame| {
        let area = frame.area();
        let board = board_rect(area);

        let theme = game.theme();
        let inner_width = board.width.saturating_sub(2);
        let inner_height = board.height.saturating_sub(2);
        let width = (inner_width / 2) as i16;
        let height = inner_height as i16;

        let mut grid = vec![vec![' '; inner_width as usize]; height as usize];
        let mut styles = vec![
            vec![Style::default().fg(theme.fg).bg(theme.bg); inner_width as usize];
            height as usize
        ];

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
                FoodKind::StarFruit => ('★', Color::Yellow),
            };
            let grid_pos = food.grid_pos(game.terminal_grid);
            paint_double_cell(
                &mut grid,
                &mut styles,
                grid_pos,
                width,
                height,
                [glyph, glyph],
                Style::default()
                    .fg(color)
                    .bg(theme.bg)
                    .add_modifier(Modifier::BOLD),
            );
        }

        let flash_all_solid = game.flash_until.is_some_and(|t| now < t);
        let active_star = game.effective_star_stacks(now);
        let star_scroll_segments = game.star_scroll_segments_at(now);
        let mut visible_snake_segments = HashMap::new();
        for (i, seg) in game.snake.iter().enumerate() {
            visible_snake_segments.insert(*seg, i);
        }
        for (seg, i) in visible_snake_segments {
            let glyphs = segment_glyphs(i, flash_all_solid);

            let snake_color = if active_star.is_some() {
                rainbow_color_for_segment(i, game.snake.len(), star_scroll_segments)
            } else if game.tunnel_dim_until.is_some_and(|t| now < t) {
                Color::DarkGray
            } else {
                theme.fg
            };

            paint_double_cell(
                &mut grid,
                &mut styles,
                seg,
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

        let body =
            Paragraph::new(lines).block(Block::default().borders(Borders::ALL).title("Zen Snake"));
        frame.render_widget(body, board);

        let hud = format!(
            "coverage: {:>5.1}% | len: {} | sim: 60hz | render: 60fps{} | q to quit",
            game.coverage() * 100.0,
            game.snake.len(),
            if let Some(remaining) = game.star_remaining(now) {
                let stacks = game.effective_star_stacks(now).unwrap_or(0);
                format!(" | star x{}: {:.1}s", stacks, remaining.as_secs_f32())
            } else if game.star_cheat_enabled {
                format!(" | special effect x{}", game.star_cheat_stacks)
            } else {
                String::new()
            }
        );
        let hud_widget = Paragraph::new(hud).style(Style::default().fg(theme.accent).bg(theme.bg));
        frame.render_widget(
            hud_widget,
            Rect::new(0, area.height.saturating_sub(1), area.width, 1),
        );

        let selected_style = Style::default()
            .fg(theme.bg)
            .bg(theme.accent)
            .add_modifier(Modifier::BOLD);
        let popup_style = Style::default().fg(theme.fg).bg(theme.bg);

        match mode {
            AppMode::StartMenu => {
                let popup = centered_rect(board, 34, 8);
                let start_style = if start_menu_selection == 0 {
                    selected_style
                } else {
                    popup_style
                };
                let exit_style = if start_menu_selection == 1 {
                    selected_style
                } else {
                    popup_style
                };
                let menu = Paragraph::new(vec![
                    Line::from(""),
                    Line::from(Span::styled("[ Start ]", start_style)),
                    Line::from(""),
                    Line::from(Span::styled("[ Exit  ]", exit_style)),
                    Line::from(""),
                    Line::from(Span::styled("W/S or Up/Down, Enter select", popup_style)),
                ])
                .block(Block::default().borders(Borders::ALL).title("Menu"))
                .alignment(ratatui::layout::Alignment::Center)
                .style(popup_style);
                frame.render_widget(Clear, popup);
                frame.render_widget(menu, popup);
            }
            AppMode::Paused => {
                let popup = centered_rect(board, 42, 14);
                let checkbox = if game.star_cheat_enabled {
                    "[x]"
                } else {
                    "[ ]"
                };
                let grow_checkbox = if game.grow_with_time_enabled {
                    "[x]"
                } else {
                    "[ ]"
                };
                let magnet_checkbox = if game.food_magnet_enabled {
                    "[x]"
                } else {
                    "[ ]"
                };
                let cheat_control_style = if game.star_cheat_enabled {
                    popup_style
                } else {
                    popup_style.fg(Color::DarkGray)
                };
                let resume_style = if pause_focus == PauseMenuFocus::Resume {
                    selected_style
                } else {
                    popup_style
                };
                let cheat_toggle_style = if pause_focus == PauseMenuFocus::StarCheatToggle {
                    selected_style
                } else {
                    popup_style
                };
                let minus_style = if pause_focus == PauseMenuFocus::StarCheatMinus {
                    selected_style
                } else {
                    cheat_control_style
                };
                let plus_style = if pause_focus == PauseMenuFocus::StarCheatPlus {
                    selected_style
                } else {
                    cheat_control_style
                };
                let grow_with_time_style = if pause_focus == PauseMenuFocus::GrowWithTimeToggle {
                    selected_style
                } else {
                    popup_style
                };
                let food_magnet_style = if pause_focus == PauseMenuFocus::FoodMagnetToggle {
                    selected_style
                } else {
                    popup_style
                };
                let pause_lines = vec![
                    Line::from(""),
                    Line::from(Span::styled("Resume", resume_style)),
                    Line::from(""),
                    Line::from(vec![
                        Span::raw("Special Effect "),
                        Span::styled(checkbox, cheat_toggle_style),
                    ]),
                    Line::from(""),
                    Line::from(vec![
                        Span::raw("Stacks: "),
                        Span::styled("[-]", minus_style),
                        Span::raw(format!(" {} ", game.star_cheat_stacks)),
                        Span::styled("[+]", plus_style),
                    ]),
                    Line::from(""),
                    Line::from(vec![
                        Span::raw("Grow With Time "),
                        Span::styled(grow_checkbox, grow_with_time_style),
                    ]),
                    Line::from(""),
                    Line::from(vec![
                        Span::raw("Food Magnet "),
                        Span::styled(magnet_checkbox, food_magnet_style),
                    ]),
                    Line::from(""),
                    Line::from(Span::styled("Enter select, Esc resume", popup_style)),
                ];
                let menu = Paragraph::new(pause_lines)
                    .block(Block::default().borders(Borders::ALL).title("Paused"))
                    .alignment(ratatui::layout::Alignment::Center)
                    .style(popup_style);
                frame.render_widget(Clear, popup);
                frame.render_widget(menu, popup);
            }
            AppMode::Playing => {}
        }
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
    let terminal_area = Rect::new(0, 0, size.width, size.height);
    let (grid_w, grid_h) = grid_size_from_area(terminal_area);
    let mut game = Game::new(grid_w, grid_h);
    let mut mode = AppMode::StartMenu;
    let mut start_menu_selection = 0usize;
    let mut pause_focus = PauseMenuFocus::Resume;

    let start = Instant::now();
    let mut last_update = start;
    let mut last_render = start.checked_sub(RENDER_TICK).unwrap_or(start);

    loop {
        let now = Instant::now();
        let next_update = last_update + SIMULATION_TICK;
        let next_render = last_render + RENDER_TICK;
        let wait_until = next_update.min(next_render);
        let timeout = wait_until.saturating_duration_since(now);

        if event::poll(timeout)? {
            while event::poll(Duration::from_millis(0))? {
                match event::read()? {
                    Event::Key(key) if key.kind == KeyEventKind::Press => match key.code {
                        KeyCode::Char('q') => {
                            disable_raw_mode()?;
                            execute!(terminal.backend_mut(), LeaveAlternateScreen)?;
                            terminal.show_cursor()?;
                            return Ok(());
                        }
                        KeyCode::Esc => match mode {
                            AppMode::Playing => {
                                mode = AppMode::Paused;
                                pause_focus = PauseMenuFocus::Resume;
                            }
                            AppMode::Paused => {
                                mode = AppMode::Playing;
                            }
                            AppMode::StartMenu => {}
                        },
                        KeyCode::Up | KeyCode::Char('w') => match mode {
                            AppMode::StartMenu => {
                                start_menu_selection = (start_menu_selection + 1) % 2;
                            }
                            AppMode::Paused => {
                                pause_focus = pause_focus.previous();
                            }
                            AppMode::Playing => game.push_dir(Dir::Up),
                        },
                        KeyCode::Down | KeyCode::Char('s') => match mode {
                            AppMode::StartMenu => {
                                start_menu_selection = (start_menu_selection + 1) % 2;
                            }
                            AppMode::Paused => {
                                pause_focus = pause_focus.next();
                            }
                            AppMode::Playing => game.push_dir(Dir::Down),
                        },
                        KeyCode::Left | KeyCode::Char('a') => {
                            if mode == AppMode::Playing {
                                game.push_dir(Dir::Left);
                            }
                        }
                        KeyCode::Right | KeyCode::Char('d') => {
                            if mode == AppMode::Playing {
                                game.push_dir(Dir::Right);
                            }
                        }
                        KeyCode::Enter => match mode {
                            AppMode::StartMenu => {
                                if start_menu_selection == 0 {
                                    let size = terminal.size()?;
                                    let terminal_area = Rect::new(0, 0, size.width, size.height);
                                    let (grid_w, grid_h) = grid_size_from_area(terminal_area);
                                    game = Game::new(grid_w, grid_h);
                                    mode = AppMode::Playing;
                                } else {
                                    disable_raw_mode()?;
                                    execute!(terminal.backend_mut(), LeaveAlternateScreen)?;
                                    terminal.show_cursor()?;
                                    return Ok(());
                                }
                            }
                            AppMode::Paused => match pause_focus {
                                PauseMenuFocus::Resume => {
                                    mode = AppMode::Playing;
                                }
                                PauseMenuFocus::StarCheatToggle => {
                                    game.star_cheat_enabled = !game.star_cheat_enabled;
                                }
                                PauseMenuFocus::StarCheatMinus => {
                                    if game.star_cheat_enabled {
                                        game.star_cheat_stacks =
                                            game.star_cheat_stacks.saturating_sub(1).max(1);
                                    }
                                }
                                PauseMenuFocus::StarCheatPlus => {
                                    if game.star_cheat_enabled {
                                        game.star_cheat_stacks =
                                            game.star_cheat_stacks.saturating_add(1);
                                    }
                                }
                                PauseMenuFocus::GrowWithTimeToggle => {
                                    game.grow_with_time_enabled = !game.grow_with_time_enabled;
                                }
                                PauseMenuFocus::FoodMagnetToggle => {
                                    game.food_magnet_enabled = !game.food_magnet_enabled;
                                }
                            },
                            AppMode::Playing => {}
                        },
                        _ => {}
                    },
                    Event::Resize(_, _) => {
                        terminal.autoresize()?;
                        let size = terminal.size()?;
                        let terminal_area = Rect::new(0, 0, size.width, size.height);
                        let (grid_w, grid_h) = grid_size_from_area(terminal_area);
                        game.resize(grid_w, grid_h);
                    }
                    _ => {}
                }
            }
        }

        let now = Instant::now();
        while mode == AppMode::Playing && now.duration_since(last_update) >= SIMULATION_TICK {
            last_update += SIMULATION_TICK;
            game.update(last_update);
        }

        if mode != AppMode::Playing {
            last_update = now;
        }

        if now.duration_since(last_render) >= RENDER_TICK {
            draw(
                &mut terminal,
                &game,
                now,
                mode,
                start_menu_selection,
                pause_focus,
            )?;
            last_render = now;
        }
    }
}
