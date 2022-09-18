#ifndef TYPES_H
#define TYPES_H

#include "MLX42/MLX42.h"

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
	t_dot offset;
	t_dot rotation;

	mlx_t *mlx;
	mlx_image_t *img;
} t_fdf;
#endif
