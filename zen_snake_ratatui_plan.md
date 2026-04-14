# Zen Snake (Ratatui) — Lite Terminal UI Game Plan

## 1) MVP Goal
Build a playable **Zen Snake** in Rust using `ratatui` + `crossterm` where flow and visuals matter more than score.

### Core MVP features
- Wraparound map (soft boundaries / tunneling).
- Living gradient snake body (`█ -> ▓ -> ▒ -> ░ -> vanish`).
- Basic food + growth.
- Ghost trail on turns.
- Full-circle reset on self-collision (shrink to length 3) instead of game over.

---

## 2) Tech Stack
- Rust stable.
- Rendering: `ratatui`.
- Input/events + terminal mode: `crossterm`.
- RNG: `rand`.
- Time: `std::time::Instant` + fixed timestep update loop.

---

## 3) Architecture (Lite but scalable)

## `App` (top-level)
Holds:
- `GameState` (snake, foods, particles, world theme, timers).
- `InputState` (queued direction changes).
- `RuntimeTuning` (dynamic tick settings).

## `GameState`
- `grid: RectSize { w, h }`
- `snake: Snake`
- `foods: Vec<Food>`
- `particles: Vec<Particle>`
- `theme: Theme`
- `paint_progress: PaintMap` (trail-covered cells)
- `score_like_metrics` (optional, hidden or tiny)

## `Snake`
- `segments: Vec<Pos>` (head at index 0)
- `dir: Dir`
- `pending_growth: u16`
- `tunnel_dim_timer: Duration` (brief dream-state dim)
- `auto_curve: Option<AutoCurveState>` (from inertia fruit)

## `Food`
Enum:
- `RippleSeed { pos, next_pulse_at }`
- `PrismPetal { pos, palette_id }`
- `InertiaFruit { pos, duration }`

## `Particle`
- `pos`
- `glyph` (`.` / `◦` / `░`)
- `ttl`
- `kind` (`Ripple`, `Spark`, `GhostPivot`, `Collapse`)

---

## 4) Main Loop
Use a hybrid loop:
1. Poll input continuously (short timeout).
2. Run fixed simulation step at `current_tick_ms`.
3. Render every frame (or after each update).

Pseudo:
- `handle_input()`
- `if now >= next_update { update(); next_update += tick }`
- `draw()`

This keeps gameplay deterministic while UI stays responsive.

---

## 5) Mechanics Mapping

## A) Living Gradient body
Render based on segment age from head:
- Head + recent N cells: `█`
- Next band: `▓`
- Next band: `▒`
- Tail band: `░`

Rule for “weight of growth”:
- Keep `solid_len` roughly constant (e.g., 4).
- Increase dissolve band proportionally with total snake length.

## B) Soft boundaries / tunnel
Movement wraps:
- `x < 0 => w-1`, `x >= w => 0` (same for `y`).
- On wrap event: set `tunnel_dim_timer = 400ms`; during this timer render snake in dimmer shade / lower-contrast glyph band.

## C) Near-miss bonus
Each update:
- Check Moore neighborhood (8 cells) around head.
- If any body segment found at distance 1 and no collision, spawn brief `Spark` particle (`░`, ttl ~250ms).

## D) Food ecosystem

### Ripple Seed
- Emits ring pulses every 2 seconds:
  - Spawn ripple particles expanding outward with fading ttl.
- On eat:
  - Reverse effect: pull active particles toward snake head over ~300ms.
  - Temporarily render full snake as `█` flash (~200ms).

### Prism Petal
- On eat: switch `Theme` palette (foreground/background/accent set).
- No growth bonus required (or small optional).

### Inertia Fruit
- On eat: enable `auto_curve` mode for N seconds.
- Snake auto-turns 90° every 10 tiles unless player overrides.
- Slight speed-up while active.

## E) Ghost trail
- On every user turn, place `GhostPivot` particle `░` with ttl = 5s.
- These also count toward paint/progress coverage.

## F) Dynamic tick rate
Track recent turn behavior over a sliding window (e.g., 4s):
- `agitation = turns_per_second + reversal_attempts_weight`
- Map agitation to tick:
  - calm: 140ms
  - medium: 110ms
  - agitated: 90ms
- Smooth with lerp to avoid jitter.

## G) Full-circle reset
On self-collision:
1. Spawn collapse particles.
2. Animate merge/shrink for ~500ms.
3. Reset snake to length 3 at safe spawn.
4. Permanently brighten global background slightly (`theme.brightness += step`).

Goal condition:
- Track percent of board touched by ghost trail/snake path.
- Win when coverage threshold reached (e.g., 75–90%).

---

## 6) Rendering Plan (ratatui)
Single full-screen `Canvas`-like grid via `Paragraph` or custom cell painting in a `Frame` area.

Render order each frame:
1. Background theme fill.
2. Paint map tint layer.
3. Particles (ripple/spark/ghost).
4. Foods.
5. Snake.
6. Minimal HUD (mode, coverage %, optional calm/agitation meter).

Use `Style` palettes per theme:
- Forest
- Deep Sea
- Dusk
- Mono Zen

---

## 7) File/Module Layout
- `src/main.rs` (bootstrap loop + terminal setup/restore)
- `src/app.rs` (App orchestration)
- `src/game/mod.rs`
  - `state.rs`
  - `snake.rs`
  - `food.rs`
  - `particles.rs`
  - `theme.rs`
  - `update.rs`
- `src/render.rs`
- `src/input.rs`
- `src/config.rs` (constants/tunables)

---

## 8) Milestone Plan

### Milestone 1 (Playability)
- Grid, movement, wraparound, input queue, basic food.
- Static snake render.

### Milestone 2 (Core Zen identity)
- Living gradient.
- Ghost trail.
- Full-circle collision reset.

### Milestone 3 (Ecosystem)
- Ripple Seed + particles.
- Prism theme shifts.
- Inertia fruit + auto-curve.

### Milestone 4 (Polish)
- Dynamic tick rate.
- Coverage-based win state.
- Balance tuning and accessibility options.

---

## 9) Tunables (start values)
- Base tick: `120ms`
- Min tick: `85ms`
- Tunnel dim duration: `400ms`
- Ghost pivot ttl: `5s`
- Ripple period: `2s`
- Inertia auto-turn cadence: `10 tiles`
- Win coverage: `80%`

Keep all in `config.rs` for easy experimentation.

---

## 10) Testing Strategy (lite)
- Unit tests:
  - wraparound math
  - self-collision detection
  - gradient band assignment by index
  - dynamic tick mapping from agitation metric
- Deterministic simulation test with seeded RNG over N ticks.
- Manual QA checklist in terminal sizes: 80x24, 120x30, 160x40.

---

## 11) Nice-to-have after MVP
- Ambient sound hooks (optional, off by default).
- Replay export (list of turns + seed).
- “Meditation mode” with no HUD.
