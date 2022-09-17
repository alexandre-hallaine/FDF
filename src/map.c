#include "../include/functions.h"

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define hexa "0123456789abcdef"
#define HEXA "0123456789ABCDEF"

void center_map(t_dot *map)
{
	float x_min = 0, x_max = 0;
	float y_min = 0, y_max = 0;
	float z_min = 0, z_max = 0;

	for (t_dot *dot = map; dot; dot = dot->next)
	{
		if (dot->x < x_min)
			x_min = dot->x;
		if (dot->x > x_max)
			x_max = dot->x;
		if (dot->y < y_min)
			y_min = dot->y;
		if (dot->y > y_max)
			y_max = dot->y;
		if (dot->z < z_min)
			z_min = dot->z;
		if (dot->z > z_max)
			z_max = dot->z;
	}

	float x_center = (x_max - x_min) / 2;
	float y_center = (y_max - y_min) / 2;
	float z_center = (z_max - z_min) / 2;

	for (t_dot *dot = map; dot; dot = dot->next)
	{
		dot->x -= x_center;
		dot->y -= y_center;
		dot->z -= z_center;
	}
}

void update_data(t_dot *dot, bool is_color, bool is_hexa, bool is_negatif, char c)
{
	ssize_t nbr = is_color ? dot->color : dot->z;
	if (is_hexa)
	{
		unsigned char index = 0;
		while (hexa[index] != c && HEXA[index] != c && index < 16)
			index++;
		if (index < 16)
			nbr = nbr * 16 + index;
	}
	else
		nbr = nbr * 10 + c - '0';

	if (is_negatif)
		nbr = -nbr;

	if (is_color)
		dot->color = nbr;
	else
		dot->z = nbr;
}

t_dot *get_dot(int fd, char *c)
{
	static size_t x = 0, y = 0;

	while (true)
	{
		if (read(fd, c, 1) <= 0)
			return NULL;
		if (*c != ' ' && *c != '\n')
			break;
	}

	t_dot *dot = malloc(sizeof(t_dot));
	dot->x = x++;
	dot->y = y;
	dot->z = *c - '0';
	dot->color = 0;

	bool is_hexa = false, is_color = false, is_negatif = false;
	while (read(fd, c, 1) > 0)
		if (*c == 'x')
			is_hexa = true;
		else if (*c == ',')
			is_color = true;
		else if (*c == '-')
			is_negatif = true;
		else if (*c == ' ' || *c == '\n')
			break;
		else
		{
			update_data(dot, is_color, is_hexa, is_negatif, *c);
			is_negatif = false;
		}

	if (is_color == false)
		dot->color = 0xffffff;

	if (*c == '\n')
	{
		x = 0;
		y++;
	}
	return dot;
}

t_dot *read_map(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		error("Error: open() failed");

	char *c = malloc(sizeof(char));
	if (c == NULL)
		return NULL;

	t_dot *first = get_dot(fd, c);
	t_dot *current = first;
	if (current)
		while ((current->next = get_dot(fd, c)))
			current = current->next;

	close(fd);
	free(c);
	center_map(first);
	return first;
}
