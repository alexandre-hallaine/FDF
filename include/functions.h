#pragma once

#include "types.h"

// main.c
void error(int code, char *str, ...);

// map.c
void load_map(char *filename);

// loop.c
void loop(void *param);

// hook.c
void scroll(double xdelta, double ydelta, mlx_t *mlx);
void cursor(double xpos, double ypos, mlx_t* mlx);
