#ifndef ENGINE_SHADER_PBR_WITH_SHADOWS_HEADER_H
#define ENGINE_SHADER_PBR_WITH_SHADOWS_HEADER_H
#include "ishader.h"

#include <stdint.h>

enum PBR {
	PBR_ALBEDO,
	PBR_HEIGHT,
	PBR_METALLIC,
	PBR_AO,
	PBR_NORMAL,
	PBR_ROUGHNESS,
	N_PBR
};

class ShaderPBRWithShadows: public IShader {
	public:
		void init () override;
		void render (void *_data) override;

		uint32_t program;
		uint32_t uniform_model;
		uint32_t uniform_cam;
		uint32_t uniform_projection;
		uint32_t uniform_rotate;
		uint32_t uniform_scale;

		uint32_t uniform_sampler_albedo;
		uint32_t uniform_sampler_normal;
		uint32_t uniform_sampler_metallic;
		uint32_t uniform_sampler_roughness;
		uint32_t uniform_sampler_ao;
		uint32_t uniform_point_light_position;
		uint32_t uniform_point_light_color;
		uint32_t uniform_direction_light;
		uint32_t uniform_direction_light_color;
		uint32_t uniform_cam_pos;
		uint32_t uniform_translation;
};

#endif
