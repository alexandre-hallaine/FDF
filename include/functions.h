#pragma once

#include "types.h"

// main.c
void error(int code, char *str, ...);

// map.c
t_map load_map(char *filename);

// loop.c
void loop(void *param);

// hook.c
void scroll(double xdelta, double ydelta, void *param);

void cursor(double xpos, double ypos, void *param);

void key(mlx_key_data_t keydata, void *param);
