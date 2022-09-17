#include "../include/functions.h"

void draw_dot(int *data, size_t size_x, size_t size_y, size_t x, size_t y, int color)
{
	size_t index = y * size_x + x;
	if (index < size_x * size_y)
		data[index] = color;
}
