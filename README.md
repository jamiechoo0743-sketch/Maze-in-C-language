# Maze Game

## Description

This project is a C-based maze game where the player must collect the
treasure and then reach the goal while avoiding the enemy.

The program uses multiple C source and header files to separate the
different functionalities of the game.

## Features

The game includes the following functionalities:

- Loading the maze from a text file
- Displaying the maze with colours
- Player movement using keyboard input
- Treasure collection
- Goal and winning condition
- Enemy movement using a direction-based algorithm
- Random path selection using the provided random number generator
- Enemy movement in normal and furious modes
- Undo functionality using a linked list
- Immediate keyboard input without pressing Enter
- Screen clearing and short delays for gameplay
- Dynamic memory allocation and deallocation

## Game Rules

The player is represented by:

- `P` - Player
- `T` - Treasure
- `G` - Goal
- `<` / direction symbol - Enemy
- `#` - Wall

The player must collect the treasure before entering the goal.

The enemy moves after the player's movement. In normal mode, the enemy
moves two steps. After the player collects the treasure, the enemy enters
furious mode and moves three steps.

If the enemy reaches the player, the game is over.

## Controls

| Key | Action |
|-----|--------|
| `W` / `w` | Move up |
| `S` / `s` | Move down |
| `A` / `a` | Move left |
| `D` / `d` | Move right |
| `U` / `u` | Undo the previous move |

The player can use the undo command to restore the previous game state.

## Enemy Movement

The enemy uses its current orientation to determine its forward, left,
right and backward directions.

The enemy:

1. Continues moving forward when the path is clear.
2. Uses the random number generator when a decision between available
   paths is required.
3. Turns left or right when only one side path is available.
4. Turns 180 degrees when it reaches a complete dead end.
5. Changes its movement speed after the player collects the treasure.

The enemy movement is implemented in `game.c`.

## Furious Mode

When the player collects the treasure, the enemy enters furious mode.

In furious mode:

- The enemy moves three steps after each player movement.
- The enemy is displayed differently to make the mode easier to notice.

## Undo System

The undo functionality stores previous game states using a linked list.

Each `GameState` stores information such as:

- Player position
- Enemy position
- Treasure position
- Enemy direction
- Treasure collection status

The main linked-list functions are:

- `insertFirst()` - stores a previous game state
- `removeFirst()` - restores the previous game state
- `freeList()` - releases the linked-list memory

## File Structure

| File | Purpose |
|------|---------|
| `main.c` | Main game loop, input handling and game flow |
| `game.c` | Player movement, enemy movement, game logic and undo functions |
| `game.h` | Function declarations and game data structures |
| `map.c` | Loading and freeing the map |
| `map.h` | Map function declarations |
| `color.c` | Terminal colour functions |
| `color.h` | Colour function declarations |
| `terminal.c` | Immediate keyboard input functions |
| `terminal.h` | Terminal function declarations |
| `random.c` | Random number generator |
| `random.h` | Random number generator declarations |
| `newSleep.c` | Provides a short delay during gameplay |
| `newSleep.h` | Sleep function declaration |
| `Makefile` | Automates compilation and cleaning |

## Compilation

The project can be compiled using the provided Makefile.

First, clean any previous object files and executable:

```bash
make clean
