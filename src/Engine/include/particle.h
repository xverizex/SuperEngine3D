#ifndef ENGINE_PARTICLE_HEADER_H
#define ENGINE_PARTICLE_HEADER_H
#include "object.h"

class Particle: public Object {
	public:
		Particle(TYPE_SHADERS type_shader);
		virtual void step ();
};

#endif
