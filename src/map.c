#include "functions.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define hexa "0123456789abcdef"
#define HEXA "0123456789ABCDEF"

void map_delta(t_map *map)
{
	map->min.x = map->first->position.x, map->min.y = map->first->position.y, map->min.z = map->first->position.z;
	map->max.x = map->first->position.x, map->max.y = map->first->position.y, map->max.z = map->first->position.z;

	for (t_dot *dot = map->first; dot; dot = dot->next)
	{
		if (dot->position.x < map->min.x)
			map->min.x = dot->position.x;
		if (dot->position.y < map->min.y)
			map->min.y = dot->position.y;
		if (dot->position.z < map->min.z)
			map->min.z = dot->position.z;

		if (dot->position.x > map->max.x)
			map->max.x = dot->position.x;
		if (dot->position.y > map->max.y)
			map->max.y = dot->position.y;
		if (dot->position.z > map->max.z)
			map->max.z = dot->position.z;
	}
}

float scale(t_position delta[2], t_size window)
{
	t_position size = {
		.x = delta[1].x - delta[0].x,
		.y = delta[1].y - delta[0].y,
		.z = delta[1].z - delta[0].z};

	float window_size = window.width > window.height ? window.height : window.width;

	t_position scale = {
		.x = size.x ? window_size / size.x : 0,
		.y = size.y ? window_size / size.y : 0,
		.z = size.z ? window_size / size.z : 0};

	float min_scale = scale.x;
	if (scale.y < min_scale)
		min_scale = scale.y;
	if (scale.z < min_scale)
		min_scale = scale.z;
	return min_scale / 2;
}

void center_map(t_map *map)
{
	t_position center = {
		.x = (map->max.x + map->min.x) / 2,
		.y = (map->max.y + map->min.y) / 2,
		.z = (map->max.z + map->min.z) / 2};

	for (t_dot *dot = map->first; dot; dot = dot->next)
	{
		dot->position.x -= center.x;
		dot->position.y -= center.y;
		dot->position.z -= center.z;
	}

	map_delta(map);
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
		if (*c == '\n')
		{
			if (x != 0)
				++y;
			x = 0;
		}
		else if (*c && (*c != ' ' && *c != '\t'))
			break;
		if (read(fd, c, 1) <= 0)
			return NULL;
	}

	t_dot *dot = malloc(sizeof(t_dot));
	dot->pixel = malloc(sizeof(t_dot));
	dot->position.x = x++;
	dot->position.y = y;
	dot->position.z = *c - '0';
	dot->color = 0;

	if (dot == NULL || dot->pixel == NULL)
		return NULL;

	bool is_hexa = false, is_color = false, is_negatif = false;
	while (true)
	{
		if (read(fd, c, 1) <= 0)
			*c = 0;
		if (*c == 'x')
			is_hexa = true;
		else if (*c == ',')
			is_color = true;
		else if (*c == '-')
			is_negatif = true;
		else if (!*c || *c == ' ' || *c == '\n')
			break;
		else
		{
			update_data(dot, is_color, is_hexa, is_negatif, *c);
			is_negatif = false;
		}
	}
	if (is_color == false)
		dot->color = 0xFFFFFF;
	return dot;
}

t_map load_map(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(2, "Error: open() failed\n");

	char c = 0;
	t_dot *first = get_dot(fd, &c);
	if (first == NULL)
		error(3, "Error: get_dot() failed\n");
	for (t_dot *dot = first; dot; dot = dot->next)
		dot->next = get_dot(fd, &c);
	close(fd);

	t_map map = {.first = first};
	map_delta(&map);
	center_map(&map);
	return map;
}

void free_dots(t_dot *first)
{
	t_dot *tmp;
	while (first)
	{
		tmp = first;
		first = first->next;
		free(tmp->pixel);
		free(tmp);
	}
}
