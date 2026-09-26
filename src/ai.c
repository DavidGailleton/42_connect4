/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpupier <qpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:45:48 by qpupier           #+#    #+#             */
/*   Updated: 2026/09/26 15:31:41 by qpupier          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

static void		simulate_column(t_board* board, unsigned int column, unsigned int* visits, unsigned int* victories)
{
	visits[column]++;
	(void)board;
	(void)victories;
}

unsigned int	best_column(t_board* board, double* scores)
{
	unsigned int	column_min;

	column_min = 0;
	for (unsigned int x = 0; x < board->size_x; x++)
	{
		if (!x || scores[x] < scores[column_min])
			column_min = x;
	}
	return (column_min + 1);
}

unsigned int	ai_choose_column(t_board* board)
{
	double			scores[board->size_x];
	unsigned int	column_min;
	unsigned int*	victories;
	unsigned int*	visits;

	return (rand() % board->size_x + 1);
	visits = malloc(sizeof(unsigned int) * board->size_x);
	if (!visits)
		return (rand() % board->size_x + 1);// TODO: handle malloc failure
	victories = malloc(sizeof(unsigned int) * board->size_x);
	if (!victories)
	{
		free(visits);
		return (rand() % board->size_x + 1);// TODO: handle malloc failure
	}
	ft_memset(visits, 0, sizeof(visits));
	ft_memset(victories, 0, sizeof(victories));
	ft_memset(scores, 0, sizeof(scores));
	simulate_column(board, rand() % board->size_x, visits, victories);
	for (unsigned int i = 0; i < 2; i++)
	{
		column_min = 0;
		for (unsigned int x = 0; x < board->size_x && i > 0; x++)
		{
			scores[x] = (victories[x] + MCTS_UCB1_CONST) / (visits[x] + 1);
			if (!x || scores[x] < scores[column_min])
				column_min = x;
		}
		simulate_column(board, column_min, visits, victories);
	}
	free(visits);
	free(victories);
	return (best_column(board, scores));
}
