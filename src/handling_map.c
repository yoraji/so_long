#include "../so_long.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_map(const char *filename, t_map *map) {
   FILE *file;

    file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    calculate_map_dimensions(filename, &map->width, &map->height);
	map->map = malloc(map->height * sizeof(char *));
    if (!map->map) {
        perror("Failed to allocate memory for map");
        fclose(file);
        return 0;
    }
    if (!map->map) {
        perror("Error allocating memory for map");
        fclose(file);
        return 0;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        map->map[i] = malloc(map->width + 1);
        if (!map->map[i]) {
            perror("Error allocating memory for map line");
			free_map(map);
            free(line);
            fclose(file);
            return 0;
        }
        strncpy(map->map[i], line, map->width);
        map->map[i][map->width] = '\0';
		if (!map->map[i]) {
            perror("Failed to allocate memory for map line");
            free_map(map);
            fclose(file);
            return 0;
        }
        i++;
    }
    free(line);
    fclose(file);
    // // Print the map for debugging
    // printf("Map width: %d, height: %d\n", map->width, map->height);
    // for (int j = 0; j < map->height; j++) {
    //     printf("Map line %d: %s\n", j, map->map[j]);
    // }
    return 1;
}

void calculate_map_dimensions(const char *filename, int *width, int *height) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    *width = 0;
    *height = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        if (read > *width) {
            *width = read;
        }
        (*height)++;
    }
    free(line);
    fclose(file);
}

char *find_starting_position(t_map *map)
{
    for (int y = 0; y < map->height; y++)
    {
        if (map->map[y] == NULL)
        {
            fprintf(stderr, "Error: Map row %d is NULL\n", y);
            continue;
        }

        for (int x = 0; x < map->width; x++)
        {
            printf("Checking position (%d, %d): %c\n", y, x, map->map[y][x]);
            if (map->map[y][x] == 'P')
            {
                map->player_x = x;
                map->player_y = y;
                return &map->map[y][x];
            }
        }
    }
    return NULL;
}

void parse_map(t_map *map, const char *file)
{
    int fd;
    char *line;
    int i = 0;

    calculate_map_dimensions(file, &map->width, &map->height);

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        exit(1);
    }

    map->map = malloc(sizeof(char *) * map->height);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Read line: %s\n", line);
        map->map[i] = malloc(map->width + 1);
        strcpy(map->map[i], line);
        free(line);
        i++;
    }

    close(fd);

    printf("Map width: %d, height: %d\n", map->width, map->height); // Debug print
    for (int j = 0; j < map->height; j++)
    {
        printf("Map line %d: %s\n", j, map->map[j]); // Debug print
    }
}