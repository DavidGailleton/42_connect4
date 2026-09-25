#include "../inc/connect4.h"
#include "../libft/libft.h"

int is_only_digits(char *s) {
  for (int i = 0; s[i]; i++) {
    if (!ft_isdigit(s[i]))
      return (1);
  }
  return (0);
}

int check_args(int ac, char *av[]) {
  if (ac != 3)
    return (INVALID_NB_ARGS);
  if (is_only_digits(av[1]) || is_only_digits(av[2]))
    return (INVALID_INT_ARGS);
  if (ft_atoi(av[1]) < 6)
    return (INVALID_ROW_LEN);
  if (ft_atoi(av[2]) < 7)
    return (INVALID_COLUMN_LEN);
  return (0);
}
