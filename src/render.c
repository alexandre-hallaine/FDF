#include "functions.h"

#include <stdbool.h>

void render(t_fdf *fdf)
{
	t_dot *current = fdf->map;
	t_dot *right = find_dot(fdf->map, current->x + 1, current->y);
	t_dot *down = find_dot(fdf->map, current->x, current->y + 1);

	for (; current; current = current->next)
	{
		t_dot current_stack = stack_dot(current);
		t_dot right_stack = stack_dot(right);
		t_dot down_stack = stack_dot(down);

		apply_math(&current_stack, fdf->rotation, fdf->offset, fdf->scale);
		if (right)
		{
			apply_math(&right_stack, fdf->rotation, fdf->offset, fdf->scale);
			if (current->y == right->y)
				dda(fdf->img, fdf->display, &current_stack, &right_stack);
			right = right->next;
		}
		if (down)
		{
			apply_math(&down_stack, fdf->rotation, fdf->offset, fdf->scale);
			if (current->x == down->x)
				dda(fdf->img, fdf->display, &current_stack, &down_stack);
			down = down->next;
		}
	}
}

bool check_key(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);

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
