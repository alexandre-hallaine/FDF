#include "../include/types.h"

#include "../minilibx-linux/mlx.h"

#include <unistd.h>
#include <stdlib.h>

void render(t_map map)
{
	int sizex = 640, sizey = 480;
	int bpp = 32, size_line = sizex * sizeof(int), endian = 0;

	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, sizex, sizey, "fdf");

	void *img = mlx_new_image(mlx, sizex, sizey);
	int *data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);

	for (int y = 0; y < sizey; y++)
		for (int x = 0; x < sizex; x++)
			data[x + y * sizex] = rand() % 0xFFFFFF;

	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_destroy_image(mlx, img);
	mlx_loop(mlx);

	(void)map;
}