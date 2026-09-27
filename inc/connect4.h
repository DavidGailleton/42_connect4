#ifndef CONNECT4
# define CONNECT4

# include "libft.h"
# include <stdlib.h>
# include <time.h>

# define COLOR_RESET "\033[0m"
# define COLOR_BOLD "\033[1m"
# define COLOR_DIM "\033[2m"
# define COLOR_ITALIC "\033[3m"
# define COLOR_RED "\033[31m"
# define COLOR_GREEN "\033[32m"
# define COLOR_YELLOW "\033[33m"
# define COLOR_BLUE "\033[34m"
# define COLOR_PINK "\033[35m"
# define COLOR_CYAN "\033[36m"

// Error cods
// Parsing
# define INVALID_NB_ARGS 1
# define INVALID_ROW_LEN 2
# define INVALID_COLUMN_LEN 3
# define INVALID_INT_ARGS 4

# define MCTS_UCB1_CONST 2
# define TIME_TO_SIMULATE 5
# define MAXSIZE_MINIMAX 30

typedef struct s_board {
	unsigned int size_x;
	unsigned int size_y;
	unsigned char **array;
} t_board;

typedef struct	s_tree
{
	long int		column;
	unsigned int	visits;
	unsigned int	victories;
	struct s_tree**	children;
}				t_tree;

typedef struct	s_stat
{
	unsigned int	victories;
	unsigned int	visits;
}				t_stat;

long int		mcts_choose_column(t_board *board);
unsigned int	pseudo_ln(unsigned int n);
unsigned int	select_col_ab(t_board *board, unsigned char piece);
int				check_args(int ac, char *av[]);
int				is_overflow_underflow(char *s_int);
unsigned char	end_game(t_board *board, unsigned int last_column);
t_board*		copy_board(t_board* board);
t_board*		init_board(int size_x, int size_y);
void			free_board(t_board* board);
void			free_children(t_tree* node, t_board* board);
void			free_tree(t_tree* node, t_board* board);
void			game(int size_x, int size_y);
void			play_token(t_board *board, unsigned int column, unsigned char player);
void			print_board(t_board *board);
void			print_tree(t_tree* node, int depth, t_board* board);

#endif // !CONNECT4
