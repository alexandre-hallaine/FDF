#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

void error(char *str);
t_dot *read_map(char *filename);
void window(t_dot *map);
#endif