/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:01:39 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 16:01:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include "minilibx-linux/mlx.h"
# include "../get_next_line/get_next_line.h"

#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307
#define TILE_SIZE 32

typedef struct s_map {
	int width;
	int height;
	char **map;
	int player_x;
	int player_y;
}	t_map;

typedef struct s_vars {
	int player_x;
	int player_y;
	int moves;
}	t_vars;

typedef struct s_game {
	t_map map;
	t_vars vars;
	int total_collectibles;
	int collected;
	void *mlx;
	void *win;
	void *img_door;
	void *img_background;
	void *img_wall;
	void *img_player_up;
	void *img_player_down;
	void *img_player_left;
	void *img_player_right;
	void *img_player;
	void *img_collectible;
	int img_width;
	int img_height;
	int mov;
}	t_game;

void	up(t_game *game);
void	down(t_game *game);
void	left(t_game *game);
void	right(t_game *game);
void	exit_game(t_game *game);
void	flood_fill(t_map *map, int x, int y);
int		is_path_valid(t_map *map, int start_x, int start_y);
void	move_player(t_game *game, int new_x, int new_y, void *player_img);
void	free_map(t_map *map);
void	render_map(t_game *game, t_map *map);
void	print_map(t_map *map);
void	parse_map(t_map *map, const char *file);
char	*find_starting_position(t_map *map);
void	find_player_position(t_map *map, t_vars *vars);
void	update_player_position(t_game *game, int new_x, int new_y, int keycode);
int		count_collectibles(t_map *map);
int		key_hook(int keycode, t_game *game);
void	setup_hooks(t_game *game);
int read_map(char *filename, t_map *map );
void	free_map(t_map *map);
int		mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int		mlx_loop(void *mlx);
void	free_game(t_game *game);
void	init_game(t_game *game);
int check_map(t_game *game, t_map *map);
int		count_exits(t_game *game);
int count_collectibles__(t_game *game);
void	free_vars(t_vars *vars);
//
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlen(char const *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
//
#endif