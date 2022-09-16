#include "../include/functions.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        error("Usage: ./main <filename>");
    t_dot *map = read_map(argv[1]);
	window(map);
    return 0;
}
