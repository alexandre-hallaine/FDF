#include "../include/types.h"
#include "../minilibx-linux/mlx.h"

#define WIDTH 1200
#define HEIGHT 900

float center_map(t_dot *map)
{
	float x_min = 0, x_max = 0;
	float y_min = 0, y_max = 0;
	float z_min = 0, z_max = 0;

	for (t_dot *dot = map; dot; dot = dot->next)
	{
		if (dot->x < x_min)
			x_min = dot->x;
		if (dot->x > x_max)
			x_max = dot->x;
		if (dot->y < y_min)
			y_min = dot->y;
		if (dot->y > y_max)
			y_max = dot->y;
		if (dot->z < z_min)
			z_min = dot->z;
		if (dot->z > z_max)
			z_max = dot->z;
	}

	float x_center = (x_max - x_min) / 2;
	float y_center = (y_max - y_min) / 2;
	float z_center = (z_max - z_min) / 2;

	for (t_dot *dot = map; dot; dot = dot->next)
	{
		dot->x -= x_center;
		dot->y -= y_center;
		dot->z -= z_center;
	}

	float scale_x = WIDTH / (x_max - x_min);
	float scale_y = HEIGHT / (y_max - y_min);
	float scale = scale_x < scale_y ? scale_x : scale_y;
	return scale / 2;
}

t_fdf init(t_dot *map)
{
	float scale = center_map(map);
	void *mlx = mlx_init();

	t_fdf fdf = {
		.map = map,
		.scale = scale,
		.display = {
			.width = WIDTH,
			.height = HEIGHT,
		},
		.mlx = mlx,
		.win = mlx_new_window(mlx, WIDTH, HEIGHT, "FDF"),
		.rotation = {
			.x = 0,
			.y = 0,
			.z = 0,
		},
	};
	return fdf;
}
