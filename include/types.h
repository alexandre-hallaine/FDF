#pragma once

#include "MLX42/MLX42.h"

#include <stddef.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct s_dot {
    int height;
    int color;

    double position[2];
} t_dot;

typedef struct s_map {
    unsigned short width;
    unsigned short height;
    t_dot *dots;
} t_map;

typedef struct s_options {
    short offset[2];
    float scale;
} t_options;

typedef struct s_data {
    t_map map;
    t_options options;
} t_data;

extern t_data g_data;
