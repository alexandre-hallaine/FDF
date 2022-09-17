#include "../include/functions.h"
#include "../minilibx-linux/mlx.h"

#include <stdbool.h>


void render(t_dot *map, t_dot *rotation, size_t size_x, size_t size_y, int *data)
{
	t_dot delta = {
		.x = size_x / 2,
		.y = size_y / 2};
	float zoom = 10;

	t_dot *current = map;
	t_dot *right = find_dot(map, current->x + 1, current->y);
	t_dot *down = find_dot(map, current->x, current->y + 1);

	for (; current; current = current->next)
	{
		t_dot current_stack = stack_dot(current);
		t_dot right_stack = stack_dot(right);
		t_dot down_stack = stack_dot(down);

		apply_math(&current_stack, rotation, &delta, zoom);
		if (right)
		{
			apply_math(&right_stack, rotation, &delta, zoom);
			if (current->y == right->y)
				dda(data, size_x, size_y, &current_stack, &right_stack);
			right = right->next;
		}
		if (down)
		{
			apply_math(&down_stack, rotation, &delta, zoom);
			if (current->x == down->x)
				dda(data, size_x, size_y, &current_stack, &down_stack);
			down = down->next;
		}
	}
}

void window(t_dot *map)
{
	int size_x = 1200, size_y = 900;
	int bpp = 32, size_line = size_x * sizeof(int), endian = 0;

	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, size_x, size_y, "fdf");

	t_dot rotation = {
		.x = 0,
		.y = 0,
		.z = 0};

	while (true)
	{
		void *img = mlx_new_image(mlx, size_x, size_y);
		int *data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);

		render(map, &rotation, size_x, size_y, data);

		mlx_put_image_to_window(mlx, win, img, 0, 0);
		mlx_destroy_image(mlx, img);

		rotation.z += 0.001;
	}
}