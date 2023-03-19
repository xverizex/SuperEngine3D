#include "shader_pbr_with_shadows.h"
#include "shaders.h"
#include <glad/glad.h>
#include "object.h"
#include "camera.h"
#include "light.h"
#include "sun.h"
#include <stdio.h>

void ShaderPBRWithShadows::init()
{
	program = getProgram(SHADER_PBR_WITH_SHADOWS);

	glUseProgram(program);

	uniform_rotate = glGetUniformLocation(program, "rotate");
	uniform_model = glGetUniformLocation(program, "model");
	uniform_projection = glGetUniformLocation(program, "projection");
	uniform_cam = glGetUniformLocation(program, "view");
	uniform_translation = glGetUniformLocation(program, "translate");
	uniform_scale = glGetUniformLocation(program, "scale");

	uniform_sampler_albedo = glGetUniformLocation(program, "albedoMap");
	uniform_sampler_normal = glGetUniformLocation(program, "normalMap");
	uniform_sampler_metallic = glGetUniformLocation(program, "metallicMap");
	uniform_sampler_roughness = glGetUniformLocation(program, "roughnessMap");
	uniform_sampler_ao = glGetUniformLocation(program, "aoMap");

	uniform_point_light_position = glGetUniformLocation(program, "pointLightPositions");
	uniform_point_light_color = glGetUniformLocation(program, "pointLightColors");

	uniform_direction_light = glGetUniformLocation(program, "directionLightDir");
	uniform_direction_light_color = glGetUniformLocation(program, "directionLightColor");

	uniform_cam_pos = glGetUniformLocation(program, "camPos");
}

void ShaderPBRWithShadows::render(void *_data)
{
	Object *obj = static_cast<Object *>(_data);

	glUseProgram(program);

	glm::mat4 &cam = get_shader_cam();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj->vdata->tex_sampler[PBR_ALBEDO]);
	glUniform1i(uniform_sampler_albedo, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, obj->vdata->tex_sampler[PBR_NORMAL]);
	glUniform1i(uniform_sampler_normal, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, obj->vdata->tex_sampler[PBR_METALLIC]);
	glUniform1i(uniform_sampler_metallic, 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, obj->vdata->tex_sampler[PBR_ROUGHNESS]);
	glUniform1i(uniform_sampler_roughness, 3);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, obj->vdata->tex_sampler[PBR_AO]);
	glUniform1i(uniform_sampler_ao, 4);

	glUniformMatrix4fv(uniform_cam, 1, GL_FALSE, &cam[0][0]);

	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, &obj->model[0][0]);
	glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, &obj->projection[0][0]);
	glUniformMatrix4fv(uniform_translation, 1, GL_FALSE, &obj->translate[0][0]);
	glUniformMatrix4fv(uniform_rotate, 1, GL_FALSE, &obj->rotate[0][0]);
	glUniformMatrix4fv(uniform_scale, 1, GL_FALSE, &obj->scale[0][0]);

	Light *light = Light::getInstance();
	
	Camera *camera = Camera::getInstance();

	glUniform3fv(uniform_point_light_position, 1, light->pos);
	glUniform3fv(uniform_point_light_color, 1, light->color);

	Sun* sun = Sun::getInstance();

	glUniform3fv(uniform_direction_light, 1, sun->direction);
	glUniform3fv(uniform_direction_light_color, 1, sun->color);
	
	glUniform3fv(uniform_cam_pos, 1, &camera->pos[0]);

	glBindVertexArray(obj->vao[obj->cur_frame]);

	glDrawArrays(GL_TRIANGLES, 0, obj->max_vertex);

}