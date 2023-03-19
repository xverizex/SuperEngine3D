#ifndef ENGINE_SHADERS_H
#define ENGINE_SHADERS_H
#include "ishader.h"
#include <glm/glm.hpp>

enum TYPE_SHADERS {
	SHADER_PBR_WITH_SHADOWS,
	SHADER_PARTICLE_SYSTEM,
	SHADER_3D_SIMPLE,
	SHADER_2D_SIMPLE,
	SHADER_PARTICLE_SLEEP_ATTACK_START,
	TYPE_SHADERS_N
};

uint32_t getProgram(uint32_t index);
void init_shaders ();
glm::mat4& get_shader_cam();
IShader* getIShader(TYPE_SHADERS index);
#endif
