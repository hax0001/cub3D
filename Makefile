# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror 

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =  get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		gar_co/gar_co.c \
		cub3d.c \

OBJS = $(SRCS:.c=.o)


# **************************************************************************** #
#                                 MAKE RULES                                   #
# **************************************************************************** #

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

# **************************************************************************** #
#                              ADDITIONAL RULES                                #
# **************************************************************************** #

.PHONY: all clean fclean re

.SECONDARY: