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

	load_map(argv[1]);
	return 0;
}
