/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpupier <qpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 11:25:15 by qpupier           #+#    #+#             */
/*   Updated: 2026/09/26 11:49:33 by qpupier          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"
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
		return (NULL); // TODO: free result
	i = 0;
	while (i < size_y) {
		result->array[i] = malloc(sizeof(unsigned char) * (size_x + 1));
		if (!result->array[i])
			return (NULL); // TODO: free result->array and result
		ft_memset(result->array[i], '.', sizeof(unsigned char) * size_x);
		result->array[i][size_x] = 0;
		i++;
	}
	result->array[size_y] = NULL;
	return (result);
}

void print_board(t_board *board) {
	unsigned int i;
	unsigned int j;

	j = 0;
	while (j < board->size_y) {
		i = 0;
		while (i < board->size_x) {
			if (board->array[j][i] == 'O')
				ft_putstr_fd(COLOR_RED, 1);
			else if (board->array[j][i] == 'X')
				ft_putstr_fd(COLOR_BLUE, 1);
			write(1, &board->array[j][i], 1);
			ft_putstr_fd(COLOR_RESET, 1);
			write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
}
