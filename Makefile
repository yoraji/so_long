NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux -I./get_next_line
MLX_PATH = ./minilibx-linux
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11
GNL_PATH = ./get_next_line
SRCS =	src/main.c src/flood_fill.c src/left_right.c src/up_down.c \
		src/update_player_pos.c src/for_free.c src/handling_map.c src/ft_strchr.c src/ft_strdup.c src/ft_strjoin.c src/ft_strlen.c src/ft_substr.c \
		src/utils_00.c ./src/path_utils.c ./src/ft_memcpy.c ./src/mlx.c $(GNL_PATH)/get_next_line.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
