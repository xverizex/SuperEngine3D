#ifndef ENGINE_ISHADER_HEADER_H
#define ENGINE_ISHADER_HEADER_H
#include <glad/glad.h>


class IShader {
	public:
		virtual void init () = 0;
		virtual void render (void *_data) = 0;
};

#endif
