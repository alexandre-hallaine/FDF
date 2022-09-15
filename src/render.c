#include "../include/types.h"

#include "../minilibx-linux/mlx.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <math.h>

void draw_dot(t_map map, size_t size_x, size_t size_y, int *data)
{
	size_t scale = 10;

	for (size_t y = 0; y < map.height; y++)
		for (size_t x = 0; x < map.width; x++)
		{
			ssize_t new_x = (ssize_t)(x - y) * cos(30 * M_PI / 180);
			ssize_t new_y = (ssize_t)(x + y) * sin(30 * M_PI / 180) - map.data[y * map.width + x];
			size_t index = (size_y / 2 + new_y * scale) * size_x + (size_x / 2 + new_x * scale);
			if (index < size_x * size_y)
				data[index] = 0x00FFFFFF;
		}
}

void render(t_map map)
{
	int sizex = 640, sizey = 480;
	int bpp = 32, size_line = sizex * sizeof(int), endian = 0;

	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, sizex, sizey, "fdf");

	void *img = mlx_new_image(mlx, sizex, sizey);
	int *data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);

	draw_dot(map, sizex, sizey, data);

	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_destroy_image(mlx, img);
	mlx_loop(mlx);
}