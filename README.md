# Dots-and-Boxes-Game

Overview
--------

Dots-and-Boxes-Game is a command-line implementation of the classic pen-and-paper game "Dots and Boxes" written in C for a small fixed grid. The project includes:

- A playable two-player mode.
- A human vs bot mode with three bot difficulty levels (Easy, Medium, Hard).
- Bot vs bot/demo programs in the `DEMO/` folder.
- Unit-style tests and gameplay tests in the `testing/` folder.

By default the game grid is controlled by macros in `game/headers.h` (see "Configuration" below).

Quick features
--------------

- Grid defined by `ROW_SIZE` and `COL_SIZE` in `game/headers.h` (defaults used in this repo: `ROW_SIZE=5`, `COL_SIZE=6`).
- Easy bot: random valid moves.
- Medium bot: attempts "safe" moves and takes immediate boxes when available.
- Hard bot: uses minimax with alpha-beta pruning; the parallel version evaluates moves in threads (requires pthreads).

Build
-----

The source files are in `game/` and the demo/test drivers are in `DEMO/` and `testing/`.

Prerequisites
- A C compiler (GCC recommended) and standard C library.
- For the parallel/hard bot you need POSIX threads support. On Linux and macOS compile with `-pthread`. On Windows, either use WSL or install a pthreads compatibility library (e.g., pthreads-w32) or build using MSYS2/MinGW-w64 that provides pthread support.

Examples (Linux / macOS)

Compile the main interactive program:

```bash
gcc -O2 -pthread game/main.c -o dots
```

Run it:

```bash
./dots
```

Compile tests:

```bash
gcc -O2 -pthread testing/tests.c -o run_tests
./run_tests
```

Compile a demo (human vs bot):

```bash
gcc -O2 -pthread DEMO/human_vs_bot_1.c -o demo_human_vs_bot
./demo_human_vs_bot
```

Notes for Windows
- If you use MinGW/MSYS2, replace `-pthread` with `-lpthread` if your toolchain requires it (and ensure pthreads library is available), or use WSL which supports `-pthread` directly.
- If compiling with Microsoft Visual C (MSVC) the code will need adaptation because MSVC does not provide POSIX threads; consider using WSL or porting threading parts to Win32 threads.

Usage
-----

When running the main program you will be prompted to choose a mode:

- Two-player: two human players alternate entering moves.
- Play vs bot: choose bot difficulty (1 = Easy, 2 = Medium, 3 = Hard).

Move input format
- When prompted for a player's move, enter four integers: `r1 c1 r2 c2` representing two adjacent dots. Example: `0 0 0 1` draws a horizontal line between dot (0,0) and (0,1).
- Rows are in range `0..ROW_SIZE-1` and columns `0..COL_SIZE-1`.

Gameplay details
- The in-memory board uses a character grid with dots `.` at even/even coordinates, spaces for empty edges, `-` for horizontal edges, `|` for vertical edges, and `A`/`B` for boxes claimed by Player A or Player B.
- When a player completes one or more boxes they get another turn.
- The game ends when all boxes are claimed; the winner is the player with the higher score.

Bots
----

- Easy (`generateEasyMove`) — chooses a random valid line.
- Medium (`generateMediumMove`) — tries to take immediate boxes; otherwise selects a move that avoids creating a third edge on a box when possible.
- Hard (`generateHardMove`) — uses `getGamePhase` to switch behavior: in the opening it plays safe (medium); in midgame it runs a parallel minimax evaluation (`generateParallelMinimaxMove`) using `DEPTH` and `THREADS` macros from `game/headers.h`.

Configuration
-------------

Change the following macros in `game/headers.h` to alter behavior and board size:

- `ROW_SIZE` — number of dot rows (default 5)
- `COL_SIZE` — number of dot columns (default 6)
- `DEPTH` — minimax search depth for the hard bot
- `THREADS` — upper bound on spawned threads in the parallel evaluator

Adjusting the grid sizes requires recompiling. Note: increasing the grid size increases branching factor and will make the minimax (hard) mode much slower.

Testing and demos
-----------------

Unit-like tests: `testing/tests.c` compiles the core game logic with a small set of checks. Run as shown in the Build section.

Gameplay demos: `testing/gameplay_tests.c` and the `DEMO/` folder contain drivers for running bot-vs-bot matches and sample human-vs-bot/human-vs-human executables.

Files overview
--------------

- `game/headers.h` — central macros, typedefs, and function prototypes.
- `game/main.c` — main interactive program (includes other game .c files).
- `game/driverFunctions.c` — game initialization and high-level loops (`twoPlayer`, `bot`, `testBots`).
- `game/boardFunctions.c` — board operations, drawing lines, box checks, and display.
- `game/playerFunctions.c` — player input, score calculation, and endgame handling.
- `game/botFunctions.c` — bot move generators (easy/medium/hard), minimax and threading.
- `DEMO/` — several small drivers demonstrating modes and tournaments.
- `testing/` — automated test runners and gameplay tests.

Known limitations & notes
------------------------

- The code mixes `#include "*.c"` in driver files (for simplicity) rather than building proper object files; that means compiling `main.c` or the demo/test driver pulls in all sources. This is intentional for this project structure but can be refactored to a multi-file build using object files and a Makefile.
- Parallel minimax relies on POSIX threads; on Windows you must provide a pthreads implementation or build/run under WSL.
- Minimax depth (`DEPTH`) and grid size directly control runtime; use small grids or lower depth for faster runs.

Next steps
----------

- Run the tests with the compile commands above.
- If you want, I can add a `Makefile` and CI-friendly build scripts, or convert the build to a multi-file compilation with proper linking.

