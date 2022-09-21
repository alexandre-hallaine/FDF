#include "functions.h"

#include <stdbool.h>

void scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fdf *fdf = (t_fdf *)param;
	float focator = 1 + ydelta / 10;
	if (fdf->scale * focator >= 1 && fdf->scale * focator <= 1000)
	{
		fdf->scale *= focator;

		fdf->offset.x = (fdf->offset.x - fdf->display.width / 2) * focator + fdf->display.width / 2;
		fdf->offset.y = (fdf->offset.y - fdf->display.height / 2) * focator + fdf->display.height / 2;
	}
	(void)xdelta;
}

void cursor_hook(double xpos, double ypos, void *param)
{
	static double last_xpos = 0, last_ypos = 0;

	t_fdf *fdf = (t_fdf *)param;
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		fdf->offset.x += xpos - last_xpos;
		fdf->offset.y += ypos - last_ypos;
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
		mlx_close_window(fdf->mlx);
	else if (keydata.key == MLX_KEY_SPACE)
	{
		fdf->lines = !fdf->lines;

		if (fdf->lines)
			mlx_set_window_title(fdf->mlx, "FDF - Lines");
		else
			mlx_set_window_title(fdf->mlx, "FDF - Points");
	}
	else if (keydata.key == MLX_KEY_C)
		fdf->true_color = !fdf->true_color;
	else
		return;

	if (fdf->img)
	{
		mlx_delete_image(fdf->mlx, fdf->img);
		fdf->img = NULL;
	}
}

void keys(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->rotation.x += 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->rotation.x -= 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->rotation.z += 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->rotation.z -= 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->rotation.y += 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->rotation.y -= 0.05;

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->offset.y += 10;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->offset.y -= 10;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->offset.x += 10;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->offset.x -= 10;

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_ADD))
		fdf->scale *= 1.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_SUBTRACT))
		fdf->scale *= 0.95;

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
	{
		fdf->rotation.x = 0;
		fdf->rotation.y = 0;
		fdf->rotation.z = 0;
		fdf->offset.x = fdf->display.width / 2;
		fdf->offset.y = fdf->display.height / 2;
		fdf->scale = get_scale(fdf->map, fdf->display);
	}
}

void loop(void *fdf)
{
	t_fdf *fdf_ptr = (t_fdf *)fdf;
	if (fdf_ptr->img)
		mlx_delete_image(fdf_ptr->mlx, fdf_ptr->img);

	fdf_ptr->img = mlx_new_image(fdf_ptr->mlx, fdf_ptr->display.width, fdf_ptr->display.height);
	mlx_image_to_window(fdf_ptr->mlx, fdf_ptr->img, 0, 0);

	keys(fdf_ptr);
	render(fdf_ptr);
}
