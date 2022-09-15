#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>

typedef struct
{
    size_t width;
    size_t height;

    char *data;
} t_map;
#endif