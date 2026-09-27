#include <stdlib.h>
#include <unistd.h>

#include "connect4.h"
#include "libft.h"

int main(int argc, char *argv[]) {
	int parse_result = check_args(argc, argv);
	unsigned char graphic_mode;
	t_board *board;
	t_mlx *mlx_data;

	graphic_mode = 0;
	if (!parse_result && argc == 4) {
		if (ft_strncmp(argv[3], "-v", 8) == 0)
			graphic_mode = 1;
		else
			parse_result = INVALID_NB_ARGS;
	}
	switch (parse_result) {
	case INVALID_NB_ARGS:
		ft_putstr_fd("Usage: ./connect4 {nb_row} {nb_collumn} [-v]\n", 2);
		return (EXIT_FAILURE);
	case INVALID_INT_ARGS:
		ft_putstr_fd(
			"Args should only be valid integer:\nExample: ./connect4 8 10\n",
			2);
		return (EXIT_FAILURE);
	case INVALID_ROW_LEN:
		ft_putstr_fd("Row arg should be minimum 6\n", 2);
		return (EXIT_FAILURE);
	case INVALID_COLUMN_LEN:
		ft_putstr_fd("Column arg should be minimum 6\n", 2);
		return (EXIT_FAILURE);
	default:
		break;
	}
	srand((unsigned int)time(NULL));
	board = init_board(ft_atoi(argv[2]), ft_atoi(argv[1]));
	if (!board) {
		ft_putstr_fd("An unknow error occured...", 2);
		return (EXIT_FAILURE);
	}
	if (graphic_mode) {
		mlx_data = init_mlx(board);
		mlx_mouse_hook(mlx_data->win, mlx_mouse_hook_detect, mlx_data);
		mlx_loop(mlx_data->mlx);
		mlx_destroy_image(mlx_data->mlx, mlx_data->img.ptr);
		mlx_destroy_window(mlx_data->mlx, mlx_data->win);
		free_board(mlx_data->board);
		free(mlx_data);
	} else
		game(board);
	return (EXIT_SUCCESS);
}
