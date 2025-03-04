/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:00:48 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 16:00:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	flood_fill(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0
		|| y >= map->height || map->map[y][x] == '1' || map->map[y][x] == 'F')
		return ;
	map->map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void print_map(t_map *map) {
    if (!map || !map->map) {
        printf("Map is not initialized\n");
        return;
    }

    for (int y = 0; y < map->height; y++) {
        if (map->map[y]) {
            printf("%s\n", map->map[y]);
        } else {
            printf("Row %d is not initialized\n", y);
        }
    }
}

int count_exits(t_game *game) {
	int count = 0;
	for (int y = 0; y < game->map.height; y++)
	{
		for (int x = 0; x < game->map.width; x++)
		{
			if (game->map.map[y][x] == 'E')
				count++;
		}
	}
	return count;
}
