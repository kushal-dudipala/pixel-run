# Pixel-Run 🕹️
*A timed avoidance game for the Game Boy Advance (GBA)*

## Overview
Pixel-Run is a simple GBA game built in C, where the player must navigate to the goal while avoiding moving enemies — all within a limited time.  
The game runs as a finite-state machine with states for `START`, `PLAY`, `WIN`, `LOSE`, and `RESET`. Wrote originally for Georgia Tech Computer Organization Course

## Features
- Classic GBA Mode 3 graphics (framebuffer drawing)
- 25-second countdown timer
- Collision detection for enemies and goal
- State-based logic for win/loss conditions
- Custom sprites for player, enemies, and screens

## Build & Run
You can compile and run the game using the provided Makefile and Docker script.

```bash
# Build
make

# Run with Docker 
./docker-gba.sh
```
