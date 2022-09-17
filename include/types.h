#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>
#include <sys/types.h>

typedef struct s_dot t_dot;

struct s_dot
{
	float x;
	float y;
	float z;
	int color;
	t_dot *next;
};

#endif