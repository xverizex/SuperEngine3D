#include "object.h"
#include <glm/ext.hpp>
#include "main.h"
#include "downloader.h"
#include "shaders.h"
#include <glad/glad.h>
#include "shader_pbr_with_shadows.h"
#include <stdio.h>
#include "berry.h"
#include "card.h"

Object::Object(SPRITE_ASSET res, TYPE_SHADERS thsader)
{
	cur_tex = 0;
	bonus = nullptr;

	WindowSize* ws = WindowSize::getInstance();
	
	float aspect = static_cast<float>(ws->width) / static_cast<float>(ws->height);

	projection = glm::ortho (0.f, static_cast<float>(ws->width), 0.f, static_cast<float>(ws->height), -1.0f, 10.f);
	
	model = glm::mat4(1.0f);
	rotate = glm::mat4(1.0f);
	scale = glm::mat4(1.0f);

	vdata = downloader_load_sprite (res);
	shader = getIShader(thsader);

	uint32_t count = vdata->f_count;

	vao = new uint32_t[count];
	vbo = new uint32_t[count];

	glGenBuffers (count, vbo);
	glGenVertexArrays (count, vao);
	
	for (int i = 0; i < count; i++) {
		
		glBindVertexArray (vao[i]);
		glBindBuffer (GL_ARRAY_BUFFER, vbo[i]);
		glBufferData (GL_ARRAY_BUFFER, sizeof (float) * 30, vdata->f[i], GL_STATIC_DRAW);

		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof (float) * 5, (void *) 0);
		glEnableVertexAttribArray (0);
		glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, sizeof (float) * 5, (void *) (sizeof(float) * 3));
		glEnableVertexAttribArray (1);

		glBindBuffer (GL_ARRAY_BUFFER, 0);
		glBindVertexArray (0);

	}
	
	max_vertex = 6;
}

Object::Object(MODEL_ASSET res, TYPE_SHADERS tshader, bool dependies)
{
	bonus = nullptr;
	cur_tex = 0;
	cur_frame = 0;

	
	typeRes = res;

	WindowSize* ws = WindowSize::getInstance();
	
	float aspect = static_cast<float>(ws->width) / static_cast<float>(ws->height);

	projection = glm::perspective (glm::radians(45.f), aspect, 0.1f, 1000.f);
	
	model = glm::mat4(1.0f);
	rotate = glm::mat4(1.0f);
	scale = glm::mat4(1.0f);

	vdata = downloader_object_load (res);
	shader = getIShader(tshader);

	uint32_t count = vdata->f_count;

	vao = new uint32_t[count];
	vbo = new uint32_t[count];

	aabb_box.min = glm::vec3(FLT_MAX);
	aabb_box.max = glm::vec3(-FLT_MAX);


	for (uint32_t i = 0; i < vdata->size; i++) {
		glm::vec3 point;
		 point.x = vdata->f[0][i * 8 + 0];
		 point.y = vdata->f[0][i * 8 + 1];
		 point.z = vdata->f[0][i * 8 + 2];

		 if (point.x < aabb_box.min.x) aabb_box.min.x = point.x; 
		 if (point.y < aabb_box.min.y) aabb_box.min.y = point.y;
		 if (point.z < aabb_box.min.z) aabb_box.min.z = point.z;

		if (point.x > aabb_box.max.x) aabb_box.max.x = point.x;
		if (point.y > aabb_box.max.y) aabb_box.max.y = point.y;
		if (point.z > aabb_box.max.z) aabb_box.max.z = point.z;
	}

	
	glGenBuffers (count, vbo);
	glGenVertexArrays (count, vao);
	for (int i = 0; i < count; i++) {
		
		glBindVertexArray (vao[i]);
		glBindBuffer (GL_ARRAY_BUFFER, vbo[i]);
		glBufferData (GL_ARRAY_BUFFER, sizeof (float) * vdata->size * 24, vdata->f[i], GL_STATIC_DRAW);

		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof (float) * 8, (void *) 0);
		glEnableVertexAttribArray (0);
		glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, sizeof (float) * 8, (void *) (sizeof(float) * 3));
		glEnableVertexAttribArray (1);
		glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, sizeof (float) * 8, (void *) (sizeof(float) * 5));
		glEnableVertexAttribArray (2);

		glBindBuffer (GL_ARRAY_BUFFER, 0);
		glBindVertexArray (0);

	}
	
	max_vertex = vdata->size * 24;
}

Object::Object(TYPE_SHADERS tshader)
{
	bonus = nullptr;
	cur_tex = 0;
	cur_frame = 0;

	WindowSize* ws = WindowSize::getInstance();
	
	float aspect = static_cast<float>(ws->width) / static_cast<float>(ws->height);

	projection = glm::perspective (glm::radians(45.f), aspect, 0.1f, 100.f);
	
	model = glm::mat4(1.0f);
	rotate = glm::mat4(1.0f);
	scale = glm::mat4(1.0f);

	shader = getIShader(tshader);

	
}

void Object::setPos(glm::vec3 &p)
{
	pos = p;

	translate = glm::translate(model, pos);

	if (bonus) {
		glm::vec3 bp = pos;
		bp.y = 0.74f;
		bonus->setPos(bp);
	}
}

void Object::move(float _x, float _z)
{
	pos.x += _x;
	pos.z += _z;

	translate = glm::translate(model, pos);
}

void Object::render ()
{
	shader->render(this);

	if (bonus) {
		bonus->step();
		bonus->render();
	}
}
