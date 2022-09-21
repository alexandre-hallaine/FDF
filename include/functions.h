#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

t_dot stack_dot(t_dot *dot);
t_dot *find_dot(t_dot *dot, float x, float y);

void dda(mlx_image_t *img, t_display display, t_dot *dot1, t_dot *dot2);

float get_scale(t_dot *map, t_display display);
t_dot *read_map(char *filename);
void free_map(t_dot *map);

void render(t_fdf *fdf);

void scroll_hook(double xdelta, double ydelta, void* param);
void cursor_hook(double xpos, double ypos, void* param);
void key_hook(mlx_key_data_t keydata, void* param);
void loop(void *fdf);

void error(char *str);
#endif
