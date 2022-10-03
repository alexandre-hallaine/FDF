#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

void error(char *str)
{
	dprintf(2, "%s\n", str);
	exit(1);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		error("Usage: ./main <filename>");

	t_dot *map = load_map(argv[1]);
	t_option option = {0};
	t_window window = generate_window(option);

	option.scale = scale(map, window.size);
	option.offset = (t_position){window.size.width / 2, window.size.height / 2, 0};

	start((t_fdf){map, window, option});

	mlx_terminate(window.pointer);
	free_map(map);
	return 0;
}
