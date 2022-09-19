#include "functions.h"

#include <stdbool.h>

void key_hook(mlx_key_data_t keydata, void *fdf)
{
	if (keydata.action != MLX_RELEASE)
		return;

	t_fdf *fdf_ptr = (t_fdf *)fdf;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf_ptr->mlx);
	else if (keydata.key == MLX_KEY_L)
	{
		fdf_ptr->lines = !fdf_ptr->lines;

		if (fdf_ptr->lines)
			mlx_set_window_title(fdf_ptr->mlx, "FDF - Lines");
		else
			mlx_set_window_title(fdf_ptr->mlx, "FDF - Points");
	}
	else if (keydata.key == MLX_KEY_C)
		fdf_ptr->true_color = !fdf_ptr->true_color;
	else
		return;

	if (fdf_ptr->img)
	{
		mlx_delete_image(fdf_ptr->mlx, fdf_ptr->img);
		fdf_ptr->img = NULL;
	}
}

bool check_key(t_fdf *fdf)
{
	t_dot old_rotation = fdf->rotation;
	t_dot old_offset = fdf->offset;
	float old_scale = fdf->scale;

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
		fdf->offset.y -= 10;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->offset.y += 10;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->offset.x -= 10;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->offset.x += 10;

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

	if (old_rotation.x != fdf->rotation.x ||
		old_rotation.y != fdf->rotation.y ||
		old_rotation.z != fdf->rotation.z ||
		old_offset.x != fdf->offset.x ||
		old_offset.y != fdf->offset.y ||
		old_scale != fdf->scale)
		return (true);
	return (false);
}

void loop(void *fdf)
{
	t_fdf *fdf_ptr = (t_fdf *)fdf;
	if (fdf_ptr->img)
	{
		if (!check_key(fdf_ptr))
			return;
		mlx_delete_image(fdf_ptr->mlx, fdf_ptr->img);
	}

	fdf_ptr->img = mlx_new_image(fdf_ptr->mlx, fdf_ptr->display.width, fdf_ptr->display.height);
	mlx_image_to_window(fdf_ptr->mlx, fdf_ptr->img, 0, 0);
	render(fdf_ptr);
}
