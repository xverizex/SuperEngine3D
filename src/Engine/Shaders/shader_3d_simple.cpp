#include "shader_3d_simple.h"
#include "shaders.h"
#include <glad/glad.h>
#include "object.h"
#include "camera.h"
#include "light.h"
#include "sun.h"
#include <stdio.h>
#include <time.h>

void Shader3dSimple::init()
{
	program = getProgram(SHADER_3D_SIMPLE);

	glUseProgram(program);

	uniform_model = glGetUniformLocation(program, "model");
	uniform_projection = glGetUniformLocation(program, "projection");
	uniform_cam = glGetUniformLocation(program, "view");
	uniform_translation = glGetUniformLocation(program, "translate");
	uniform_scale = glGetUniformLocation(program, "scale");
	uniform_sampler = glGetUniformLocation(program, "s_texture");
	uniform_rotate = glGetUniformLocation(program, "rotate");
}

void Shader3dSimple::render(void *_data)
{
	Object *obj = static_cast<Object *>(_data);

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj->vdata->tex_sampler[0]);
	glUniform1i(uniform_sampler, 0);

	glm::mat4 &cam = get_shader_cam();

	glUniformMatrix4fv(uniform_cam, 1, GL_FALSE, &cam[0][0]);

	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, &obj->model[0][0]);
	glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, &obj->projection[0][0]);
	glUniformMatrix4fv(uniform_translation, 1, GL_FALSE, &obj->translate[0][0]);
	glUniformMatrix4fv(uniform_scale, 1, GL_FALSE, &obj->scale[0][0]);
	glUniformMatrix4fv(uniform_rotate, 1, GL_FALSE, &obj->rotate[0][0]);
	
	
	glBindVertexArray(obj->vao[obj->cur_frame]);

	glDrawArrays(GL_TRIANGLES, 0, obj->max_vertex);
}