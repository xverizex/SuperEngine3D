#include "shader_particle_system.h"
#include "shaders.h"
#include <glad/glad.h>
#include "object.h"
#include "camera.h"
#include "light.h"
#include "sun.h"
#include <stdio.h>
#include <time.h>

void ShaderParticleSystem::init()
{
	program = getProgram(SHADER_PARTICLE_SYSTEM);

	glUseProgram(program);

	uniform_model = glGetUniformLocation(program, "model");
	uniform_projection = glGetUniformLocation(program, "projection");
	uniform_cam = glGetUniformLocation(program, "view");
	uniform_translation = glGetUniformLocation(program, "translate");
	uniform_scale = glGetUniformLocation(program, "scale");
	uniform_time = glGetUniformLocation(program, "time");
}

void ShaderParticleSystem::render(void *_data)
{
	Object *obj = static_cast<Object *>(_data);

	glUseProgram(program);

	glm::mat4 &cam = get_shader_cam();

	glUniformMatrix4fv(uniform_cam, 1, GL_FALSE, &cam[0][0]);

	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, &obj->model[0][0]);
	glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, &obj->projection[0][0]);
	glUniformMatrix4fv(uniform_translation, 1, GL_FALSE, &obj->translate[0][0]);
	glUniformMatrix4fv(uniform_scale, 1, GL_FALSE, &obj->scale[0][0]);
	glUniform1f(uniform_time, time(0));
	
	glBindVertexArray(obj->vao[0]);

	glDrawArrays(GL_POINTS, 0, 40);

}