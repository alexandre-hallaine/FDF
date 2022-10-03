#include "functions.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

int two_color(int color[2], float percent)
{
	int rgb1[3] = {
		(color[0] >> 16) & 0xFF,
		(color[0] >> 8) & 0xFF,
		color[0] & 0xFF};
	int rgb2[3] = {
		(color[1] >> 16) & 0xFF,
		(color[1] >> 8) & 0xFF,
		color[1] & 0xFF};

	int rgb[3] = {
		rgb1[0] + (rgb2[0] - rgb1[0]) * percent,
		rgb1[1] + (rgb2[1] - rgb1[1]) * percent,
		rgb1[2] + (rgb2[2] - rgb1[2]) * percent};
	return (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
}

bool is_in_window(t_position position, t_window window)
{
	return (position.x >= 0 && position.x < window.size.width &&
			position.y >= 0 && position.y < window.size.height);
}

void dda(t_window window, t_dot dot[2])
{
	if (!is_in_window(dot[0].pixel, window) &&
		!is_in_window(dot[1].pixel, window))
		return;

	t_position delta = {
		.x = dot[1].pixel.x - dot[0].pixel.x,
		.y = dot[1].pixel.y - dot[0].pixel.y};
	float step = ABS(delta.x) > ABS(delta.y) ? ABS(delta.x) : ABS(delta.y);
	delta.x /= step;
	delta.y /= step;

	t_position tmp = dot[0].pixel;
	for (float current = 0; current <= step; current++)
	{
		if (is_in_window(tmp, window))
		{
			int color = two_color((int[2]){dot[0].color, dot[1].color}, current / step);
			mlx_put_pixel(window.image, tmp.x, tmp.y, color << 8 | 0xFF);
		}

		tmp.x += delta.x;
		tmp.y += delta.y;
	}
}
