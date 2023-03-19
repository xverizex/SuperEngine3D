#ifndef ENGINE_OBJECT_HEADER_H
#define ENGINE_OBJECT_HEADER_H
#include <stdint.h>
#include <glm/glm.hpp>
#include "vdata.h"
#include "shaders.h"
#include "downloader.h"
#include <glm/gtc/matrix_transform.hpp>

class Bonus;
class Berry;
class IShader; 

class Object {
	public:
		Object(TYPE_SHADERS tshader);
		Object(MODEL_ASSET res, TYPE_SHADERS tshader, bool dependies = true);
		Object(SPRITE_ASSET res, TYPE_SHADERS thsader);
		void setPos(glm::vec3 &_pos);
		void move(float x, float z);
		void render();

		MODEL_ASSET typeRes;
		Bonus *bonus;

		char name[32];
		uint32_t cur_frame;
	
		uint32_t v_size;
		Vdata *vdata;

		glm::vec3 pos;

		int max_vertex;
		int cur_tex;

		uint32_t *tex;
		uint32_t sz_tex;

		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 translate;
		glm::mat4 model;
		glm::mat4 rotate;
		glm::mat4 scale;
	
		uint32_t *vbo;
		uint32_t *vao;

		IShader *shader;

		uint32_t shader_type;
		uint32_t program;
};

#endif
