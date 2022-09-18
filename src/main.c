#include "functions.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		error("Usage: ./main <filename>");
	t_dot *map = read_map(argv[1]);
	t_fdf fdf = init(map);

	mlx_loop_hook(fdf.mlx, loop, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return 0;
}
