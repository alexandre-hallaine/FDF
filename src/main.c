#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

t_data g_data = {0};

void error(int code, char *str, ...)
{
	va_list args;
	va_start(args, str);
	vfprintf(stderr, str, args);
	va_end(args);
	exit(code);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		error(1, "Usage: %s <filename>\n", argv[0]);

	g_data.map = load_map(argv[1]);
	g_data.options = (t_options){
		.offset = {WIDTH / 2, HEIGHT / 2},
		.scale = 1
	};
	
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, argv[0], true);

	mlx_scroll_hook(mlx, scroll, mlx);
	mlx_cursor_hook(mlx, cursor, mlx);
	mlx_key_hook(mlx, key, mlx);
	mlx_loop_hook(mlx, loop, mlx);
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free(g_data.map.dots);
	return 0;
}
