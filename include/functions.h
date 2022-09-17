#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

void error(char *str);
t_dot *read_map(char *filename);
t_dot rotate(t_dot dot, t_rotation rotation);
void window(t_dot *map);
#endif