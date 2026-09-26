#include "connect4.h"
#include <limits.h>
#include <stdio.h>

const int MAX_DEPTH = 7;
#define WIN_SCORE 100000

static unsigned int col_order(t_board *board, unsigned int i) {
	return (i % 2 ? board->size_x / 2 - (i + 1) / 2
				  : board->size_x / 2 + i / 2);
}

static unsigned char opponent(unsigned char piece) {
	return (piece == 'X' ? 'O' : 'X');
}

static int add_piece(t_board *board, unsigned int col, unsigned char piece) {
	for (int row = (int)board->size_y - 1; row >= 0; row--) {
		if (board->array[row][col] == '.') {
			board->array[row][col] = piece;
			return (row);
		}
	}
	return (-1);
}

static void remove_piece(t_board *board, unsigned int col) {
	for (unsigned int row = 0; row < board->size_y; row++) {
		if (board->array[row][col] != '.') {
			board->array[row][col] = '.';
			return;
		}
	}
}

static int is_winning_move(t_board *board, int row, int col) {
	unsigned int last_row = row;
	unsigned int last_column = col;
	unsigned char last_player = board->array[last_row][last_column];
	unsigned int i;
	unsigned int j;

	for (i = 0; last_row + i < board->size_y &&
				board->array[last_row + i][last_column] == last_player;
		 i++)
		;
	if (i >= 4)
		return (1);

	for (i = 0; last_column + i < board->size_x &&
				board->array[last_row][last_column + i] == last_player;
		 i++)
		;
	for (j = 1; j <= last_column &&
				board->array[last_row][last_column - j] == last_player;
		 j++)
		;
	if (i + j - 1 >= 4)
		return (1);

	for (i = 0;
		 last_row + i < board->size_y && last_column + i < board->size_x &&
		 board->array[last_row + i][last_column + i] == last_player;
		 i++)
		;
	for (j = 1; j <= last_row && j <= last_column &&
				board->array[last_row - j][last_column - j] == last_player;
		 j++)
		;
	if (i + j - 1 >= 4)
		return (1);

	for (i = 0; last_row + i < board->size_y && i <= last_column &&
				board->array[last_row + i][last_column - i] == last_player;
		 i++)
		;
	for (j = 1; j <= last_row && last_column + j < board->size_x &&
				board->array[last_row - j][last_column + j] == last_player;
		 j++)
		;
	if (i + j - 1 >= 4)
		return (1);

	return (0);
}

static int score_window(t_board *board, int row, int col, int d_row, int d_col,
						unsigned char ai) {
	static const int points[4] = {0, 1, 10, 100};
	int mine = 0;
	int theirs = 0;
	int r;
	int c;

	for (int k = 0; k < 4; k++) {
		r = row + k * d_row;
		c = col + k * d_col;

		if (r < 0 || c < 0 || r >= (int)board->size_y ||
			c >= (int)board->size_x)
			return (0);
		if (board->array[r][c] == ai)
			mine++;
		else if (board->array[r][c] != '.')
			theirs++;
	}

	if (mine && theirs)
		return (0);

	return (mine ? points[mine] : -points[theirs]);
}

static int evaluate(t_board *board, unsigned char ai) {
	int score = 0;
	int dirs[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

	for (int row = 0; row < (int)board->size_y; row++)
		for (int col = 0; col < (int)board->size_x; col++)
			for (int d = 0; d < 4; d++)
				score +=
					score_window(board, row, col, dirs[d][0], dirs[d][1], ai);

	return (score);
}

static int alphabeta(t_board *board, int alpha, int beta, unsigned char turn,
					 unsigned char ai, int depth) {
	int best;
	int score;
	int row;
	int maximizing;
	int played;

	if (depth <= 0)
		return (evaluate(board, ai));

	maximizing = (turn == ai);
	best = maximizing ? INT_MIN : INT_MAX;
	played = 0;

	for (unsigned int i = 0; i < board->size_x; i++) {
		unsigned int col = col_order(board, i);

		if (board->array[0][col] != '.')
			continue;

		played = 1;
		row = add_piece(board, col, turn);

		if (is_winning_move(board, row, (int)col))
			score = maximizing ? WIN_SCORE + depth : -WIN_SCORE - depth;
		else
			score =
				alphabeta(board, alpha, beta, opponent(turn), ai, depth - 1);

		remove_piece(board, col);

		if (maximizing) {
			if (score > best)
				best = score;
			if (best > alpha)
				alpha = best;
		} else {
			if (score < best)
				best = score;
			if (best < beta)
				beta = best;
		}
		if (alpha >= beta)
			break;
	}

	return (played ? best : 0);
}

unsigned int select_col_ab(t_board *board, unsigned char piece) {
	int max_score = INT_MIN;
	unsigned int col_max = board->size_x / 2;
	int temp_score;
	int row;

	for (unsigned int i = 0; i < board->size_x; i++) {
		unsigned int col = col_order(board, i);
		if (board->array[0][col] != '.')
			continue;
		row = add_piece(board, col, piece);
		if (is_winning_move(board, row, (int)col))
			temp_score = WIN_SCORE + MAX_DEPTH;
		else
			temp_score = alphabeta(board, INT_MIN, INT_MAX, opponent(piece),
								   piece, MAX_DEPTH - 1);
		remove_piece(board, col);
		// printf("col %d: %d\n", col, temp_score);
		if (temp_score > max_score) {
			col_max = col;
			max_score = temp_score;
		}
	}
	return (col_max);
}
