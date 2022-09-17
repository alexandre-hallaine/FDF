#include "../include/functions.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		error("Usage: ./main <filename>");
	t_dot *map = read_map(argv[1]);
	t_fdf fdf = init(map);
	window(&fdf);
	return 0;
}
