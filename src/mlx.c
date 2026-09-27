/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpupier <qpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 16:18:58 by qpupier           #+#    #+#             */
/*   Updated: 2026/09/27 21:27:13 by qpupier          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

static int	ft_create_img(void *ptr, t_mlx_img *img, int w, int h)
{
	img->ptr = mlx_new_image(ptr, w, h);
	if (!img->ptr)
		return (0);
	img->img = (unsigned int *)mlx_get_data_addr(img->ptr, &img->bpp, &img->s_l,
			&img->end);
	if (!img->img)
		return (0);
	img->w = w;
	img->h = h;
	return (1);
}

static void	ft_pixel_put_rgb(t_mlx_img img, int x, int y, t_rgb color)
{
	unsigned int	index;
	unsigned int	pixel;

	if (x < 0 || y < 0 || x >= img.w || y >= img.h)
		return ;
	index = y * (img.s_l / (img.bpp * 0.125)) + x;
	pixel = ((unsigned int)color.a << 24)	\
			| ((unsigned int)color.r << 16)	\
			| ((unsigned int)color.g << 8)	\
			| (unsigned int)color.b;
	img.img[index] = pixel;
}

static inline double	distance(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

static void	mlx_draw_board(t_mlx *mlx_data)
{
	unsigned int	cell_size_x;
	unsigned int	cell_size_y;

	if (!ft_create_img(mlx_data->mlx, &mlx_data->img, mlx_data->width, mlx_data->height))
		return;
	cell_size_x = (mlx_data->width - 2 * MARGIN) / mlx_data->board->size_x;
	cell_size_y = (mlx_data->height - 2 * MARGIN) / mlx_data->board->size_y;
	mlx_data->cell_size = (cell_size_x < cell_size_y) ? cell_size_x : cell_size_y;
	mlx_data->interval_x = (mlx_data->width - 2 * MARGIN - mlx_data->board->size_x * mlx_data->cell_size) / (mlx_data->board->size_x + 1);
	mlx_data->interval_y = (mlx_data->height - 2 * MARGIN - mlx_data->board->size_y * mlx_data->cell_size) / (mlx_data->board->size_y + 1);
	for (int y = 0; y < mlx_data->img.h; y++)
		for (int x = 0; x < mlx_data->img.w; x++)
		{
			if (x > MARGIN && x < mlx_data->img.w - MARGIN && y > MARGIN && y < mlx_data->img.h - MARGIN)
				ft_pixel_put_rgb(mlx_data->img, x, y, (t_rgb){0, 0, 150, 255});
			else
				ft_pixel_put_rgb(mlx_data->img, x, y, (t_rgb){0, 0, 0, 255});
		}
	for (unsigned int y = 0; y < mlx_data->board->size_y; y++)
		for (unsigned int x = 0; x < mlx_data->board->size_x; x++)
			for (unsigned int i = 0; i < mlx_data->cell_size; i++)
				for (unsigned int j = 0; j < mlx_data->cell_size; j++)
					if (distance(i, j, mlx_data->cell_size / 2, mlx_data->cell_size / 2) < mlx_data->cell_size / 2 * 0.8)
					{
						if (distance(i, j, mlx_data->cell_size / 2 - 0.1 * mlx_data->cell_size, mlx_data->cell_size / 2 - 0.1 * mlx_data->cell_size) < mlx_data->cell_size / 2 * 0.8)
							ft_pixel_put_rgb(mlx_data->img, MARGIN + mlx_data->interval_x + x * (mlx_data->cell_size + mlx_data->interval_x) + i, MARGIN + mlx_data->interval_y + y * (mlx_data->cell_size + mlx_data->interval_y) + j, (t_rgb){0, 0, 0, 255});
						else
							ft_pixel_put_rgb(mlx_data->img, MARGIN + mlx_data->interval_x + x * (mlx_data->cell_size + mlx_data->interval_x) + i, MARGIN + mlx_data->interval_y + y * (mlx_data->cell_size + mlx_data->interval_y) + j, (t_rgb){0, 0, 100, 255});
					}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img.ptr, 0, 0);
	mlx_string_put(mlx_data->mlx, mlx_data->win, MARGIN / 2, MARGIN / 2, 0xFFFFFF, mlx_data->ai == 1 ? "You are player 2 (yellow) and the AI is player 1 (red)." : "You are player 1 (red) and the AI is player 2 (yellow).");
}

void	mlx_draw_piece(t_mlx *mlx_data, t_board *board, unsigned char next_ai_turn)
{
	for (unsigned int y = 0; y < board->size_y; y++)
		for (unsigned int x = 0; x < board->size_x; x++)
			for (unsigned int i = 0; i < mlx_data->cell_size; i++)
				for (unsigned int j = 0; j < mlx_data->cell_size; j++)
					if (distance(i, j, mlx_data->cell_size / 2, mlx_data->cell_size / 2) < mlx_data->cell_size / 2 * 0.8)
					{
						if (distance(i, j, mlx_data->cell_size / 2 - 0.05 * mlx_data->cell_size, mlx_data->cell_size / 2 - 0.05 * mlx_data->cell_size) > mlx_data->cell_size / 2 * 0.8)
							ft_pixel_put_rgb(mlx_data->img, MARGIN + mlx_data->interval_x + x * (mlx_data->cell_size + mlx_data->interval_x) + i, MARGIN + mlx_data->interval_y + y * (mlx_data->cell_size + mlx_data->interval_y) + j, (t_rgb){0, 0, 100, 255});
						else if (board->array[y][x] == 'O')
							ft_pixel_put_rgb(mlx_data->img, MARGIN + mlx_data->interval_x + x * (mlx_data->cell_size + mlx_data->interval_x) + i, MARGIN + mlx_data->interval_y + y * (mlx_data->cell_size + mlx_data->interval_y) + j, (t_rgb){200, 0, 0, 255});
						else if (board->array[y][x] == 'X')
							ft_pixel_put_rgb(mlx_data->img, MARGIN + mlx_data->interval_x + x * (mlx_data->cell_size + mlx_data->interval_x) + i, MARGIN + mlx_data->interval_y + y * (mlx_data->cell_size + mlx_data->interval_y) + j, (t_rgb){200, 200, 0, 255});
					}
	// if (!next_ai_turn)
	// 	for (int y = mlx_data->height - MARGIN; y < mlx_data->height; y++)
	// 		for (int x = 0; x < MARGIN; x++)
	// 			ft_pixel_put_rgb(mlx_data->img, x, y, (t_rgb){0, 0, 0, 255});
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img.ptr, 0, 0);
	mlx_string_put(mlx_data->mlx, mlx_data->win, MARGIN / 2, MARGIN / 2, 0xFFFFFF, mlx_data->ai == 1 ? "You are player 2 (yellow) and the AI is player 1 (red)." : "You are player 1 (red) and the AI is player 2 (yellow).");
	// if (next_ai_turn)
	// 	mlx_string_put(mlx_data->mlx, mlx_data->win, MARGIN / 2, mlx_data->height - MARGIN / 2, 0xFFFFFF, "AI is thinking...");
}

t_mlx*	init_mlx(t_board* board)
{
	t_mlx*	mlx_data;

	mlx_data = malloc(sizeof(t_mlx));
	if (!mlx_data)
		return (NULL);
	mlx_data->board = board;
	if (!mlx_data->board)
	{
		free(mlx_data);
		return (NULL);
	}
	mlx_data->ai = rand() % 2 + 1;
	mlx_data->mlx = mlx_init();
	mlx_data->width = WIN_WIDTH;
	mlx_data->height = WIN_HEIGHT;
	mlx_data->win = mlx_new_window(mlx_data->mlx, mlx_data->width, mlx_data->height, "Connect4");
	mlx_draw_board(mlx_data);
	mlx_data->round = 0;
	return (mlx_data);
}

void	exit_mlx(t_mlx* mlx_data, int exit_code)
{
	if (mlx_data)
	{
		if (mlx_data->img.ptr)
			mlx_destroy_image(mlx_data->mlx, mlx_data->img.ptr);
		if (mlx_data->win)
			mlx_destroy_window(mlx_data->mlx, mlx_data->win);
		if (mlx_data->board)
			free_board(mlx_data->board);
		free(mlx_data);
	}
	exit(exit_code);
}

int	mlx_mouse_hook_detect(int button, int x, int y, t_mlx* mlx_data)
{
	int				column;
	short int		status;
	unsigned char	player;

	column = -1;
	player = mlx_data->round % 2 + 1;
	// if (player == mlx_data->ai)
	// 	mlx_string_put(mlx_data->mlx, mlx_data->win, MARGIN / 2, mlx_data->height - MARGIN / 2, 0xFFFFFF, "AI is thinking...");
	// else
	if (player != mlx_data->ai)
	{
		if (button != 1 || x < 0 || y < 0 || (unsigned int)x < MARGIN || (unsigned int)y < MARGIN || (unsigned int)x > mlx_data->width - MARGIN || (unsigned int)y > mlx_data->height - MARGIN)
			return (0);
		column = (x - MARGIN) / (mlx_data->cell_size + mlx_data->interval_x);
		if (column_full(mlx_data->board, column))
			return (0);
	}
	ft_putstr_fd("\nLoop 1\n", 1);
	status = loop(mlx_data->board, mlx_data->ai, mlx_data, &mlx_data->round, column);
	if (status)
	{
		ft_putstr_fd("\nFinal board state:\n", 1);
		print_board(mlx_data->board);
		if (status == -1)
		{
			ft_putstr_fd("Error during loop. Exiting game.\n", 1);
			exit_mlx(mlx_data, EXIT_FAILURE);
		}
		if (status == 1)
			ft_putstr_fd("\nPlayer 1 (O) wins!\n", 1);
		else if (status == 2)
			ft_putstr_fd("\nPlayer 2 (X) wins!\n", 1);
		else if (status == 3)
			ft_putstr_fd("\nIt's a draw!\n", 1);
		if (status == 1 || status == 2)
		{
			if (mlx_data->ai == status)
			{
				ft_putstr_fd(COLOR_RED, 1);
				ft_putstr_fd("\nLoss!\n", 1);
			}
			else
			{
				ft_putstr_fd(COLOR_GREEN, 1);
				ft_putstr_fd("\nVictory!\n", 1);
			}
			ft_putstr_fd(COLOR_RESET, 1);
		}
		exit_mlx(mlx_data, EXIT_SUCCESS);
	}
	if (player != mlx_data->ai)
	{
		ft_putstr_fd("\nLoop 2\n", 1);
		mlx_mouse_hook_detect(1, 0, 0, mlx_data);
	}
	return (0);
}
