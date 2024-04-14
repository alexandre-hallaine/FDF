#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

// main.c
void error(int code, char *str, ...);

float scale(t_position delta[2], t_size window);
t_map load_map(char *filename);
void free_dots(t_dot *first);

char *generate_title(t_option option);
t_window generate_window(t_option option);
void start(t_fdf fdf);

void scroll_hook(double xdelta, double ydelta, void *param);
void cursor_hook(double xpos, double ypos, void *param);
void key_hook(mlx_key_data_t keydata, void *param);
void loop_hook(void *param);

void render(t_fdf *fdf);

bool is_in_window(t_position position, t_window window);
void dda(t_dot dot[2], t_window window);
#endif
