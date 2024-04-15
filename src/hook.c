#include "types.h"

void scroll(double xdelta, double ydelta, mlx_t *mlx)
{
	(void)xdelta;
	float focator = 1 + ydelta / 10;
	g_data.options.scale *= focator;

	int position[2];
	mlx_get_mouse_pos(mlx, position, position + 1);
	g_data.options.offset[0] = position[0] - (position[0] - g_data.options.offset[0]) * focator;
	g_data.options.offset[1] = position[1] - (position[1] - g_data.options.offset[1]) * focator;
}

void cursor(double xpos, double ypos, mlx_t* mlx)
{
	static double position[2] = {0, 0};
	float offset[2] = {position[0] - xpos, position[1] - ypos};
	position[0] = xpos; position[1] = ypos;

	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		g_data.options.offset[0] -= offset[0];
		g_data.options.offset[1] -= offset[1];
	}
}
