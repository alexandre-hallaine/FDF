#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

void error(char *str);

t_dot *read_map(char *filename);

void rotate(t_dot *dot, t_rotation rotation);

void draw_dot(int *data, size_t size_x, size_t size_y, size_t x, size_t y, int color);

void window(t_dot *map);
#endif