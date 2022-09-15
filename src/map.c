#include "../include/functions.h"

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

t_map read_map(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		error("Error: open() failed");

	t_map map = {0};
	char *c = malloc(sizeof(char));
	if (c == NULL)
		error("Error: malloc() failed");

	size_t index = 0;
	bool has_value = false;
	while (read(fd, c, 1) > 0)
	{
		switch (*c)
		{
		case '\n':
			if (!map.height)
				map.width = index + 1;
			index = 0;
			has_value = false;
			map.height++;
			break;

		case ' ':
			if (has_value)
				index++;
			has_value = false;
			break;

		default:
			if (!has_value)
			{
				has_value = true;
				map.data = realloc(map.data, (map.width * map.height + index + 1) * sizeof(char));
				map.data[map.width * map.height + index] = 0;
			}
			map.data[map.width * map.height + index] *= 10;
			map.data[map.width * map.height + index] += *c - '0';
			break;
		}
	}
	free(c);
	close(fd);
	return map;
}