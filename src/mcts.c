/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mcts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpupier <qpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:45:48 by qpupier           #+#    #+#             */
/*   Updated: 2026/09/27 14:55:09 by qpupier          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

t_tree*	select_new_node(t_tree* node, t_board* board, unsigned int* round)
{
	unsigned int	best_path;
	double			score;
	double			best_score;

	best_score = -1;
	best_path = 0;
	for (unsigned int i = 0; i < board->size_x; i++)
	{
		if (!node->children[i])
			continue;
		score = (node->children[i]->victories + MCTS_UCB1_CONST * pseudo_ln(node->visits)) / (double)(node->children[i]->visits);
		if (score > best_score)
		{
			best_score = score;
			best_path = i;
		}
	}
	play_token(board, best_path, (*round % 2) + 1);
	(*round)++;
	return (node->children[best_path]);
}

t_tree*	heuristic_to_border(t_tree* node, t_board* board, unsigned int* round, unsigned char* end)
{
	if (!node)
		return (NULL);
	if (!node->children)
	{
		*end = end_game(board, node->column);
		return (node);
	}
	if (node->column != -1)
	{
		*end = end_game(board, node->column);
		if (*end)
			return (node);
	}
	for (unsigned int i = 0; i < board->size_x; i++)
	{
		if (board->array[0][i] == '.')
		{
			if (!node->children[i])
				return (node);
		}
		else if (node->children[i])
		{
			free_tree(node->children[i], board);
			node->children[i] = NULL;
		}
	}
	return (heuristic_to_border(select_new_node(node, board, round), board, round, end));
}

unsigned int	get_nb_missing_children(t_tree* node, t_board* board)
{
	unsigned int	nb_possibilities;

	nb_possibilities = 0;
	for (unsigned int i = 0; i < board->size_x; i++)
		if (board->array[0][i] == '.' && !node->children[i])
			nb_possibilities++;
	return (nb_possibilities);
}

t_tree*	create_node(t_board* board)
{
	t_tree*	node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->column = -1;
	node->visits = 0;
	node->victories = 0;
	node->children = malloc(sizeof(t_tree*) * board->size_x);
	if (!node->children)
	{
		free(node);
		return (NULL);
	}
	for (unsigned int i = 0; i < board->size_x; i++)
		node->children[i] = NULL;
	return (node);
}

t_tree*	create_child(t_tree* tree, t_board* board)
{
	unsigned int	nb_possibilities;
	unsigned int	rd;
	t_tree*			node;

	nb_possibilities = get_nb_missing_children(tree, board);
	if (!nb_possibilities)
		return (NULL);
	node = create_node(board);
	if (!node)
		return (NULL);
	rd = rand() % nb_possibilities;
	for (unsigned int i = 0; i < board->size_x; i++)
		if (board->array[0][i] == '.' && !tree->children[i])
		{
			if (!rd)
			{
				node->column = i;
				tree->children[i] = node;
				return (node);
			}
			rd--;
		}
	return (NULL);
}

static long int play_random(t_board* board)
{
	unsigned int	nb;
	unsigned int	rd;

	nb = 0;
	for (unsigned int i = 0; i < board->size_x; i++)
		if (board->array[0][i] == '.')
			nb++;
	if (!nb)
		return (-1);
	rd = rand() % nb;
	for (unsigned int i = 0; i < board->size_x; i++)
		if (board->array[0][i] == '.')
		{
			if (!rd)
				return (i);
			rd--;
		}
	return (-1);
}

static void	simulation(t_tree* node, t_board* simulated_board, unsigned int round)
{
	long int		rd_column;
	unsigned int	player;
	unsigned char	end;

	end = 0;
	while (!end)
	{
		player = (round % 2) + 1;
		rd_column = play_random(simulated_board);
		if (rd_column == -1)
			return;
		play_token(simulated_board, rd_column, player);
		round++;
		end = end_game(simulated_board, rd_column);
	}
	node->visits++;
	if (end == 1)
		node->victories++;
}

static t_stat	calculate_stats(t_tree* node, t_board* board)
{
	t_stat			stat;
	t_stat			child_stat;
	unsigned char	end;

	stat.victories = 0;
	stat.visits = 0;
	if (!node)
		return (stat);
	if (!node->children)
		return ((t_stat){node->victories, node->visits});
	end = 1;
	for (unsigned int i = 0; i < board->size_x; i++)
	{
		if (!node->children[i])
			continue;
		end = 0;
		child_stat = calculate_stats(node->children[i], board);
		stat.victories += child_stat.victories;
		stat.visits += child_stat.visits;
	}
	if (end)
		return ((t_stat){node->victories, node->visits});
	node->victories = stat.victories;
	node->visits = stat.visits;
	return ((t_stat){node->victories, node->visits});
}

unsigned int	find_max_visits(t_tree* tree, t_board* board)
{
	unsigned int	max_visits;
	unsigned int	best_column;

	max_visits = 0;
	best_column = 0;
	for (unsigned int i = 0; i < board->size_x; i++)
	{
		if (!tree->children[i])
			continue;
		if (tree->children[i]->visits > max_visits)
		{
			max_visits = tree->children[i]->visits;
			best_column = i;
		}
	}
	ft_putstr_fd("Best column: ", 1);
	ft_putnbr_fd(best_column, 1);
	ft_putstr_fd(" (", 1);
	ft_putnbr_fd(max_visits, 1);
	ft_putstr_fd(" visits)\n", 1);
	return (best_column);
}

long int	mcts_choose_column(t_board* board)
{
	t_tree*			tree;
	t_tree*			node;
	unsigned int	best_column;
	unsigned int	round;
	t_board*		simulated_board;
	unsigned char	end;
	time_t			begin;

	tree = create_node(board);
	if (!tree)
		return (-1);
	begin = time(NULL);
	while (time(NULL) - begin < TIME_TO_SIMULATE)
	{
		simulated_board = copy_board(board);
		if (!simulated_board)
		{
			free_tree(tree, board);
			return (-1);
		}
		round = 0;
		end = 0;
		node = heuristic_to_border(tree, simulated_board, &round, &end);
		if (end)
		{
			node->visits++;
			if (end == 1)
				node->victories++;
			free_children(node, board);
			node->children = NULL;
		}
		else
		{
			if (!node)
				continue;
			node = create_child(node, simulated_board);
			if (!node)
				continue;
			play_token(simulated_board, node->column, (round % 2) + 1);
			round++;
			end = end_game(simulated_board, node->column);
			if (end)
			{
				node->visits++;
				if (end == 1)
					node->victories++;
				free_children(node, board);
				node->children = NULL;
			}
		}
		simulation(node, simulated_board, round);
		calculate_stats(tree, simulated_board);
		free_board(simulated_board);
	}
	best_column = find_max_visits(tree, board);
	free_tree(tree, board);
	return (best_column);
}
