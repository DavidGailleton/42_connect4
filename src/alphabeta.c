#include "connect4.h"

const int MAX_DEPTH = 3;

// Score of one window of 4 cells starting at (row, col) and going in
// direction (d_row, d_col). The cell (new_row, new_col) counts as `piece`.
// Returns 0 if the window is out of the board or contains an opponent piece.
static int score_window(t_board *board, int row, int col, int d_row, int d_col,
						int new_row, int new_col, unsigned char piece) {
	static const int points[5] = {0, 1, 10, 100, 1000};
	int count;
	int r;
	int c;

	count = 0;
	for (int k = 0; k < 4; k++) {
		r = row + k * d_row;
		c = col + k * d_col;
		if (r < 0 || c < 0 || r >= (int)board->size_y ||
			c >= (int)board->size_x)
			return (0);
		if (r == new_row && c == new_col)
			count++;
		else if (board->array[r][c] == piece)
			count++;
		else if (board->array[r][c] != '.')
			return (0);
	}
	return (points[count]);
}

// Score gained by `piece` ('O' or 'X') by playing in col_to_add (0-based).
// Every window of 4 cells containing the new piece (row, column, both
// diagonals) that has no opponent piece gives: +1 for 1 own piece, +10 for 2,
// +100 for 3 and +1000 for 4. The board is not modified.
// Returns 0 if the column is full.
int evaluate(t_board *board, unsigned int col_to_add, unsigned char piece) {
	static const int dirs[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
	int new_row;
	int score;

	new_row = board->size_y - 1;
	while (new_row >= 0 && board->array[new_row][col_to_add] != '.')
		new_row--;
	if (new_row < 0)
		return (0);
	score = 0;
	for (int d = 0; d < 4; d++)
		for (int shift = -3; shift <= 0; shift++)
			score +=
				score_window(board, new_row + shift * dirs[d][0],
							 (int)col_to_add + shift * dirs[d][1], dirs[d][0],
							 dirs[d][1], new_row, col_to_add, piece);
	return (score);
}

unsigned int alphabeta(t_board *board, int alpha, int beta,
					   unsigned int ai_turn, int depth) {}

#include <stdio.h>
unsigned int select_col_ab(t_board *board, unsigned char piece) {
	int max_score = 0;
	int temp_score;

	for (unsigned int col = (board->size_y) / 2;
		 col < board->size_y && col >= 0; col = col % 2 ? col + 1 : col - 2) {
		temp_score = evaluate(board, col, piece);
		printf("col %d: %d\n", col, temp_score);
	}
}
