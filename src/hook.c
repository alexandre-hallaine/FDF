#include "functions.h"

#include <stdlib.h>

void scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fdf *fdf = (t_fdf *)param;

	(void)xdelta;
	float focator = 1 + ydelta / 10;
	if (fdf->option.scale * focator < .01 || fdf->option.scale * focator > 1000)
		return;

	int mouse_x, mouse_y;
	mlx_get_mouse_pos(fdf->window.pointer, &mouse_x, &mouse_y);

	fdf->option.scale *= focator;
	fdf->option.offset.x = mouse_x - (mouse_x - fdf->option.offset.x) * focator;
	fdf->option.offset.y = mouse_y - (mouse_y - fdf->option.offset.y) * focator;
}

void cursor_hook(double xpos, double ypos, void *param)
{
	static double last_xpos = 0, last_ypos = 0;

	t_fdf *fdf = (t_fdf *)param;
	if (mlx_is_mouse_down(fdf->window.pointer, MLX_MOUSE_BUTTON_LEFT))
	{
		fdf->option.offset.x += xpos - last_xpos;
		fdf->option.offset.y += ypos - last_ypos;
	}

	last_xpos = xpos;
	last_ypos = ypos;
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.action != MLX_RELEASE)
		return;

	t_fdf *fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->window.pointer);
	if (keydata.key == MLX_KEY_C)
		fdf->option.isColor = !fdf->option.isColor;
	else if (keydata.key == MLX_KEY_SPACE)
		fdf->option.isLine = !fdf->option.isLine;
	else
		return;

	char *title = generate_title(fdf->option);
	mlx_set_window_title(fdf->window.pointer, title);
	free(title);
}

void update_option(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->window.pointer, MLX_KEY_R))
	{
		fdf->option.offset = (t_position){.x = fdf->window.size.width / 2, .y = fdf->window.size.height / 2};
		fdf->option.rotation = (t_position){0, 0, 0};
		fdf->option.scale = scale(fdf->map, fdf->window.size);
	}

	if (mlx_is_key_down(fdf->window.pointer, MLX_KEY_W))
		fdf->option.rotation.x += 0.05;
	if (mlx_is_key_down(fdf->window.pointer, MLX_KEY_S))
		fdf->option.rotation.x -= 0.05;
	if (mlx_is_key_down(fdf->window.pointer, MLX_KEY_A))
		fdf->option.rotation.y += 0.05;
	if (mlx_is_key_down(fdf->window.pointer, MLX_KEY_D))
		fdf->option.rotation.y -= 0.05;
	if (mlx_is_key_down(fdf->window.pointer, MLX_KEY_Q))
		fdf->option.rotation.z += 0.05;
	if (mlx_is_key_down(fdf->window.pointer, MLX_KEY_E))
		fdf->option.rotation.z -= 0.05;
}

void loop_hook(void *param)
{
	t_fdf *fdf = (t_fdf *)param;
	mlx_image_t *old_image = fdf->window.image;
	fdf->window.image = mlx_new_image(fdf->window.pointer, fdf->window.size.width, fdf->window.size.height);

	update_option(fdf);
	render(fdf);

	if (old_image)
		mlx_delete_image(fdf->window.pointer, old_image);
	mlx_image_to_window(fdf->window.pointer, fdf->window.image, 0, 0);
}
