#include "types.h"

#include <stdlib.h>
#include <math.h>

#define ABS(x) (x < 0 ? -x : x)

void isometri(t_dot *dot, float x, float y, float z) {
	dot->position[0] = (x - y) * cos(30 * M_PI / 180);
	dot->position[1] = (x + y) * sin(30 * M_PI / 180) - z;
}

void dda(mlx_image_t *image, t_dot dot[2])
{
	double position[2] = { dot[0].position[0], dot[0].position[1] };
	double position_delta[2] = {
		dot[1].position[0] - position[0],
		dot[1].position[1] - position[1]
	};

	float rgb[3] = { dot[0].color >> 16 & 0xFF, dot[0].color >> 8 & 0xFF, dot[0].color & 0xFF };
	float rgb_delta[3] = {
		(dot[1].color >> 16 & 0xFF) - rgb[0],
		(dot[1].color >> 8 & 0xFF) - rgb[1],
		(dot[1].color & 0xFF) - rgb[2]
	};

	double step_amount = ABS(position_delta[0]) > ABS(position_delta[1]) ? ABS(position_delta[0]) : ABS(position_delta[1]);
	for (double step = 0; step <= step_amount; step++)
	{
		if (position[0] >= 0 && position[0] < image->width && position[1] >= 0 && position[1] < image->height)
			mlx_put_pixel(image, position[0], position[1], (short)rgb[0] << 24 | (short)rgb[1] << 16 | (short)rgb[2] << 8 | 0xFF);

		position[0] += position_delta[0] / step_amount;
		position[1] += position_delta[1] / step_amount;

		rgb[0] += rgb_delta[0] / step_amount;
		rgb[1] += rgb_delta[1] / step_amount;
		rgb[2] += rgb_delta[2] / step_amount;
	}
}

void loop(mlx_t *mlx) {
	static mlx_image_t *image = NULL;
	if (image) mlx_delete_image(mlx, image);
	image = mlx_new_image(mlx, mlx->width, mlx->height);
	mlx_image_to_window(mlx, image, 0, 0);

	for (unsigned short y = 0; y < g_data.map.height; y++)
		for (unsigned short x = 0; x < g_data.map.width; x++) {
			t_dot *dot = &g_data.map.dots[y * g_data.map.width + x];
			isometri(dot, x, y, dot->height);

			dot->position[0] *= g_data.options.scale;
			dot->position[1] *= g_data.options.scale;

			dot->position[0] += g_data.options.offset[0];
			dot->position[1] += g_data.options.offset[1];
		}

	for (unsigned short y = 0; y < g_data.map.height; y++)
		for (unsigned short x = 0; x < g_data.map.width; x++) {
			if (x < g_data.map.width - 1)
				dda(image, (t_dot[2]){
					g_data.map.dots[y * g_data.map.width + x],
					g_data.map.dots[y * g_data.map.width + x + 1]
				});

		 	if (y < g_data.map.height - 1)
		 		dda(image, (t_dot[2]){
		 			g_data.map.dots[y * g_data.map.width + x],
		 			g_data.map.dots[(y + 1) * g_data.map.width + x]
		 		});
		}
}
