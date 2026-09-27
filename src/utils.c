/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpupier <qpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 11:34:38 by qpupier           #+#    #+#             */
/*   Updated: 2026/09/27 15:05:05 by qpupier          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

void	free_tree(t_tree* node, t_board* board)
{
	if (!node)
		return;
	free_children(node, board);
	free(node);
}

void	free_children(t_tree* node, t_board* board)
{
	if (!node || !node->children)
		return;
	for (unsigned int i = 0; i < board->size_x; i++)
		if (node->children[i])
			free_tree(node->children[i], board);
	free(node->children);
	node->children = NULL;
}

unsigned int	pseudo_ln(unsigned int n)
{
	unsigned int	result;

	result = 0;
	while (n > 1)
	{
		n *= 0.5;
		result++;
	}
	return (result);
}

void	print_tree(t_tree* node, int depth, t_board* board)
{
	if (!node)
		return;
	for (int i = 0; i < depth; i++)
		ft_putstr_fd("  ", 1);
	ft_putnbr_fd(node->column, 1);
	ft_putstr_fd(" (", 1);
	ft_putnbr_fd(node->victories, 1);
	ft_putstr_fd(" / ", 1);
	ft_putnbr_fd(node->visits, 1);
	ft_putstr_fd(")\n", 1);
	if (node->children)
		for (unsigned int i = 0; i < board->size_x; i++)
			print_tree(node->children[i], depth + 1, board);
}

t_board*	copy_board(t_board* board)
{
	t_board*	new_board;

	new_board = malloc(sizeof(t_board));
	if (!new_board)
		return (NULL);
	new_board->size_x = board->size_x;
	new_board->size_y = board->size_y;
	new_board->array = malloc(sizeof(unsigned char*) * new_board->size_y);
	if (!new_board->array)
	{
		free(new_board);
		return (NULL);
	}
	for (unsigned int i = 0; i < new_board->size_y; i++)
	{
		new_board->array[i] = malloc(sizeof(unsigned char) * new_board->size_x);
		if (!new_board->array[i])
		{
			for (unsigned int j = 0; j < i; j++)
				free(new_board->array[j]);
			free(new_board->array);
			free(new_board);
			return (NULL);
		}
		for (unsigned int j = 0; j < new_board->size_x; j++)
			new_board->array[i][j] = board->array[i][j];
	}
	return (new_board);
}
