#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>
#include <sys/types.h>

typedef struct
{
	size_t width;
	size_t height;

	char *data;
} t_map;

typedef struct
{
	ssize_t x;
	ssize_t y;
	ssize_t z;
} t_dot;
#endif