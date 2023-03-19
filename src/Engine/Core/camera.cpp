#include "camera.h"
#include "shaders.h"
#include <glm/gtc/matrix_transform.hpp>

static Camera *global;

Camera::Camera()
{
	pos = glm::vec3(0.f);
}

Camera *Camera::getInstance()
{
	if (!global) global = new Camera ();
	return global;
}
void Camera::setPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Camera::setEye(float x, float y, float z)
{
	eye.x = x;
	eye.y = y;
	eye.z = z;
}

void Camera::commitAfterSet()
{
	glm::mat4 &cam = get_shader_cam();

	cam = glm::lookAt(pos, eye, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::move(float x, float z)
{
	pos.x += x;
	pos.z += z;

	eye.x += x;
	eye.z += z;

	glm::mat4 &cam = get_shader_cam();

	cam = glm::lookAt(pos, eye, glm::vec3(0.0f, 1.0f, 0.0f));
}