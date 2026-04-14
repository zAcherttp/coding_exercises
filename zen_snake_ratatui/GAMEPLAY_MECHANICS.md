# Zen Snake Gameplay Mechanics

This document describes the gameplay as it is currently implemented in `src/main.rs`.

## Overview

Zen Snake is a terminal snake game built with `ratatui` and `crossterm`. It uses:

- a `60 Hz` simulation loop
- a `60 Hz` render loop
- movement tuned to feel like one base snake-cell step every `100 ms`
- wraparound world edges for the snake
- a start menu and an in-game pause menu
- multiple fruit types, special effects, and optional cheats

## Menus And Controls

### Start menu

On launch, the game opens to a start menu with:

- `Start`
- `Exit`

Navigation:

- `W` / `S`
- `Up` / `Down`
- `Enter` to confirm

Choosing `Start` creates a fresh run using the current terminal size.

### In-game controls

- `WASD` or arrow keys change snake direction
- opposite-direction turns are rejected
- `Esc` opens the pause menu
- `q` exits immediately

### Pause menu

The pause menu contains:

- `Resume`
- `Special Effect`
- `Stacks: [-] n [+]`
- `Grow With Time`
- `Food Magnet`

Navigation:

- `W` / `S`
- `Up` / `Down`
- `Enter` to toggle or activate the focused item
- `Esc` resumes play

## Simulation And Movement

### Timing

- simulation tick: `16.666667 ms` (`60 Hz`)
- render tick: `16.666667 ms` (`60 FPS`)
- base movement feel: `100 ms` per cell

Internally, the game accumulates fractional movement progress each simulation tick, so the world updates at `60 Hz` while the snake still feels like it moves at the older `100 ms` cadence.

### Speed modifiers

The snake speed can be increased by star effects and cheats, but the final movement speed is capped.

- max snake speed: `14 cells/sec`

That cap is universal because it is applied in the shared movement-rate calculation.

## Board, Resize, And Wrapping

### Board layout

- the playfield block starts at terminal origin `(0, 0)`
- the HUD occupies the final terminal line
- the game board size is derived from the current terminal size

### Terminal resize

When the terminal is resized:

- the board dimensions are recalculated
- the snake, paint trail, particles, and foods are remapped into the new bounds
- foods that would overlap the snake or duplicate another food position are discarded and later replenished by normal spawn logic

### Edge behavior

The snake wraps across board edges.

On a wrap:

- the head re-enters from the opposite edge
- the snake gets a temporary tunnel-dim visual effect

Food magnet movement does **not** use portal logic. Magnetized foods move only within board-local space and are clamped to the board.

## Snake State

The snake starts at length `3` and faces right.

The body is stored from head to tail, and rendering resolves overlaps explicitly:

- if multiple body segments occupy the same cell, the later body segment wins visually

This matters during star overlap states, where the snake may legally pass through itself.

## Collisions

### Normal self-collision

Without an active star effect, the snake colliding with its own body triggers a reset instead of a game over.

Reset behavior:

- ripple particles spawn across the old body
- snake length resets to `3`
- direction resets to `Right`
- pending growth is cleared
- active star state is cleared
- star scroll state is cleared

### Star overlap behavior

While star is active:

- self-collision is disabled
- the head can pass through the snake body

When star ends:

- existing overlapped body cells remain safe
- a future head-to-body collision under normal rules still causes a reset

## Paint Trail And Particles

### Paint trail

Every new head position is added to a persistent coverage map.

- covered cells render as `..`
- HUD coverage is the percentage of board cells ever painted

### Ghost particles

On successful turns, the previous head position emits a ghost particle with a `5s` lifetime.

### Spark particles

If the new head is within a Moore-neighborhood near miss of the body, a short spark particle is emitted.

### Ripple particles

Ripple particles are used by:

- ripple fruit ambient pulses
- collision reset bursts

## Food System

### Spawn rules

The game refills food up to:

- total foods: `6`
- max foods per type: `3`

Food types are chosen randomly from any type still under its per-type cap.

### Food rendering

Foods are rendered by their current board cell:

- `RippleSeed`: `◎`
- `PrismPetal`: `✶`
- `StarFruit`: `★`

### Consumption rule

Food is consumed when its current grid cell touches **any** snake segment, not only the head.

This is especially important for magnetized food, which may reach the body before the head.

### RippleSeed

On consume:

- adds `3` pending growth
- triggers a short full-body solid flash
- pulls existing particles to the head position briefly

Ambient behavior:

- emits a small ripple pulse every `2s`

### PrismPetal

On consume:

- adds `3` pending growth
- advances to the next visual theme

### StarFruit

On consume:

- adds `3` pending growth
- grants or refreshes star effect
- adds one speed stack
- resets the star timer to `6s`

If star is already active, the stack count increases but the timer refreshes instead of extending cumulatively.

## Star Effect

Star can come from:

- eating `StarFruit`
- enabling the `Special Effect` cheat

### Core effects

- increases snake speed
- allows moving through the snake’s own body
- enables rainbow rendering across the snake body

### Stacks

The effective star stack count is the maximum of:

- active timed star stacks
- cheat-configured `Special Effect` stacks

### Visuals

When star is active, the snake body renders as a scrolling rainbow:

- the gradient is distributed across head-to-tail order
- the phase is circular, so the loop is smooth
- the scroll advances along the snake body path
- the scroll is tied to movement progress, not just wall-clock time

## Cheats

### Special Effect

`Special Effect` forces a star-like state without requiring fruit pickup.

- checkbox enables or disables it
- stack count can be adjusted with `-` and `+`
- minimum stack count is `1`
- cheat star visuals are enabled as well

### Grow With Time

When enabled, the snake gains passive growth at:

- `2 length/sec`

This works by feeding the normal pending-growth system through a time accumulator.

### Food Magnet

When enabled:

- only one food is pulled at a time
- the active target is the food currently closest to the snake head
- the pull target is the snake head
- foods move with continuous position and velocity, not teleport steps
- movement uses a direct board-local trajectory, not edge portals
- speed increases with distance using a softened exponential curve
- speed is bounded so foods catch up without jumping erratically

If the target changes:

- the old target’s velocity is zeroed immediately
- the new closest food begins homing

## HUD

The HUD shows:

- coverage percent
- current snake length
- simulation/render rate label
- star timer and stack count when a timed star is active
- `special effect xN` when cheat star is enabled without a timed star

## Themes

The game cycles through predefined themes. Prism fruit advances to the next theme, and repeated collision resets gradually brighten the current background.

## Rendering Notes

- snake cells are double-width painted for better terminal proportions
- the body uses denser glyphs near the head and lighter glyphs near the tail
- wrap events temporarily dim the snake
- overlap rendering prioritizes the later body segment

## Current Behavioral Summary

The current game is best described as a fast terminal snake sandbox with:

- wraparound navigation
- coverage painting
- themed fruit effects
- stackable star speed
- smooth rainbow body rendering
- pause-menu cheats for star state, passive growth, and food magnetism
- reset-on-crash instead of game over
