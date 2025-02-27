# Variables
NAME = so_long
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I./minilibx-linux -I./get_next_line -I./libft
MLX_PATH = ./minilibx-linux
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11
GNL_PATH = ./get_next_line
LIBFT_PATH = ./libft
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft
SRCS = src/main.c src/flood_fill.c src/left_right.c src/up_down.c src/handling_map.c ./src/path_utils.c ./src/mlx.c $(GNL_PATH)/get_next_line.c
OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all