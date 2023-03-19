#ifndef ENGINE_ILEVEL_HEADER_H
#define ENGINE_ILEVEL_HEADER_H

#include <stdint.h>

class ILevel {
	public:
		virtual void init () = 0;
		virtual void render () = 0;
		virtual void update () = 0;
		virtual void click (int x, int y) = 0;
};

#endif
