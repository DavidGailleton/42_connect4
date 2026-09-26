/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpupier <qpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 10:57:17 by qpupier           #+#    #+#             */
/*   Updated: 2026/09/26 14:53:27 by qpupier          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"
#include <stddef.h>
#include <stdio.h>

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

static void play_token(t_board *board, unsigned int column,
					   unsigned char player) {
  unsigned int row;

  row = board->size_y - 1;
  while (row > 0 && board->array[row][column] != '.')
	row--;
  board->array[row][column] = player == 1 ? 'O' : 'X';
}

static unsigned int play_round(t_board *board, unsigned char player, unsigned char ai)
{
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
	if (player == ai)
		column = ai_choose_column(board);
	else
		column = get_column_to_play(board);
	// (void)ai;
	// (void)get_column_to_play;
	play_token(board, column - 1, player);
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
  unsigned int x_to = 0;
  unsigned int o_to = 0;

  if (last_column == 0)
	return (0);
  last_column--;

  unsigned int last_row;
  for (last_row = 0;
	   last_row < board->size_y && board->array[last_row][last_column] == '.';
	   last_row++)
	;

  if (last_row >= board->size_y)
	return (0);

  for (unsigned int x = 0; board->array[x]; x++) {
	for (unsigned int y = 0; board->array[x][y]; y++) {
	  switch (board->array[x][y]) {
	  case 'X':
		o_to = 0;
		x_to++;
		break;
	  case 'O':
		x_to = 0;
		o_to++;
		break;
	  default:
		o_to = 0;
		x_to = 0;
		break;
	  }
	  if (o_to >= 4)
		return ('O');
	  if (x_to >= 4)
		return ('X');
	}
  }

  for (unsigned int y = 0; board->array[0][y]; y++) {
	for (unsigned int x = 0; board->array[x]; x++) {
	  switch (board->array[x][y]) {
	  case 'X':
		o_to = 0;
		x_to++;
		break;
	  case 'O':
		x_to = 0;
		o_to++;
		break;
	  default:
		o_to = 0;
		x_to = 0;
		break;
	  }
	  if (o_to >= 4)
		return ('O');
	  if (x_to >= 4)
		return ('X');
	}
  }
  unsigned int i;

  for (unsigned int x = 0; board->array[x]; x++) {
	for (unsigned int y = 0; board->array[x][y]; y++) {
		if (board->array[x][y] != '.' && y + 4 < board->size_y &&
			x + 4 < board->size_x) {
		for (i = 0; i < 4; i++) {
			if (board->array[x + i][y + i] != board->array[x][y])
				break;
		}
		if (i == 4)
		  return board->array[x][y];
	  }
	  if (board->array[x][y] != '.' && y + 4 < board->size_y &&
		  x - 4 < board->size_x) {
		for (i = 0; i < 4; i++) {
		  if (board->array[x - i][y + i] != board->array[x][y])
			break;
		}
		if (i == 4)
		  return board->array[x][y];
	  }
	}
  }

  return (0);
}

static unsigned char not_end_game(t_board *board, unsigned int last_column) {
	if (board_full(board) || four_connected(board, last_column))
		return (0);
	return (1);
	(void)last_column;
}

void game(int size_x, int size_y) {
	unsigned int	last_column;
	int				round;
	unsigned char	ai;
	unsigned char	player;
	t_board*		board;

	ai = 2;
	round = 0;
	board = init_board(size_x, size_y);
	last_column = 0;
	while (not_end_game(board, last_column))
	{
		player = (round % 2) + 1;
		last_column = play_round(board, player, ai);
		round++;
	}
	ft_putstr_fd("\nResult:\n", 1);
	print_board(board);
}
