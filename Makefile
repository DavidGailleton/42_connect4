.PHONY: all clean fclean re debug force

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD
CFLAGS_DEBUG = -Wall -Wextra -MMD -g3 -D DEBUG=1

NAME = connect4
P_SRC = src/
P_OBJ = .obj/
P_INC = inc/
P_LIBFT = libft/

SRC	=	main.c 		\
		ai.c		\
		board.c		\
		game.c		\
		parsing.c

SRCS = $(addprefix $(P_SRC), $(SRC))
OBJS = $(patsubst $(P_SRC)%.c,$(P_OBJ)%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)
LIBFT = $(P_LIBFT)libft.a
LIBS = -L$(P_LIBFT) -lft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(P_OBJ)%.o: $(P_SRC)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(P_INC) -I$(P_LIBFT) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(P_LIBFT)

clean:
	rm -rf $(P_OBJ)
	$(MAKE) -C $(P_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(P_LIBFT) fclean

re: fclean all

debug:
	$(MAKE) CFLAGS="$(CFLAGS_DEBUG)" all

-include $(DEPS)

.SILENT:
