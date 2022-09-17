#include "../include/functions.h"

t_dot stack_dot(t_dot *dot)
{
	if (dot == NULL)
		return ((t_dot){0, 0, 0, 0, NULL});
	t_dot new_dot = {
		.x = dot->x,
		.y = dot->y,
		.z = dot->z,
		.color = dot->color,
		.next = NULL};
	return new_dot;
}

t_dot *find_dot(t_dot *dot, size_t x, size_t y)
{
	for (t_dot *tmp = dot; tmp; tmp = tmp->next)
		if (tmp->x == x && tmp->y == y)
			return tmp;
	return NULL;
}
