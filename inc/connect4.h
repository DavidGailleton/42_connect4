#ifndef CONNECT4
#define CONNECT4

#include "libft.h"
#include <stdlib.h>
#include <time.h>

#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_DIM "\033[2m"
#define COLOR_ITALIC "\033[3m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_PINK "\033[35m"
#define COLOR_CYAN "\033[36m"

// Error cods
// Parsing
#define INVALID_NB_ARGS 1
#define INVALID_ROW_LEN 2
#define INVALID_COLUMN_LEN 3
#define INVALID_INT_ARGS 4

#define MCTS_UCB1_CONST 5

typedef struct s_board {
	unsigned int size_x;
	unsigned int size_y;
	unsigned char **array;
} t_board;

unsigned int ai_choose_column(t_board *board);
int check_args(int ac, char *av[]);
int is_overflow_underflow(char *s_int);
t_board *init_board(int size_x, int size_y);
void game(int size_x, int size_y);
void print_board(t_board *board);

#endif // !CONNECT4
