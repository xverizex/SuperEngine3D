#ifdef __ANDROID__
#include "SDL.h"
#include <android/log.h>
#else
#include <SDL2/SDL.h>
#endif
#include <glad/glad.h>
#include <stdint.h>
#include <iostream>
#include "shaders.h"
#include "ishader.h"
#include "shader_pbr_with_shadows.h"
#include "shader_particle_system.h"
#include "shader_3d_simple.h"
#include "shader_2d_simple.h"
#include "shader_particle_sleep_attack_start.h"
#include <glm/glm.hpp>

static IShader **global;

static uint32_t program[TYPE_SHADERS_N];

static long get_total_file_size (SDL_RWops *io)
{
	SDL_RWseek (io, 0, RW_SEEK_END);
	long pos = SDL_RWtell (io);
	SDL_RWseek (io, 0, RW_SEEK_SET);
	return pos;
}

static char *get_data_from_file (const char *filename)
{
	SDL_RWops *io = SDL_RWFromFile (filename, "rb");
	long pos = get_total_file_size (io);
	char *data = new char[pos + 1];
	SDL_RWread (io, data, pos, 1);
	data[pos] = 0;
	SDL_RWclose (io);
	return data;
}

static uint32_t compile_shader (int type, const char *filename)
{
	char *data = get_data_from_file (filename);

	uint32_t shader = glCreateShader (type);
	glShaderSource (shader, 1, &data, nullptr);
	glCompileShader (shader);

	int status;
	glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		int log_length;
		glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &log_length);
		char *log = new char[log_length];
		glGetShaderInfoLog (shader, log_length, nullptr, log);
		std::cout << log << "!!" << std::endl;
		delete []log;
	}

	return shader;
}

static uint32_t link_program (uint32_t vertex, uint32_t fragment)
{
	uint32_t program = glCreateProgram ();
	glAttachShader (program, vertex);
	glAttachShader (program, fragment);
	glLinkProgram (program);

	int status;
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		int log_length;
		glGetProgramiv (program, GL_INFO_LOG_LENGTH, &log_length);
		char *log = new char[log_length];
		glGetProgramInfoLog (program, log_length, nullptr, log);
		std::cout << log << "!!" << std::endl;
		delete []log;
	}

	return program;
}

static uint32_t load_shader (const char *name_shader)
{
	char vpath[255];
	char fpath[255];
	snprintf (vpath, 255, "assets/%s.vert", name_shader);
	snprintf (fpath, 255, "assets/%s.frag", name_shader);

	uint32_t vertex = compile_shader (GL_VERTEX_SHADER, vpath);
	uint32_t fragment = compile_shader (GL_FRAGMENT_SHADER, fpath);
	uint32_t program = link_program (vertex, fragment);

	return program;
}

uint32_t getProgram(uint32_t index)
{
	return program[index];
}

void init_shaders ()
{
	global = new IShader *[TYPE_SHADERS_N];

	program[SHADER_PBR_WITH_SHADOWS] = load_shader("pbr_with_shadows");
	global[SHADER_PBR_WITH_SHADOWS] = new ShaderPBRWithShadows ();
	global[SHADER_PBR_WITH_SHADOWS]->init ();

	program[SHADER_PARTICLE_SYSTEM] = load_shader("particle_system");
	global[SHADER_PARTICLE_SYSTEM] = new ShaderParticleSystem();
	global[SHADER_PARTICLE_SYSTEM]->init ();

	program[SHADER_3D_SIMPLE] = load_shader("3d_simple");
	global[SHADER_3D_SIMPLE] = new Shader3dSimple();
	global[SHADER_3D_SIMPLE]->init ();

	program[SHADER_2D_SIMPLE] = load_shader("2d_simple");
	global[SHADER_2D_SIMPLE] = new Shader2dSimple();
	global[SHADER_2D_SIMPLE]->init ();

	program[SHADER_PARTICLE_SLEEP_ATTACK_START] = load_shader("particle_sleep_attack_start");
	global[SHADER_PARTICLE_SLEEP_ATTACK_START] = new ShaderParticleSleepAttackStart();
	global[SHADER_PARTICLE_SLEEP_ATTACK_START]->init ();

}

static glm::mat4 cam;

glm::mat4& get_shader_cam()
{
	return cam;
}

IShader* getIShader(TYPE_SHADERS index)
{
	return global[index];
}