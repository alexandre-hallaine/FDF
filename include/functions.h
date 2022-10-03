#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

void error(char *str);

float scale(t_dot *map, t_size window);
t_dot *load_map(char *filename);
void free_map(t_dot *current);

char *generate_title(t_option option);
t_window generate_window(t_option option);
void start(t_fdf fdf);

void scroll_hook(double xdelta, double ydelta, void *param);
void cursor_hook(double xpos, double ypos, void *param);
void key_hook(mlx_key_data_t keydata, void *param);
void loop_hook(void *param);

void render(t_fdf *fdf);

bool is_in_window(t_position position, t_window window);
void dda(t_window window, t_dot dot[2]);
#endif
