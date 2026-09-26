#include <stdlib.h>
#include <unistd.h>

#include "connect4.h"
#include "libft.h"

int main(int argc, char *argv[]) {
	int parse_result = check_args(argc, argv);

	switch (parse_result) {
	case INVALID_NB_ARGS:
		write(2, "2 args is expected: ./connect4 {nb_row} {nb_collumn}\n", 53);
		return (EXIT_FAILURE);
	case INVALID_INT_ARGS:
		write(2, "Args should only be valid integer:\nExample: ./connect4 8 10\n",
					60);
		return (EXIT_FAILURE);
	case INVALID_ROW_LEN:
		write(2, "Row arg should be minimum 6\n", 28);
		return (EXIT_FAILURE);
	case INVALID_COLUMN_LEN:
		write(2, "Column arg should be minimum 6\n", 31);
		return (EXIT_FAILURE);
	default:
		break;
	}
	game(ft_atoi(argv[2]), ft_atoi(argv[1]));
	return (EXIT_SUCCESS);
}
