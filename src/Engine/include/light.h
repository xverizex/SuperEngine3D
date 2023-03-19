#ifndef ENGINE_LIGHT_HEADER_H
#define ENGINE_LIGHT_HEADER_H
#include <glm/glm.hpp>

class Light {
	public:
		static Light* getInstance();
		void init (uint32_t size);
		void setPos (uint32_t index, float x, float y, float z);
		void setColor (uint32_t index, float r, float g, float b);
		float* pos;
		float* color;

	private:
		Light();
};

#endif
