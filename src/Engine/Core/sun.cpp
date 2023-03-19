#include "sun.h"

static Sun *global;

Sun::Sun()
{

}

Sun* Sun::getInstance()
{
	if (!global) global = new Sun();
	return global;
}

void Sun::init (uint32_t size)
{
	pos = new float[size * 3];
	color = new float[size * 3];
	direction = new float[size * 3];
}
void Sun::setPos (uint32_t index, float x, float y, float z)
{
	pos[index * 3 + 0] = x;
	pos[index * 3 + 1] = y;
	pos[index * 3 + 2] = z;
}

void Sun::setColor (uint32_t index, float r, float g, float b)
{
	color[index * 3 + 0] = r;
	color[index * 3 + 1] = g;
	color[index * 3 + 2] = b;
}

void Sun::setDirection (uint32_t index, float x, float y, float z)
{
	direction[index * 3 + 0] = x;
	direction[index * 3 + 1] = y;
	direction[index * 3 + 2] = z;
}