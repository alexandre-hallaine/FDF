#include "../include/types.h"

#include <math.h>

void rotate(t_dot *dot, t_dot rotation)
{
	float x = dot->x;
	float y = dot->y;
	float z = dot->z;

	if (rotation.x)
	{
		dot->y = y * cos(rotation.x) + z * sin(rotation.x);
		dot->z = -y * sin(rotation.x) + z * cos(rotation.x);
	}
	if (rotation.y)
	{
		dot->x = x * cos(rotation.y) + z * sin(rotation.y);
		dot->z = -x * sin(rotation.y) + z * cos(rotation.y);
	}
	if (rotation.z)
	{
		dot->x = x * cos(rotation.z) + y * sin(rotation.z);
		dot->y = -x * sin(rotation.z) + y * cos(rotation.z);
	}
}

void isometri(t_dot *dot)
{
	float x = dot->x;
	float y = dot->y;
	dot->x = (x - y) * cos(30 * M_PI / 180);
	dot->y = -dot->z + (x + y) * sin(30 * M_PI / 180);
}

void apply_math(t_dot *dot, t_dot rotation, t_dot offset, float zoom)
{
	rotate(dot, rotation);
	isometri(dot);
	dot->x = dot->x * zoom + offset.x;
	dot->y = dot->y * zoom + offset.y;
}
