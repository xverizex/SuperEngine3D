#ifndef ENGINE_CAMERA_HEADER_H
#define ENGINE_CAMERA_HEADER_H
#include <glm/glm.hpp>

class Camera {
	public:
		glm::vec3 pos;
		glm::vec3 eye;

		static Camera *getInstance();
		void setPos(float x, float y, float z);
		void setEye(float x, float y, float z);
		void commitAfterSet();
		void move(float x, float z);
	private:
		Camera ();
};

#endif
