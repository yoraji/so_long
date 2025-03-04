/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:09:47 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 23:09:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// void parse_map(char *file)
// {
// 	int		fd;
// 	char	*line;
// 	int		ret;

// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		return (0);
// 	while ((ret = get_next_line(fd, &line)) > 0)
// 	{
// 		if (map->width == 0)
// 			map->width = ft_strlen(line);
// 		map->height++;
// 	}
// 	if (ret < 0)
// 		return (0);
// 	close(fd);
// }

void	move_player(int x, int y)
{
	if (map->map[player->y + y][player->x + x] == '1')
		return ;
	if (map->map[player->y + y][player->x + x] == 'C')
	{
		map->map[player->y + y][player->x + x] = 'P';
		map->map[player->y][player->x] = '0';
		player->x += x;
		player->y += y;
		player->collectibles++;
	}
	else if (map->map[player->y + y][player->x + x] == 'E')
	{
		if (player->collectibles == map->collectibles)
		{
			map->map[player->y + y][player->x + x] = 'P';
			map->map[player->y][player->x] = '0';
			player->x += x;
			player->y += y;
			exit(0);
		}
	}
	else
	{
		map->map[player->y + y][player->x + x] = 'P';
		map->map[player->y][player->x] = '0';
		player->x += x;
		player->y += y;
	}
}

void	check_win_condition(void)
{
	int	i;
	int	j;
	int	collectibles;

	i = 0;
	collectibles = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'C')
				collectibles++;
			j++;
		}
		i++;
	}
	if (collectibles == 0)
		exit(0);
}

int	cheack_exit(void)
{
	int	i;
	int	j;
	int	exit;

	i = 0;
	exit = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'E')
				exit++;
			j++;
		}
		i++;
	}
	if (exit != 1)
		return (1);
	return (0);
}