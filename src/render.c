#include "../include/functions.h"

#include "../minilibx-linux/mlx.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

t_dot isometric(t_dot dot, t_dot delta, t_dot scale)
{
	t_dot new = {
		.x = (dot.x - dot.y) * cos(30 * M_PI / 180),
		.y = (dot.x + dot.y) * sin(30 * M_PI / 180) - dot.z,
		.z = dot.z};
	new.x = new.x *scale.x + delta.x;
	new.y = new.y *scale.y + delta.y;
	new.z = new.z *scale.z + delta.z;
	return new;
}

void draw_dot(t_dot dot, int *data, size_t size_x, size_t size_y)
{
	size_t index = dot.y * size_x + dot.x;
	if (index < size_x * size_y)
		data[index] = 0x00FFFFFF;
}

void draw_line(t_dot dot1, t_dot dot2, int *data, size_t size_x, size_t size_y)
{
	bool using_x = labs(dot2.x - dot1.x) > labs(dot2.y - dot1.y);
	if ((using_x && dot1.x > dot2.x) || (!using_x && dot1.y > dot2.y)) 
		return draw_line(dot2, dot1, data, size_x, size_y);

	if (using_x)
	{
		for (ssize_t x = dot1.x; x <= dot2.x; x++)
			if (dot1.x != dot2.x)
				draw_dot((t_dot){x, dot1.y + (dot2.y - dot1.y) * (x - dot1.x) / (dot2.x - dot1.x), 0}, data, size_x, size_y);
	}
	else
		for (ssize_t y = dot1.y; y <= dot2.y; y++)
			if (dot1.y != dot2.y)
				draw_dot((t_dot){dot1.x + (dot2.x - dot1.x) * (y - dot1.y) / (dot2.y - dot1.y), y, 0}, data, size_x, size_y);
}

void render(t_map map, size_t size_x, size_t size_y, int *data)
{
	t_dot delta = {
		.x = size_x / 2,
		.y = size_y / 2};
	t_dot scale = {
		.x = size_x / map.width / 4,
		.y = size_y / map.height / 4,
		.z = 1};

	for (size_t y = 0; y < map.height; y++)
		for (size_t x = 0; x < map.width; x++)
		{
			t_dot dot = isometric((t_dot){x, y, map.data[y * map.width + x]}, delta, scale);
			size_t index = dot.y * size_x + dot.x;
			if (index < size_x * size_y)
				data[index] = 0xFFFFFF;
			if (x != 0)
				draw_line(dot, isometric((t_dot){x - 1, y, map.data[y * map.width + x - 1]}, delta, scale), data, size_x, size_y);
			if (y != 0)
				draw_line(dot, isometric((t_dot){x, y - 1, map.data[(y - 1) * map.width + x]}, delta, scale), data, size_x, size_y);
			if (x != map.width - 1)
				draw_line(dot, isometric((t_dot){x + 1, y, map.data[y * map.width + x + 1]}, delta, scale), data, size_x, size_y);
			if (y != map.height - 1)
				draw_line(dot, isometric((t_dot){x, y + 1, map.data[(y + 1) * map.width + x]}, delta, scale), data, size_x, size_y);
		}
}

void window(t_map map)
{
	int size_x = 640, size_y = 480;
	int bpp = 32, size_line = size_x * sizeof(int), endian = 0;

	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, size_x, size_y, "fdf");

	void *img = mlx_new_image(mlx, size_x, size_y);
	int *data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);

	render(map, size_x, size_y, data);

	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_destroy_image(mlx, img);
	mlx_loop(mlx);
}