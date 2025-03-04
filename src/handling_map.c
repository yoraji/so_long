/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:30:25 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 16:30:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int read_map(char *filename, t_map *map ) {
	int fd;
	char *line;
	int i = 0;

	printf("Reading map\n");
	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "Failed to open file\n");
		return 0;
	}

	map->height = 0;
	map->width = 0;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Read line: %s", line);
		if (map->width == 0)
			map->width = strlen(line);
		map->height++;
		free(line);
	}
	close(fd);
	printf("Map dimensions: width=%d, height=%d\n", map->width, map->height);
	map->map = malloc(map->height * sizeof(char *));
	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		free(map->map);
		return 0;
	}
	while ((line = get_next_line(fd)) != NULL) {
		map->map[i] = malloc(map->width + 1);
		if (!map->map[i]) {
			free_map(map);
			free(line);
			close(fd);
			return 0;
		}
		strncpy(map->map[i], line, map->width);
		map->map[i][map->width] = '\0';
		free(line);
		i++;
	}
	close(fd);
	return 1;
}
//???
// void	calculate_map_dimensions(const char *filename, int *width, int *height) {
// 	FILE *file = fopen(filename, "r");
// 	if (!file) {
// 		perror("Error opening file");
// 		return ;
// 	}
// 	char *line = NULL;
// 	size_t len = 0;
// 	ssize_t read;
// 	*width = 0;
// 	*height = 0;
// 	while ((read = getline(&line, &len, file)) != -1) {
// 		if (read > *width)
// 			*width = read;
// 		(*height)++;
// 	}
// 	free(line);
// 	fclose(file);
// }

char	*find_starting_position(t_map *map)
{
	for (int y = 0; y < map->height; y++)
	{
		if (map->map[y] == NULL)
			continue;
		for (int x = 0; x < map->width; x++)
		{
			if (map->map[y][x] == 'P')
			{
				map->player_x = x;
				map->player_y = y;
				return (&map->map[y][x]);
			}
		}
	}
	return (NULL);
}

void parse_map(t_map *map, const char *file)
{
	int fd;
	char *line;
	int i = 0;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(1);
	map->map = malloc(sizeof(char *) * map->height);
	while ((line = get_next_line(fd)) != NULL)
	{
		map->map[i] = malloc(map->width + 1);
		if (map->map[i] == NULL)
		{
			free(line);
			close(fd);
			exit(1);
		}
		strcpy(map->map[i], line);
		free(line);
		i++;
	}

	close(fd);
}