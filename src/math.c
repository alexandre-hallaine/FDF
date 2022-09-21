#include "functions.h"

#include <math.h>

void rotate_x(t_dot *dot, float angle)
{
	float y = dot->y;
	float z = dot->z;

	dot->y = y * cos(angle) + z * sin(angle);
	dot->z = -y * sin(angle) + z * cos(angle);
}

void rotate_y(t_dot *dot, float angle)
{
	float x = dot->x;
	float z = dot->z;

	dot->x = x * cos(angle) + z * sin(angle);
	dot->z = -x * sin(angle) + z * cos(angle);
}

void rotate_z(t_dot *dot, float angle)
{
	float x = dot->x;
	float y = dot->y;

	dot->x = x * cos(angle) - y * sin(angle);
	dot->y = x * sin(angle) + y * cos(angle);
}

void rotate(t_dot *dot, t_dot rotation)
{
	rotate_x(dot, rotation.x);
	rotate_y(dot, rotation.y);
	rotate_z(dot, rotation.z);
}

void isometri(t_dot *dot)
{
	float x = dot->x;
	float y = dot->y;
	dot->x = (x - y) * cos(30 * M_PI / 180);
	dot->y = -dot->z + (x + y) * sin(30 * M_PI / 180);
}

int get_color(float z, float scale)
{
	float max = 300 / scale;
	float min = -300 / scale;

	if (z > max)
		z = max;
	if (z < min)
		z = min;

	float ratio = (z - min) / (max - min);
	unsigned char r = 255 * ratio;
	unsigned char g = 255 * (1 - ratio);
	unsigned char b = 255;
	return (r << 16) | (g << 8) | b;
}

void update_dot(t_dot *dot, t_fdf *fdf)
{
	if (fdf->true_color)
		dot->color = get_color(dot->z, fdf->scale);

	rotate(dot, fdf->rotation);
	isometri(dot);
	dot->x = dot->x * fdf->scale + fdf->offset.x;
	dot->y = dot->y * fdf->scale + fdf->offset.y;
}

void render(t_fdf *fdf)
{
	t_dot *current = fdf->map;
	t_dot *right = find_dot(fdf->map, current->x + 1, current->y);
	t_dot *down = find_dot(fdf->map, current->x, current->y + 1);

	for (; current; current = current->next)
	{
		t_dot current_stack = stack_dot(current);
		update_dot(&current_stack, fdf);
		if (fdf->lines)
		{
			if (right)
			{
				t_dot right_stack = stack_dot(right);
				update_dot(&right_stack, fdf);
				if (current->y == right->y)
					dda(fdf->img, fdf->display, &current_stack, &right_stack);
				right = right->next;
			}
			if (down)
			{
				t_dot down_stack = stack_dot(down);
				update_dot(&down_stack, fdf);
				if (current->x == down->x)
					dda(fdf->img, fdf->display, &current_stack, &down_stack);
				down = down->next;
			}
		}
		else if (current_stack.x >= 0 && current_stack.x < fdf->display.width &&
				 current_stack.y >= 0 && current_stack.y < fdf->display.height)
			mlx_put_pixel(fdf->img, current_stack.x, current_stack.y, current_stack.color << 8 | 0xFF);
	}
}
