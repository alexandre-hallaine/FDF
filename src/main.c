#include "../include/functions.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        error("Usage: ./main <filename>");
    t_map map = read_map(argv[1]);
	render(map);
    return 0;
}
