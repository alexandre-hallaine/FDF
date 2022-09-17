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

typedef struct
{
	size_t width;
	size_t height;
} t_display;

typedef struct
{
	t_dot *map;
	float scale;

	t_display display;

	void *mlx;
	void *win;

	t_dot rotation;
} t_fdf;
#endif
