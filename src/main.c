#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

void error(char *str)
{
	dprintf(2, "%s\n", str);
	exit(1);
}

void usage(mlx_t *mlx)
{
	char *str = "Rotate: WS/AD/QE | Move: Arrows | Zoom: +/- | Switch: Space | Color: C | Reset: R | Exit: Esc";
	mlx_image_t *img = mlx_put_string(mlx, str, 0, 0);
	mlx_image_to_window(mlx, img, 0, 0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		error("Usage: ./main <filename>");

	t_dot *map = read_map(argv[1]);
	t_display display = {
		.width = 1200,
		.height = 900,
	};
	t_fdf fdf = {
		.map = map,
		.scale = get_scale(map, display),

		.display = display,
		.offset = {.x = display.width / 2,
				   .y = display.height / 2},
		.rotation = {.x = 0,
					 .y = 0,
					 .z = 0},
		.lines = true,

		.mlx = mlx_init(display.width, display.height, "FDF - Lines", false),
	};

	usage(fdf.mlx);
	mlx_key_hook(fdf.mlx, key_hook, &fdf);
	mlx_loop_hook(fdf.mlx, loop, &fdf);
	mlx_loop(fdf.mlx);

	mlx_terminate(fdf.mlx);
	free_map(map);
	return 0;
}
