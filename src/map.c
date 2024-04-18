#include "functions.h"

#include "get_next_line.h"

#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>

int extract_value(char **str) {
    int value = 0;
    char *base = "0123456789";

    for (char c = **str; c; c = *(++*str))
        if (c == 'x')
            base = "0123456789abcdef";
        else {
            char *ptr = strchr(base, c);
            if (!ptr) break;

            value *= strlen(base);
            value += ptr - base;
        }

    return value;
}

t_map load_map(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) error(2, "Failed to open file %s\n", filename);

    char *lines[USHRT_MAX];
    unsigned short height = 0;
    unsigned short width = 0;

    while(height < USHRT_MAX) {
        char *line = get_next_line(fd);
        if (line == NULL) break;
        if (*line) lines[height++] = line;
        else free(line);
    }

    if (height == 0) error(2, "Empty file %s\n", filename);
    for (char *data = *lines; width < USHRT_MAX && data; width++, data = strchr(data, ' '))
        for (; *data == ' '; data++);

    t_dot *dots = malloc(sizeof(t_dot) * (width * height));
    if (!dots) error(2, "Failed to allocate memory\n");

    for (size_t i = 0; i < height; i++) {
        char *data = lines[i];
        for (size_t j = 0; j < width; j++) {
            for (; data && *data == ' '; data++);
            
            int height = extract_value(&data);

            int color = 0xFFFFFF;
            if (*data++ == ',')
                color = extract_value(&data);

            dots[i * width + j] = (t_dot) {height, color, {0, 0}};
        }
        free(lines[i]);
    }

    return (t_map) {width, height, dots};
}
