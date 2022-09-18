#include "functions.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

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
		if (tmp1.x >= 0 && tmp1.x < display.width && tmp1.y >= 0 && tmp1.y < display.height)
			mlx_put_pixel(img, tmp1.x, tmp1.y, tmp1.color << 8 | 0xFF);

		tmp1.x += delta.x;
		tmp1.y += delta.y;
	}
}
