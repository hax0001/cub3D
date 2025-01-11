# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror 
MLX = libmlx_Linux.a  -lXext -lX11 -lm -lbsd

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =  get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		gar_co/gar_co.c \
		main.c \
		parse/parse_map.c \
		error/error.c \
		start_game/cub3d.c \
		ray_cast/cast_rays.c \

OBJS = $(SRCS:.c=.o)


# **************************************************************************** #
#                                 MAKE RULES                                   #
# **************************************************************************** #

all: display $(LIBFT) $(NAME)

display:
	@echo $(B)
	@echo "\033[1;31m                       _|         _|_|_|     _|_|_|  \033[0m"
	@echo "\033[1;31m   _|_|_|   _|    _|   _|_|_|           _|   _|    _|\033[0m"
	@echo "\033[1;33m _|         _|    _|   _|    _|     _|_|     _|    _|\033[0m"
	@echo "\033[1;33m _|         _|    _|   _|    _|         _|   _|    _|\033[0m"
	@echo "\033[1;34m   _|_|_|     _|_|_|   _|_|_|     _|_|_|     _|_|_|  \033[0m"
	@echo $(X)
	
$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

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