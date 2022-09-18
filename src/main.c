#include "functions.h"

void key_hook(mlx_key_data_t keydata, void *fdf)
{
	if (keydata.action != MLX_PRESS)
		return;

	t_fdf *fdf_ptr = (t_fdf *)fdf;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf_ptr->mlx);
	if (keydata.key == MLX_KEY_L)
	{
		fdf_ptr->lines = !fdf_ptr->lines;

		if (fdf_ptr->lines)
			mlx_set_window_title(fdf_ptr->mlx, "FDF - Lines");
		else
			mlx_set_window_title(fdf_ptr->mlx, "FDF - Points");

		if (fdf_ptr->img)
		{
			mlx_delete_image(fdf_ptr->mlx, fdf_ptr->img);
			fdf_ptr->img = NULL;
		}
	}
}

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
		.lines = true,

		.mlx = mlx_init(display.width, display.height, "FDF - Lines", false),
	};

	mlx_key_hook(fdf.mlx, key_hook, &fdf);
	mlx_loop_hook(fdf.mlx, loop, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free_map(map);
	return 0;
}
