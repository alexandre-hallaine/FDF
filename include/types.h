#pragma once

#include "MLX42/MLX42.h"

#include <stddef.h>

typedef struct s_dot
{
	size_t height;
	int color;
}  t_dot;

typedef struct s_data
{
	t_dot **dots;
} t_data;

extern t_data g_data;
