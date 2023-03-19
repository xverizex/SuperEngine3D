#ifndef ENGINE_VDATA_HEADER_H
#define ENGINE_VDATA_HEADER_H
#include <stdint.h>

struct Vdata {
	float **f;
	uint32_t f_count;
	int size;

	uint32_t *tex_sampler;
	uint32_t tex_count;

	uint32_t tex_width;
	uint32_t tex_height;

	uint8_t **data;
};


#endif
