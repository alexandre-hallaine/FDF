#include "../include/functions.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

void draw_pixel(int *data, t_display display, size_t x, size_t y, int color)
{
	if (x < display.width && y < display.height)
		data[y * display.width + x] = color;
}

void dda(int *data, t_display display, t_dot *dot1, t_dot *dot2)
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
		draw_pixel(data, display, tmp1.x, tmp1.y, tmp1.color);
		tmp1.x += delta.x;
		tmp1.y += delta.y;
	}
}
