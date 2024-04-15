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
		if (tmp[0] >= 0 && tmp[0] < WIDTH && tmp[1] >= 0 && tmp[1] < HEIGHT)
			mlx_put_pixel(image, tmp[0], tmp[1], dot[0].color << 8 | 0xFF);

		tmp[0] += delta[0];
		tmp[1] += delta[1];
	}
}

void loop(mlx_t *mlx) {
	static mlx_image_t *image = NULL;
	if (image) mlx_delete_image(mlx, image);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);

	for (size_t y = 0; g_data.dots[y]; y++)
		for (size_t x = 0; g_data.dots[y][x].color; x++) {
			t_dot *dot = &g_data.dots[y][x];
			isometri(dot, x, y, dot->height);
			dot->position[0] *= 15;
			dot->position[1] *= 15;
			dot->position[0] += WIDTH / 2;
			dot->position[1] += HEIGHT / 2;
		}

	for (size_t y = 0; g_data.dots[y]; y++)
		for (size_t x = 0; g_data.dots[y][x].color; x++) {
		 	if (g_data.dots[y][x + 1].color)
		 		dda(image, (t_dot[2]){
		 			g_data.dots[y][x],
		 			g_data.dots[y][x + 1]
		 		});

		 	if (g_data.dots[y + 1] && g_data.dots[y + 1][x].color)
		 		dda(image, (t_dot[2]){
		 			g_data.dots[y][x],
		 			g_data.dots[y + 1][x]
		 		});
		}
}
