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

	t_dot *dot = fdf->map;
	t_dot *next_y = dot;

	for (; dot; dot = dot->next)
		if (fdf->option.isLine)
		{
			if (dot->next && dot->next->position.y == dot->position.y)
				dda(fdf->window, (t_dot[2]){*dot, *dot->next});

			while (next_y && next_y->position.y <= dot->position.y)
				next_y = next_y->next;

			while (next_y && next_y->position.x < dot->position.x &&
				   (next_y->next && next_y->next->position.y == next_y->position.y))
				next_y = next_y->next;

			if (next_y && next_y->position.x == dot->position.x)
				dda(fdf->window, (t_dot[2]){*dot, *next_y});
		}
		else if (is_in_window(dot->pixel, fdf->window))
			mlx_put_pixel(fdf->window.image, dot->pixel.x, dot->pixel.y, dot->color << 8 | 0xFF);
}
