#include "functions.h"

#include <math.h>

void rotate_x(t_position *position, float angle)
{
	t_position tmp = *position;
	position->y = tmp.y * cos(angle) + tmp.z * sin(angle);
	position->z = -tmp.y * sin(angle) + tmp.z * cos(angle);
}

void rotate_y(t_position *position, float angle)
{
	t_position tmp = *position;
	position->x = tmp.x * cos(angle) + tmp.z * sin(angle);
	position->z = -tmp.x * sin(angle) + tmp.z * cos(angle);
}

void rotate_z(t_position *position, float angle)
{
	t_position tmp = *position;
	position->x = tmp.x * cos(angle) - tmp.y * sin(angle);
	position->y = tmp.x * sin(angle) + tmp.y * cos(angle);
}

void rotate(t_position *position, t_position rotation)
{
	rotate_x(position, rotation.x);
	rotate_y(position, rotation.y);
	rotate_z(position, rotation.z);
}

void isometri(t_position *position)
{
	t_position tmp = *position;
	position->x = (tmp.x - tmp.y) * cos(30 * M_PI / 180);
	position->y = (tmp.x + tmp.y) * sin(30 * M_PI / 180) - tmp.z;
}

t_position to_pixel(t_position position, t_option option)
{
	t_position tmp = position;

	rotate(&tmp, option.rotation);
	isometri(&tmp);

	tmp.x *= option.scale;
	tmp.y *= option.scale;

	tmp.x += option.offset.x;
	tmp.y += option.offset.y;

	return tmp;
}

void render(t_fdf *fdf)
{
	for (t_dot *dot = fdf->map; dot; dot = dot->next)
		dot->pixel = to_pixel(dot->position, fdf->option);

	for (t_dot *dot = fdf->map; dot; dot = dot->next)
		if (is_in_window(dot->pixel, fdf->window))
			mlx_put_pixel(fdf->window.image, dot->pixel.x, dot->pixel.y, dot->color << 8 | 0xFF);

	// t_dot *current = fdf->map;
	// t_dot *right = find_dot(fdf->map, current->x + 1, current->y);
	// t_dot *down = find_dot(fdf->map, current->x, current->y + 1);

	// for (; current; current = current->next)
	// {
	// 	t_dot current_stack = stack_dot(current);
	// 	update_dot(&current_stack, fdf);
	// 	if (fdf->lines)
	// 	{
	// 		if (right)
	// 		{
	// 			t_dot right_stack = stack_dot(right);
	// 			update_dot(&right_stack, fdf);
	// 			if (current->y == right->y)
	// 				dda(fdf->img, fdf->display, &current_stack, &right_stack);
	// 			right = right->next;
	// 		}
	// 		if (down)
	// 		{
	// 			t_dot down_stack = stack_dot(down);
	// 			update_dot(&down_stack, fdf);
	// 			if (current->x == down->x)
	// 				dda(fdf->img, fdf->display, &current_stack, &down_stack);
	// 			down = down->next;
	// 		}
	// 	}
	// 	else if (current_stack.x >= 0 && current_stack.x < fdf->display.width &&
	// 			 current_stack.y >= 0 && current_stack.y < fdf->display.height)
	// 		mlx_put_pixel(fdf->img, current_stack.x, current_stack.y, current_stack.color << 8 | 0xFF);
	// }
}
