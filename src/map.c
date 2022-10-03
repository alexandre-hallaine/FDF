#include "functions.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define hexa "0123456789abcdef"
#define HEXA "0123456789ABCDEF"

void map_delta(t_dot *map, t_position delta[2])
{
	delta[0].x = map->position.x, delta[0].y = map->position.y, delta[0].z = map->position.z;
	delta[1].x = map->position.x, delta[1].y = map->position.y, delta[1].z = map->position.z;

	for (t_dot *dot = map; dot; dot = dot->next)
	{
		if (dot->position.x < delta[0].x)
			delta[0].x = dot->position.x;
		if (dot->position.y < delta[0].y)
			delta[0].y = dot->position.y;
		if (dot->position.z < delta[0].z)
			delta[0].z = dot->position.z;

		if (dot->position.x > delta[1].x)
			delta[1].x = dot->position.x;
		if (dot->position.y > delta[1].y)
			delta[1].y = dot->position.y;
		if (dot->position.z > delta[1].z)
			delta[1].z = dot->position.z;
	}
}

float scale(t_dot *map, t_size window)
{
	t_position delta[2];
	map_delta(map, delta);

	t_position size = {
		.x = delta[1].x - delta[0].x,
		.y = delta[1].y - delta[0].y,
		.z = delta[1].z - delta[0].z};

	t_position scale = {
		.x = window.width / size.x,
		.y = window.height / size.y,
		.z = window.height / size.z,
	};

	float final_scale = scale.x;
	if (scale.y < final_scale)
		final_scale = scale.y;
	if (scale.z < final_scale)
		final_scale = scale.z;
	return final_scale / 2;
}

void center_map(t_dot *map)
{
	t_position delta[2];
	map_delta(map, delta);

	t_position center = {
		.x = (delta[0].x + delta[1].x) / 2,
		.y = (delta[0].y + delta[1].y) / 2,
		.z = (delta[0].z + delta[1].z) / 2};

	for (t_dot *dot = map; dot; dot = dot->next)
	{
		dot->position.x -= center.x;
		dot->position.y -= center.y;
		dot->position.z -= center.z;
	}
}

void update_data(t_dot *dot, bool is_color, bool is_hexa, bool is_negatif, char c)
{
	ssize_t nbr = is_color ? dot->color : dot->position.z;
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
		dot->position.z = nbr;
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
	dot->position.x = x++;
	dot->position.y = y;
	dot->position.z = *c - '0';
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
		dot->color = 0x00C991FF;

	if (*c == '\n')
	{
		x = 0;
		y++;
	}
	return dot;
}

t_dot *load_map(char *filename)
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

	free(c);
	close(fd);

	center_map(first);
	return first;
}

void free_map(t_dot *current)
{
	t_dot *tmp;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
}
