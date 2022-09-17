#include "../include/types.h"
#include <math.h>

t_dot rotate_x(t_dot dot, float angle)
{
	t_dot new_dot = {
		.x = dot.x,
		.y = dot.y * cos(angle) + dot.z * sin(angle),
		.z = -dot.y * sin(angle) + dot.z * cos(angle),
		.color = dot.color};
	return new_dot;
}

t_dot rotate_y(t_dot dot, float angle)
{
	t_dot new_dot = {
		.x = dot.x * cos(angle) + dot.z * sin(angle),
		.y = dot.y,
		.z = -dot.x * sin(angle) + dot.z * cos(angle),
		.color = dot.color};
	return new_dot;
}

t_dot rotate_z(t_dot dot, float angle)
{
	t_dot new_dot = {
		.x = dot.x * cos(angle) - dot.y * sin(angle),
		.y = dot.x * sin(angle) + dot.y * cos(angle),
		.z = dot.z,
		.color = dot.color};
	return new_dot;
}

t_dot rotate(t_dot dot, t_rotation rotation)
{
	t_dot rotated_dot = rotate_x(dot, rotation.x);
	rotated_dot = rotate_y(rotated_dot, rotation.y);
	rotated_dot = rotate_z(rotated_dot, rotation.z);
	return rotated_dot;
}