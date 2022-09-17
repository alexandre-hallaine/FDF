#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

void error(char *str);

t_dot *read_map(char *filename);

t_dot stack_dot(t_dot *dot);
t_dot *find_dot(t_dot *dot, float x, float y);

void apply_math(t_dot *dot, t_dot rotation, t_dot offset, float zoom);

void draw_pixel(int *data, size_t size_x, size_t size_y, size_t x, size_t y, int color);
void dda(int *data, size_t size_x, size_t size_y, t_dot *dot1, t_dot *dot2);

void window(t_dot *map);
#endif
