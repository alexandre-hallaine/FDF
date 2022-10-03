#include "functions.h"

#include <string.h>
#include <stdlib.h>

char *generate_title(t_option option)
{
	char title[1 << 8] = {0};
	strcat(title, "FDF");
	if (!option.isLine)
		strcat(title, " (Dot)");
	if (option.isColor)
		strcat(title, " (Color)");
	return strdup(title);
}

t_window generate_window(t_option option)
{
	int width = 1200, height = 900;
	char *title = generate_title(option);
	mlx_t *mlx = mlx_init(width, height, title, false);
	free(title);

	if (!mlx)
		return (t_window){0};

	{
		int screen_width, screen_height;
		mlx_get_monitor_size(0, &screen_width, &screen_height);
		width = screen_width * 0.8;
		height = screen_height * 0.8;
		mlx_set_window_size(mlx, width, height);
		mlx_set_window_pos(mlx, (screen_width - width) / 2, (screen_height - height) / 2);
	}

	return (t_window){
		.size = (t_size){width, height},
		.pointer = mlx,
	};
}

void usage(mlx_t *mlx)
{
	char *str = "Move: Mouse, Zoom: Scroll, Rotate: Arrows, Mode: Space, Color: C, Reset: R, Quit: Esc";
	mlx_image_t *img = mlx_put_string(mlx, str, 0, 0);
	mlx_image_to_window(mlx, img, 0, 0);
}

void start(t_fdf fdf)
{
	usage(fdf.window.pointer);
	mlx_set_cursor(fdf.window.pointer, mlx_create_std_cursor(MLX_CURSOR_HAND));

	mlx_key_hook(fdf.window.pointer, key_hook, &fdf);
	mlx_scroll_hook(fdf.window.pointer, scroll_hook, &fdf);
	mlx_cursor_hook(fdf.window.pointer, cursor_hook, &fdf);
	mlx_loop_hook(fdf.window.pointer, loop_hook, &fdf);
	mlx_loop(fdf.window.pointer);
}
