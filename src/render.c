#include "../include/functions.h"
#include "../minilibx-linux/mlx.h"

#include <stdbool.h>
#include <time.h>

void render(t_fdf *fdf, int *data)
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
				dda(data, fdf->display, &current_stack, &right_stack);
			right = right->next;
		}
		if (down)
		{
			apply_math(&down_stack, fdf->rotation, offset, fdf->scale);
			if (current->x == down->x)
				dda(data, fdf->display, &current_stack, &down_stack);
			down = down->next;
		}
	}
}

void window(t_fdf *fdf)
{
	int bpp = 32, size_line = fdf->display.width * sizeof(int), endian = 0;
	while (true)
	{
		clock_t begin = clock();

		void *img = mlx_new_image(fdf->mlx, fdf->display.width, fdf->display.height);
		int *data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);

		render(fdf, data);

		mlx_put_image_to_window(fdf->mlx, fdf->win, img, 0, 0);
		mlx_destroy_image(fdf->mlx, img);

		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		fdf->rotation.x += time_spent;
		fdf->rotation.y += time_spent;
		fdf->rotation.z += time_spent;
	}
}
