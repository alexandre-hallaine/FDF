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
	float delta[2] = {
		dot[0].position[0] - dot[1].position[0],
		dot[0].position[1] - dot[1].position[1]
	};

	float step = ABS(delta[0]) > ABS(delta[1]) ? ABS(delta[0]) : ABS(delta[1]);
	delta[0] /= step;
	delta[1] /= step;

	double tmp[2] = { dot[1].position[0], dot[1].position[1] };
	for (float current = 0; current <= step; current++)
	{
		if (tmp[0] >= 0 && tmp[0] < image->width && tmp[1] >= 0 && tmp[1] < image->height)
			mlx_put_pixel(image, tmp[0], tmp[1], dot[0].color << 8 | 0xFF);

		tmp[0] += delta[0];
		tmp[1] += delta[1];
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
