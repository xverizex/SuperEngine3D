#ifndef ENGINE_SHADER_PARTICLE_SYSTEM_HEADER_H
#define ENGINE_SHADER_PARTICLE_SYSTEM_HEADER_H
#include "ishader.h"

#include <stdint.h>

class ShaderParticleSystem: public IShader {
	public:
		void init () override;
		void render (void *_data) override;

		uint32_t program;
		uint32_t uniform_model;
		uint32_t uniform_cam;
		uint32_t uniform_projection;
		uint32_t uniform_translation;
		uint32_t uniform_scale;
		uint32_t uniform_time;
};

#endif
