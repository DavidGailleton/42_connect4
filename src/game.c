/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpupier <qpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 10:57:17 by qpupier           #+#    #+#             */
/*   Updated: 2026/09/27 15:39:30 by qpupier          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned char column_full(t_board *board, unsigned int column) {
	unsigned int row;

	row = 0;
	while (row < board->size_y) {
		if (board->array[row][column] == '.')
			return (0);
		row++;
	}
	return (1);
}

static unsigned int get_column_to_play(t_board *board) {
	unsigned int column;
	char buffer[10];

	write(1, "Enter the column to play: ", 27);
	while (1) {
		column = 0;
		ft_memset(buffer, '\0', sizeof(buffer));
		if (read(0, buffer, sizeof(buffer)) <= 0)
			continue;
		if (is_overflow_underflow(buffer)) {
			write(1, "Invalid column. Please enter a valid column: ", 45);
			continue;
		}
		column = ft_atoi(buffer);
		if (column < 1 || column > board->size_x ||
			column_full(board, column - 1)) {
			write(1, "Invalid column. Please enter a valid column: ", 45);
			continue;
		}
		return (column);
	}
}

void play_token(t_board *board, unsigned int column, unsigned char player) {
	unsigned int row;

	row = board->size_y - 1;
	while (row > 0 && board->array[row][column] != '.')
		row--;
	board->array[row][column] = player == 1 ? 'O' : 'X';
}

static long int play_round(t_board *board, unsigned char player,
						   unsigned char ai) {
	long int tmp;
	unsigned int column;

	if (player == 1)
		ft_putstr_fd(COLOR_RED, 1);
	else
		ft_putstr_fd(COLOR_BLUE, 1);
	ft_putstr_fd("\nPlayer ", 1);
	ft_putstr_fd(player == 1 ? "1" : "2", 1);
	ft_putstr_fd("'s turn\n", 1);
	ft_putstr_fd(COLOR_RESET, 1);
	print_board(board);
	if (player != ai)
		column = get_column_to_play(board) - 1;
	else if (board->size_x <= MAXSIZE_MINIMAX)
		column = select_col_ab(board, player == 1 ? 'O' : 'X');
	else {
		tmp = mcts_choose_column(board);
		if (tmp == -1)
			return (-1);
		column = (unsigned int)tmp;
	}
	play_token(board, column, player);
	ft_putstr_fd("\ncolumn chosen: ", 1);
	ft_putnbr_fd(column, 1);
	ft_putstr_fd("\n", 1);
	return (column);
}

static unsigned char board_full(t_board *board) {
	unsigned int row;
	unsigned int column;

	row = 0;
	while (row < board->size_y) {
		column = 0;
		while (column < board->size_x) {
			if (board->array[row][column] == '.')
				return (0);
			column++;
		}
		row++;
	}
	return (1);
}

static unsigned char four_connected(t_board *board, unsigned int last_column) {
	if (last_column == 0)
		return (0);

	unsigned int last_row;
	for (last_row = 0;
		 last_row < board->size_y && board->array[last_row][last_column] == '.';
		 last_row++)
		;

	if (last_row >= board->size_y)
		return (0);

	unsigned char last_player = board->array[last_row][last_column];
	unsigned int i;
	unsigned int j;

	for (i = 0; last_row + i < board->size_y &&
				board->array[last_row + i][last_column] == last_player;
		 i++)
		;
	if (i >= 4)
		return (last_player);

	for (i = 0; last_column + i < board->size_x &&
				board->array[last_row][last_column + i] == last_player;
		 i++)
		;
	for (j = 1; j <= last_column &&
				board->array[last_row][last_column - j] == last_player;
		 j++)
		;
	if (i + j - 1 >= 4)
		return (last_player);

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
		return (last_player);

	for (i = 0; last_row + i < board->size_y && i <= last_column &&
				board->array[last_row + i][last_column - i] == last_player;
		 i++)
		;
	for (j = 1; j <= last_row && last_column + j < board->size_x &&
				board->array[last_row - j][last_column + j] == last_player;
		 j++)
		;
	if (i + j - 1 >= 4)
		return (last_player);

	return (0);
}

unsigned char end_game(t_board *board, unsigned int last_column) {
	unsigned char last_player;

	last_player = four_connected(board, last_column);
	if (last_player)
		return (last_player == 'O' ? 1 : 2);
	if (board_full(board))
		return (3);
	return (0);
}

void game(int size_x, int size_y) {

	long int tmp;
	unsigned int last_column;
	unsigned char ai;
	unsigned char player;
	t_board *board;

	ai = rand() % 2;
	board = init_board(size_x, size_y);
	last_column = 0;
	player = 1;
	while (!end_game(board, last_column)) {
		tmp = play_round(board, player, ai);
		if (tmp == -1) {
			ft_putstr_fd("Error during play_round. Exiting game.\n", 1);
			free_board(board);
			return;
		}
		last_column = (unsigned int)tmp;
		player = !player;
	}
	ft_putstr_fd("\nResult:\n", 1);
	print_board(board);
	free_board(board);
}
