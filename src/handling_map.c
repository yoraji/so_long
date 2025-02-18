#include "../so_long.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_map(const char *filename, t_map *map)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open map file");
        return 1;
    }
    int map_width = 0;
    int map_height = 0;
    calculate_map_dimensions(filename, &map_width, &map_height);

    map->map = malloc(map_height * sizeof(char *));
    if (!map->map) {
        perror("Failed to allocate memory for map");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < map_height; i++) {
        map->map[i] = malloc((map_width + 1) * sizeof(char));
        if (!map->map[i]) {
            perror("Failed to allocate memory for map line");
            free_map(map);
            fclose(file);
            return 1;
        }
        if (fgets(map->map[i], map_width + 1, file) == NULL) {
            perror("Failed to read map line");
            free_map(map);
            fclose(file);
            return 1;
        }
        fgetc(file);
    }
    fclose(file);
    map->width = map_width;
    map->height = map_height;
    return 0;
}

void calculate_map_dimensions(const char *file, int *width, int *height)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        exit(1);
    }

    char buffer[1024];
    int bytes_read;
    int line_length = 0;
    *width = 0;
    *height = 0;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        for (int i = 0; i < bytes_read; i++)
        {
            if (buffer[i] == '\n')
            {
                if (*width == 0)
                {
                    *width = line_length;
                }
                (*height)++;
                line_length = 0;
            }
            else
            {
                line_length++;
            }
        }
    }

    close(fd);
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
        printf("Read line: %s\n", line); // Debug print
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