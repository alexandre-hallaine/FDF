#ifndef TYPES_H
#define TYPES_H

#include "MLX42/MLX42.h"

#include <stddef.h>

typedef struct
{
	float x;
	float y;
	float z;
} t_position;

typedef struct
{
	size_t width;
	size_t height;
} t_size;

typedef struct s_dot t_dot;

struct s_dot
{
	t_position position;
	int color;

	t_dot *next;
	t_dot *pixel;
};

typedef struct
{
	t_dot *first;

	t_position min;
	t_position max;
} t_map;

typedef struct
{
	t_size size;

	mlx_t *pointer;
	mlx_image_t *image;
} t_window;

typedef struct
{
	t_position offset;
	t_position rotation;
	float scale;

	bool isLine;
	bool isColor;
} t_option;

typedef struct
{
	t_map map;
	t_window window;

	t_option option;
} t_fdf;
#endif
