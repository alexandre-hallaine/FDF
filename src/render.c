#include "../include/functions.h"
#include "../minilibx-linux/mlx.h"

#include <stdio.h>
#include <math.h>

void draw_dot(int *data, size_t x, size_t y, size_t size_x, size_t size_y, int color)
{
	size_t index = y * size_x + x;
	if (index < size_x * size_y)
		data[index] = color;
}

t_dot isometric(t_dot *dot)
{
	t_dot new_dot = {
		.x = (dot->x - dot->y) * cos(30 * M_PI / 180),
		.y = (dot->x + dot->y) * sin(30 * M_PI / 180) - dot->z,
		.color = dot->color};
	return new_dot;
}

t_dot *find_dot(t_dot *map, size_t x, size_t y)
{
	for (t_dot *dot = map; dot != NULL; dot = dot->next)
		if (dot->x == x && dot->y == y)
			return dot;
	return NULL;
}

void render(t_dot *map, size_t size_x, size_t size_y, int *data)
{
	t_dot delta = {
		.x = size_x / 2,
		.y = size_y / 2};
	t_dot scale = {
		.x = 10,
		.y = 10};

	for (t_dot *tmp = map; tmp; tmp = tmp->next)
	{
		t_dot dot = isometric(tmp);
		draw_dot(data, dot.x * scale.x + delta.x, dot.y * scale.y + delta.y, size_x, size_y, dot.color);
	}
}

void window(t_dot *map)
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