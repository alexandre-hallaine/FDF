#include "functions.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

t_dot stack_dot(t_dot *dot)
{
	if (dot == NULL)
		return ((t_dot){0, 0, 0, 0, NULL});
	t_dot new_dot = {
		.x = dot->x,
		.y = dot->y,
		.z = dot->z,
		.color = dot->color,
		.next = NULL};
	return new_dot;
}

t_dot *find_dot(t_dot *dot, float x, float y)
{
	for (t_dot *tmp = dot; tmp; tmp = tmp->next)
		if (tmp->x == x && tmp->y == y)
			return tmp;
	return NULL;
}

int two_color(int color1, int color2, float percent)
{
	int r = (color1 >> 16) * (1 - percent) + (color2 >> 16) * percent;
	int g = ((color1 >> 8) & 0xFF) * (1 - percent) + ((color2 >> 8) & 0xFF) * percent;
	int b = (color1 & 0xFF) * (1 - percent) + (color2 & 0xFF) * percent;
	return (r << 16) | (g << 8) | b;
}

void dda(mlx_image_t *img, t_display display, t_dot *dot1, t_dot *dot2)
{
	t_dot tmp1 = stack_dot(dot1);
	t_dot tmp2 = stack_dot(dot2);

	t_dot delta = {
		.x = tmp2.x - tmp1.x,
		.y = tmp2.y - tmp1.y};

	float step = ABS(delta.x) > ABS(delta.y) ? ABS(delta.x) : ABS(delta.y);

	delta.x /= step;
	delta.y /= step;

	for (size_t i = 0; i <= step; i++)
	{
		int color = two_color(tmp1.color, tmp2.color, (float)i / step);
		if (tmp1.x >= 0 && tmp1.x < display.width &&
			tmp1.y >= 0 && tmp1.y < display.height)
			mlx_put_pixel(img, tmp1.x, tmp1.y, color << 8 | 0xFF);

		tmp1.x += delta.x;
		tmp1.y += delta.y;
	}
}
