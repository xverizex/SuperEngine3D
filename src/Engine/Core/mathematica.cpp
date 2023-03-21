#include <stdint.h>
#include <stdio.h>
#include <main.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shaders.h>
#include "mathematic.h"
#include <camera.h>
#include <limits>


glm::vec2 ray_intersect_AABB (glm::vec3 &orig, glm::vec3 &dir, Object *obj)
{
	
	
	glm::vec3 inv_dir = 1.f / dir;

		
	glm::vec3 min = obj->pos + obj->aabb_box.min;
	glm::vec3 max = obj->pos + obj->aabb_box.max;

	
	glm::vec3 mi = min;
	glm::vec3 ma = max;

#if 0
	printf ("amin: %f %f %f %f %f %f\n", min.x, min.y, min.z, max.x, max.y, max.z);
#endif

	glm::vec3 tMin = (mi - orig) * inv_dir;
	glm::vec3 tMax = (ma - orig) * inv_dir;

	glm::vec3 t1 = glm::min(tMin, tMax);
	glm::vec3 t2 = glm::max(tMin, tMax);

	float tNear = glm::max(glm::max(t1.x, t1.y), t1.z);
	float tFar = glm::min(glm::min(t2.x, t2.y), t2.z);

	return glm::vec2(tNear, tFar);
}

int ray_picking_depth(int x, int y, std::vector<Object *> &en)
{
	float winZ = 0;
	WindowSize *ws = WindowSize::getInstance();

	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);


	glm::mat4 &cam = get_shader_cam();
	glm::mat4 projection = glm::perspective(glm::radians(45.f), ws->aspect, 0.1f, 1000.f);

	glm::vec3 objPt = glm::unProject(glm::vec3(x, y, winZ), cam, projection, glm::vec4(0, 0, ws->width, ws->height));

	size_t i = 0;
	float minDist = 1000;
	int selected_box = -1;

	uint32_t size = en.size();
	for (i = 0; i < size; i++) {
		float dist = glm::distance(en[i]->pos, objPt);
		if (dist < 1.f && dist < minDist) {
			selected_box = i;
			minDist = dist;
		}
	}

	return selected_box;
}

int ray_picking (int x, int y, std::vector<Object *> &en)
{
	Camera *camera = Camera::getInstance();

	WindowSize *ws = WindowSize::getInstance();

	glm::mat4 &cam = get_shader_cam();

	glm::mat4 projection = glm::perspective(glm::radians(45.f), ws->aspect, 0.1f, 1000.f);

	glm::mat4 model (1.f);

	glm::mat4 MV = cam;

	glm::vec3 start = glm::unProject(glm::vec3(x, y, 0), MV, projection, glm::vec4(0, 0, ws->width, ws->height));
	glm::vec3 end = glm::unProject(glm::vec3(x, y, 1), MV, projection, glm::vec4(0, 0, ws->width, ws->height));

	glm::vec3 dir = glm::normalize(end - start);

#if 0
	printf ("pos: %f %f %f\n", camera->pos.x ,camera->pos.y, camera->pos.z);
	printf ("start end: %f %f %f => %f %f %f\n", start.x, start.y, start.z, end.x, end.y, end.z);
	printf ("dir: %f %f %f\n", dir.x, dir.y, dir.z);

#endif

	
	float tMin = std::numeric_limits<float>::max();

	
	int selected_box = -1;
	uint32_t size = en.size();
	for (int i = 0; i < size; i++) {
		glm::vec2 tMinMax = ray_intersect_AABB(camera->pos, dir, en[i]);

		if (tMinMax.x < tMinMax.y && tMinMax.x < tMin) {
			selected_box = i;
			tMin = tMinMax.x;
		}
	}

	

	return selected_box;
}