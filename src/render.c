#include "../include/functions.h"
#include "../minilibx-linux/mlx.h"

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void draw_dot(int *data, size_t size_x, size_t size_y, size_t x, size_t y, int color)
{
	size_t index = y * size_x + x;
	if (index < size_x * size_y)
		data[index] = color;
}

t_dot isometric(t_dot *dot, t_rotation rotation)
{
	t_dot rotated_dot = rotate(*dot, rotation);
	t_dot new_dot = {
		.x = (rotated_dot.x - rotated_dot.y) * cos(30 * M_PI / 180),
		.y = -rotated_dot.z + (rotated_dot.x + rotated_dot.y) * sin(30 * M_PI / 180),
		.color = rotated_dot.color};
	return new_dot;
}

void render(t_dot *map, t_rotation rotation, size_t size_x, size_t size_y, int *data)
{
	t_dot delta = {
		.x = size_x / 2,
		.y = size_y / 2};
	t_dot scale = {
		.x = 1,
		.y = 1};

	for (t_dot *dot = map; dot; dot = dot->next)
	{
		t_dot iso_dot = isometric(dot, rotation);
		draw_dot(data, size_x, size_y, iso_dot.x * scale.x + delta.x, iso_dot.y * scale.y + delta.y, iso_dot.color);
	}
}

void window(t_dot *map)
{
	int size_x = 1200, size_y = 900;
	int bpp = 32, size_line = size_x * sizeof(int), endian = 0;

	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, size_x, size_y, "fdf");

	t_rotation rotation = {
		.x = 0,
		.y = 0,
		.z = 0};

	while (true)
	{
		void *img = mlx_new_image(mlx, size_x, size_y);
		int *data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
		render(map, rotation, size_x, size_y, data);
		mlx_put_image_to_window(mlx, win, img, 0, 0);
		mlx_destroy_image(mlx, img);

		rotation.x += 0.005;
		rotation.y += 0.005;
		rotation.z += 0.01;
	}
}