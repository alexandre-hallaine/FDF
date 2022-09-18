#include "functions.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		error("Usage: ./main <filename>");

	t_display display = {
		.width = 1200,
		.height = 900,
	};

	t_dot *map = read_map(argv[1]);
	t_fdf fdf = {
		.map = map,
		.scale = get_scale(map, display),

		.display = display,
		.offset = {.x = display.width / 2,
				   .y = display.height / 2},
		.rotation = {.x = 0,
					 .y = 0,
					 .z = 0},

		.mlx = mlx_init(display.width, display.height, "FDF", false),
	};

	mlx_loop_hook(fdf.mlx, loop, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free_map(map);
	return 0;
}
