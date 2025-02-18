#include "../so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_map(t_map *map)
{
    for (int i = 0; i < map->height; i++)
    {
        free(map->map[i]);
    }
    free(map->map);
}

void print_map(t_map *map)
{
	printf("Map width: %d, height: %d\n", map->width, map->height);
    for (int i = 0; i < map->height; i++)
    {
        printf("%s", map->map[i]);
    }
	printf("\n");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    t_map map;
    parse_map(&map, argv[1]);
    printf("Parsed map:\n");
	if (read_map(argv[1], &map) != 0)
    {
        fprintf(stderr, "Failed to read map\n");
        return 1;
    }
    print_map(&map);

    char *ptr = find_starting_position(&map);
    if (ptr == NULL)
    {
        printf("No starting position found.\n");
        free_map(&map);
        return 1;
    }
    int start_x = map.player_x;
    int start_y = map.player_y;
    printf("Starting position: %d, %d\n", start_x, start_y);
    if (map.map[start_y][start_x] == 'E')
        printf("Starting position is an exit.\n");
    if (is_path_valid(&map, start_x, start_y))
        printf("The path is valid.\n");
    else
        printf("The path is not valid.\n");
    free_map(&map);
    return 0;
}