#include "functions.h"

#include "get_next_line.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_map_line
{
	t_dot *line;
	struct s_map_line *next;
} t_map_line;

t_map_line *line_next(int fd) {
    char *line = get_next_line(fd);
    t_map_line *new = malloc(sizeof(t_map_line));

    size_t width = 0;
    if (line && *line)
        for (char *tmp = line; tmp; tmp = ft_strchr(tmp, ' '), width++)
            for (; *tmp == ' '; tmp++);

    if (new) {
        new->line = NULL;
        new->next = NULL;
        
        if (width)
            new->line = malloc(sizeof(t_dot) * (width + 1));
        if (new->line)
            new->line[width].color = -1;
        else {
            free(new);
            new = NULL;
        }
    }

    if (new) {
        char *data = line;
        for (size_t i = 0; i < width; i++) {
            size_t height = atoi(data);
            new->line[i] = (t_dot) {height, 0xFF};

            data = ft_strchr(data, ' ');
            for (; data && *data == ' '; data++);
        }
    }
    
    if (line) free(line);
    return new;
}

void load_map(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        error(1, "Failed to open file %s\n", filename);

    size_t width = 0;
    t_map_line *line_first = line_next(fd);
    for (t_map_line *tmp = line_first; tmp; tmp = tmp->next, width++)
        tmp->next = line_next(fd);

    g_data.dots = malloc(sizeof(t_dot *) * (width + 1));
    if (g_data.dots) {
        g_data.dots[width] = NULL;
        for (size_t i = 0; i < width; i++) {
            g_data.dots[i] = line_first->line;

            t_map_line *tmp = line_first;
            line_first = line_first->next;
            free(tmp);
        }
    }
}
