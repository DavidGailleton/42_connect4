#include "../inc/connect4.h"
#include "../libft/libft.h"
#include <limits.h>
#include <stddef.h>

int is_overflow_underflow(char *s_int) {
  char *s_int_max = ft_itoa(INT_MAX);
  char *s_int_min = ft_itoa(INT_MIN);

  size_t s_int_len = ft_strlen(s_int);

  if ((s_int[0] == '-' && (s_int_len > ft_strlen(s_int_min) ||
                           (s_int_len == ft_strlen(s_int_min) &&
                            ft_strncmp(s_int, s_int_min, s_int_len) > 0))) ||
      (s_int_len > ft_strlen(s_int_min) ||
       (s_int_len == ft_strlen(s_int_max) &&
        ft_strncmp(s_int, s_int_max, s_int_len) > 0)))
    return (1);
  return (0);
}

int is_invalid_int(char *s) {
  for (int i = 0; s[i]; i++) {
    if (i == 0 && s[i] == '-')
      continue;
    if (!ft_isdigit(s[i]))
      return (1);
  }
  return (0);
}

int check_args(int ac, char *av[]) {
  if (ac != 3)
    return (INVALID_NB_ARGS);
  if (is_invalid_int(av[1]) || is_invalid_int(av[2]) ||
      is_overflow_underflow(av[1]) || is_overflow_underflow(av[2]))
    return (INVALID_INT_ARGS);
  if (ft_atoi(av[1]) < 6)
    return (INVALID_ROW_LEN);
  if (ft_atoi(av[2]) < 7)
    return (INVALID_COLUMN_LEN);
  return (0);
}
