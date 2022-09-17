#include "../include/functions.h"
#include "../minilibx-linux/mlx.h"

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

t_dot stack_dot(t_dot *dot)
{
	t_dot new_dot = {
		.x = dot->x,
		.y = dot->y,
		.z = dot->z,
		.color = dot->color,
		.next = NULL};
	return new_dot;
}

void isometri(t_dot *dot)
{
	float x = dot->x;
	float y = dot->y;
	dot->x = (x - y) * cos(30 * M_PI / 180);
	dot->y = -dot->z + (x + y) * sin(30 * M_PI / 180);
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
		t_dot tmp = stack_dot(dot);
		rotate(&tmp, rotation);
		isometri(&tmp);
		draw_dot(data, size_x, size_y, tmp.x * scale.x + delta.x, tmp.y * scale.y + delta.y, tmp.color);
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