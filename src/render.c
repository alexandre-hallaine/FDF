#include "functions.h"

#include <stdbool.h>

void render(t_fdf *fdf)
{
	t_dot offset = {
		.x = fdf->display.width / 2,
		.y = fdf->display.height / 2,
	};

	t_dot *current = fdf->map;
	t_dot *right = find_dot(fdf->map, current->x + 1, current->y);
	t_dot *down = find_dot(fdf->map, current->x, current->y + 1);

	for (; current; current = current->next)
	{
		t_dot current_stack = stack_dot(current);
		t_dot right_stack = stack_dot(right);
		t_dot down_stack = stack_dot(down);

		apply_math(&current_stack, fdf->rotation, offset, fdf->scale);
		if (right)
		{
			apply_math(&right_stack, fdf->rotation, offset, fdf->scale);
			if (current->y == right->y)
				dda(fdf->img, fdf->display, &current_stack, &right_stack);
			right = right->next;
		}
		if (down)
		{
			apply_math(&down_stack, fdf->rotation, offset, fdf->scale);
			if (current->x == down->x)
				dda(fdf->img, fdf->display, &current_stack, &down_stack);
			down = down->next;
		}
	}
}

void loop(void *fdf)
{
	t_fdf *fdf_ptr = (t_fdf *)fdf;
	if (fdf_ptr->img)
		mlx_delete_image(fdf_ptr->mlx, fdf_ptr->img);

	fdf_ptr->img = mlx_new_image(fdf_ptr->mlx, fdf_ptr->display.width, fdf_ptr->display.height);
	mlx_image_to_window(fdf_ptr->mlx, fdf_ptr->img, 0, 0);

	render(fdf_ptr);

	fdf_ptr->rotation.x += 0.005;
	fdf_ptr->rotation.y += 0.005;
	fdf_ptr->rotation.z += 0.005;
}
