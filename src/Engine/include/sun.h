#ifndef ENGINE_SUN_HEADER_H
#define ENGINE_SUN_HEADER_H

#include <glm/glm.hpp>

class Sun {
	public:
		static Sun* getInstance();
		void init (uint32_t size);
		void setPos (uint32_t index, float x, float y, float z);
		void setColor (uint32_t index, float r, float g, float b);
		void setDirection (uint32_t index, float x, float y, float z);
		float* pos;
		float* color;
		float* direction;

	private:
		Sun();
};

#endif
