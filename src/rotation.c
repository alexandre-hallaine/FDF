#include "../include/types.h"
#include <math.h>

void rotate_x(t_dot *dot, float angle)
{
	float y = dot->y;
	float z = dot->z;
	dot->y = y * cos(angle) + z * sin(angle);
	dot->z = -y * sin(angle) + z * cos(angle);
}

void rotate_y(t_dot *dot, float angle)
{
	float x = dot->x;
	float z = dot->z;
	dot->x = x * cos(angle) - z * sin(angle);
	dot->z = x * sin(angle) + z * cos(angle);
}

void rotate_z(t_dot *dot, float angle)
{
	float x = dot->x;
	float y = dot->y;
	dot->x = x * cos(angle) + y * sin(angle);
	dot->y = -x * sin(angle) + y * cos(angle);
}

void rotate(t_dot *dot, t_rotation rotation)
{
	rotate_x(dot, rotation.x);
	rotate_y(dot, rotation.y);
	rotate_z(dot, rotation.z);
}