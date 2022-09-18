#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

void error(char *str);

float get_scale(t_dot *map, t_display display);
t_dot *read_map(char *filename);
free_map(t_dot *map);

t_dot stack_dot(t_dot *dot);
t_dot *find_dot(t_dot *dot, float x, float y);

void apply_math(t_dot *dot, t_dot rotation, t_dot offset, float zoom);

void dda(mlx_image_t *img, t_display display, t_dot *dot1, t_dot *dot2);

void loop(void *fdf);
#endif
