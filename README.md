# connect4

Connect Four against an AI, in C, playable in the terminal or in a window. A 42 Lyon team project with Quentin Pupier ([qpupier](https://github.com/qpupier)).

## Features

- Board size chosen at launch (at least 6 rows and 6 columns)
- The first player (you or the AI) is picked at random
- Two AIs, chosen from the board width:
  - up to 30 columns: minimax with alpha-beta pruning. The search depth goes down as the board gets wider (9 plies under 8 columns, 4 plies from 16 columns)
  - wider boards: Monte Carlo Tree Search with UCB1
- Terminal mode with a colored board, or graphic mode with MiniLibX (click a column to play)

## Build and run

Needs `cc`, `make` and the X11 development libraries (`libX11`, `libXext`) for MiniLibX, which is included in `mlx/`.

```sh
make
./connect4 6 7        # rows, columns: terminal mode
./connect4 6 7 -v     # graphic mode
```

## Who did what

- **David Gailleton**: argument parsing, win detection, the alpha-beta AI
- **Quentin Pupier**: the board and two-player game loop, the MCTS AI, the graphic mode

`mlx/` is the MiniLibX library from 42 (see `mlx/LICENSE`); `libft/` is my libft.
