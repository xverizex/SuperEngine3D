#include "light.h"

static Light *global;

Light::Light()
{

}

Light* Light::getInstance()
{
	if (!global) global = new Light();
	return global;
}

void Light::init (uint32_t size)
{
	pos = new float[size * 3];
	color = new float[size * 3];
}
void Light::setPos (uint32_t index, float x, float y, float z)
{
	pos[index * 3 + 0] = x;
	pos[index * 3 + 1] = y;
	pos[index * 3 + 2] = z;
}

void Light::setColor (uint32_t index, float r, float g, float b)
{
	color[index * 3 + 0] = r;
	color[index * 3 + 1] = g;
	color[index * 3 + 2] = b;
}