/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpupier <qpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 11:25:15 by qpupier           #+#    #+#             */
/*   Updated: 2026/09/27 17:59:36 by qpupier          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

t_board *init_board(int size_x, int size_y) {
	t_board *result;
	int i;

	result = malloc(sizeof(t_board));
	if (!result)
		return (NULL);
	result->size_x = size_x;
	result->size_y = size_y;
	result->array =
		(unsigned char **)malloc(sizeof(unsigned char *) * (size_y + 1));
	if (!result->array)
		return (free(result), NULL);
	i = 0;
	while (i < size_y) {
		result->array[i] = malloc(sizeof(unsigned char) * (size_x + 1));
		if (!result->array[i]) {
			for (i = i - 1; i >= 0; i--)
				free(result->array[i]);
			free(result->array);
			free(result);
			return (NULL);
		}
		ft_memset(result->array[i], '.', sizeof(unsigned char) * size_x);
		result->array[i][size_x] = 0;
		i++;
	}
	result->array[size_y] = NULL;
	return (result);
}

void print_board(t_board *board) {
	unsigned int nb_digit = 1;
	unsigned int board_len = board->size_x;

	while (board_len >= 10) {
		nb_digit++;
		board_len /= 10;
	}

	for (unsigned int y = 0; y <= board->size_y; y++) {
		for (unsigned int x = 0; x < board->size_x; x++) {
			if (y == 0) {
				char *s_int = ft_itoa((int)x + 1);
				unsigned int cell_width = nb_digit * 2 + 1;
				unsigned int len = ft_strlen(s_int);
				unsigned int left = (cell_width - len) / 2;
				unsigned int right = cell_width - len - left;
				for (unsigned int j = 0; j < left; j++)
					write(1, " ", 1);
				write(1, s_int, len);
				for (unsigned int j = 0; j < right; j++)
					write(1, " ", 1);
				free(s_int);
			} else {
				for (unsigned int j = 0; j < nb_digit; j++)
					write(1, " ", 1);
				if (board->array[y - 1][x] == 'O')
					ft_putstr_fd(COLOR_RED, 1);
				else if (board->array[y - 1][x] == 'X')
					ft_putstr_fd(COLOR_YELLOW, 1);
				else
					ft_putstr_fd(COLOR_BLUE, 1);
				write(1, &board->array[y - 1][x], 1);
				ft_putstr_fd(COLOR_RESET, 1);
				for (unsigned int j = 0; j < nb_digit; j++)
					write(1, " ", 1);
			}
		}
		write(1, "\n", 1);
	}
}

void free_board(t_board *board) {
	if (!board)
		return;
	for (unsigned int i = 0; i < board->size_y; i++)
		free(board->array[i]);
	free(board->array);
	free(board);
}
