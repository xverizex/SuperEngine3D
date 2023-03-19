#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>
#include "downloader.h"

static Vdata *vdata[N_ASSETS];
static Vdata *vsprites[N_SPRITE_ASSETS];
static Vdata *vpart[N_PARTICLE_ASSETS];
static Vdata *vsprites_center[N_SPRITE_ASSETS];

static void load_model (const char *filename, MODEL_ASSET asset);
static void load_textures (const char *filename, MODEL_ASSET asset);
static void load_sprite (const char *filename, SPRITE_ASSET asset);
static void load_sprite_center (const char *filename, SPRITE_ASSET asset);

static void load_particle (const char *filename, PARTICLE_ASSET asset);

Vdata *downloader_load_particle_texture (PARTICLE_ASSET asset)
{
	switch (asset) {
		case PARTICLE_TEST:
			if (vpart[PARTICLE_TEST]) break;
			load_particle ("assets/particle_test.texture", PARTICLE_TEST);
			break;
		case SLEEP_CLOUD:
			if (vpart[SLEEP_CLOUD]) break;
			load_particle ("assets/sleep_cloud.texture", SLEEP_CLOUD);
			break;
	}

	return vsprites[asset];
}

Vdata *downloader_load_sprite_center (SPRITE_ASSET asset)
{
	switch (asset) {
		case FIGHT_START:
			if (vsprites_center[FIGHT_START]) break;
			load_sprite_center ("assets/fight_start.texture", FIGHT_START);
			break;
		case SLEEP_ATTACK:
			if (vsprites_center[SLEEP_ATTACK]) break;
			load_sprite_center ("assets/sleep_attack.texture", SLEEP_ATTACK);
			break;
		
	}

	return vsprites_center[asset];
}

Vdata *downloader_load_sprite (SPRITE_ASSET asset)
{
	switch (asset) {
		case FIGHT_START:
			if (vsprites[FIGHT_START]) break;
			load_sprite ("assets/fight_start.texture", FIGHT_START);
			break;
		case SLEEP_ATTACK:
			if (vsprites[SLEEP_ATTACK]) break;
			load_sprite ("assets/sleep_attack.texture", SLEEP_ATTACK);
			break;
	}

	return vsprites[asset];
}

Vdata *downloader_object_load (MODEL_ASSET asset)
{
	switch (asset) {
		case MODEL_TILE_GROUND:
			if (vdata[MODEL_TILE_GROUND]) break;
			load_model ("assets/tile_ground.object", MODEL_TILE_GROUND);
			load_textures ("assets/tile_ground.texture", MODEL_TILE_GROUND);
			break;
		case MODEL_TILE_GRASS:
			if (vdata[MODEL_TILE_GRASS]) break;
			load_model ("assets/tile_grass.object", MODEL_TILE_GRASS);
			load_textures ("assets/tile_grass.texture", MODEL_TILE_GRASS);
			break;
		case MODEL_TILE_BUSHES:
			if (vdata[MODEL_TILE_BUSHES]) break;
			load_model ("assets/tile_bushes.object", MODEL_TILE_BUSHES);
			load_textures ("assets/tile_bushes.texture", MODEL_TILE_BUSHES);
			break;
		case MODEL_TILE_RIVER:
			if (vdata[MODEL_TILE_RIVER]) break;
			load_model ("assets/tile_river.object", MODEL_TILE_RIVER);
			load_textures ("assets/tile_river.texture", MODEL_TILE_RIVER);
			break;
		case MODEL_TILE_TREE:
			if (vdata[MODEL_TILE_TREE]) break;
			load_model ("assets/tile_tree.object", MODEL_TILE_TREE);
			load_textures ("assets/tile_tree.texture", MODEL_TILE_TREE);
			break;
		case MODEL_HUMAN:
			if (vdata[MODEL_HUMAN]) break;
			load_model ("assets/human.object", MODEL_HUMAN);
			load_textures ("assets/human.texture", MODEL_HUMAN);
			break;
		case MODEL_BERRY:
			if (vdata[MODEL_BERRY]) break;
			load_model ("assets/berry.object", MODEL_BERRY);
			load_textures ("assets/berry.texture", MODEL_BERRY);
			break;
		case MODEL_CARD:
			if (vdata[MODEL_CARD]) break;
			load_model ("assets/card.object", MODEL_CARD);
			load_textures ("assets/card.texture", MODEL_CARD);
			break;
		case MODEL_ENEMY_WOLF:
			if (vdata[MODEL_ENEMY_WOLF]) break;
			load_model ("assets/wolf.object", MODEL_ENEMY_WOLF);
			load_textures ("assets/wolf.texture", MODEL_ENEMY_WOLF);
			break;
	}

	return vdata[asset];
}


static int swap_little_big_engian (int num)
{
        return (((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000));
}

static void load_model (const char *filename, MODEL_ASSET asset)
{
	FILE *fp = fopen (filename, "r");
	int lb = 0;
	int count = 0;
	int size;
	fread (&lb, sizeof (int), 1, fp);
	fread (&count, sizeof (int), 1, fp);
	

	vdata[asset] = new Vdata();
	vdata[asset]->f = new float*[count];
	vdata[asset]->f_count = count;
	uint32_t indexf = 0;

	for (int i = 0; i < count; i++) {
		fread (&size, sizeof (int), 1, fp);
		int totl = sizeof (float) * size * 24;
		float *f = new float[sizeof (float) * size * 24];
		int ret = fread (f, 1, totl, fp);
		vdata[asset]->f[indexf++] = f;
	}

	fclose (fp);
		
	vdata[asset]->size = size;
}

static void load_particle (const char *filename, PARTICLE_ASSET asset)
{
	vsprites[asset] = new Vdata();

	FILE *fp = fopen (filename, "r");

	uint8_t *file;

	fseek (fp, 0, SEEK_END);
	uint64_t size_file = ftell (fp);
	fseek (fp, 0, SEEK_SET);

	file = new uint8_t[size_file];
	fread (file, size_file, 1, fp);
	fclose (fp);



	const int LTBE = 0;
        const int COUNT = 1;
        const int WIDTH = 2;
        const int HEIGHT = 3;
        int *pack[4];

        for (int i = 0; i < 4; i++) {
                pack[i] = (int *) &file[i * 4];
        }

        if (*pack[LTBE] != 1) {
                for (int i = 1; i < 4; i++) {
                        *pack[i] = swap_little_big_engian (*pack[i]);
                }
        }

        int size_tex = *pack[COUNT];
        int width = *pack[WIDTH];
        int height = *pack[HEIGHT];

        uint8_t **data = new uint8_t *[size_tex];

        int pos = 4 * sizeof (int);

        int total = width * height * 4;

        for (int i = 0; i < size_tex; i++) {
                data[i] = new uint8_t[total];
                memcpy (data[i], &file[pos], total);
                pos += total;
        }

	vsprites[asset]->tex_count = size_tex;
	vsprites[asset]->tex_width = width;
	vsprites[asset]->tex_height = height;
	vsprites[asset]->data = data;

	vsprites[asset]->tex_sampler = new uint32_t[size_tex];
	glGenTextures (size_tex, vsprites[asset]->tex_sampler);
	

	for (int i = 0; i < size_tex; i++) {
		glBindTexture (GL_TEXTURE_2D, vsprites[asset]->tex_sampler[i]);
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data[i]);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glBindTexture (GL_TEXTURE_2D, 0);
                delete[] data[i];
	}

	//delete[] data;

}

static void load_sprite (const char *filename, SPRITE_ASSET asset)
{
	vsprites[asset] = new Vdata();

	FILE *fp = fopen (filename, "r");

	uint8_t *file;

	fseek (fp, 0, SEEK_END);
	uint64_t size_file = ftell (fp);
	fseek (fp, 0, SEEK_SET);

	file = new uint8_t[size_file];
	fread (file, size_file, 1, fp);
	fclose (fp);



	const int LTBE = 0;
        const int COUNT = 1;
        const int WIDTH = 2;
        const int HEIGHT = 3;
        int *pack[4];

        for (int i = 0; i < 4; i++) {
                pack[i] = (int *) &file[i * 4];
        }

        if (*pack[LTBE] != 1) {
                for (int i = 1; i < 4; i++) {
                        *pack[i] = swap_little_big_engian (*pack[i]);
                }
        }

        int size_tex = *pack[COUNT];
        int width = *pack[WIDTH];
        int height = *pack[HEIGHT];

        uint8_t **data = new uint8_t *[size_tex];

        int pos = 4 * sizeof (int);

        int total = width * height * 4;

        for (int i = 0; i < size_tex; i++) {
                data[i] = new uint8_t[total];
                memcpy (data[i], &file[pos], total);
                pos += total;
        }

	vsprites[asset]->tex_count = size_tex;
	vsprites[asset]->tex_width = width;
	vsprites[asset]->tex_height = height;

	vsprites[asset]->tex_sampler = new uint32_t[size_tex];
	glGenTextures (size_tex, vsprites[asset]->tex_sampler);
	

	for (int i = 0; i < size_tex; i++) {
		glBindTexture (GL_TEXTURE_2D, vsprites[asset]->tex_sampler[i]);
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data[i]);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glBindTexture (GL_TEXTURE_2D, 0);
                delete[] data[i];
	}

	delete[] data;

	float ww = static_cast<float>(width);
	float hh = static_cast<float>(height);


	static float v[30] = {
		0.f, 0.f, 0.0f, 1.0f, 1.0f,
		0.f, hh, 0.0f, 1.0f, 0.0f,
		ww, 0.f, 0.0f, 0.0f, 1.0f,
		ww, 0.f, 0.0f, 0.0f, 1.0f,
		ww, hh, 0.0f, 0.0f, 0.0f,
		0.f, hh, 0.0f, 1.0f, 0.0f
	};

	uint32_t count = 30;
	vsprites[asset]->f = new float*[1];
	vsprites[asset]->f[0] = new float[30];
	vsprites[asset]->f_count = 1;
	vsprites[asset]->size = 30;
	memcpy (vsprites[asset]->f[0], v, sizeof(float) * count);
}

static void load_sprite_center (const char *filename, SPRITE_ASSET asset)
{
	vsprites_center[asset] = new Vdata();

	FILE *fp = fopen (filename, "r");

	uint8_t *file;

	fseek (fp, 0, SEEK_END);
	uint64_t size_file = ftell (fp);
	fseek (fp, 0, SEEK_SET);

	file = new uint8_t[size_file];
	fread (file, size_file, 1, fp);
	fclose (fp);



	const int LTBE = 0;
        const int COUNT = 1;
        const int WIDTH = 2;
        const int HEIGHT = 3;
        int *pack[4];

        for (int i = 0; i < 4; i++) {
                pack[i] = (int *) &file[i * 4];
        }

        if (*pack[LTBE] != 1) {
                for (int i = 1; i < 4; i++) {
                        *pack[i] = swap_little_big_engian (*pack[i]);
                }
        }

        int size_tex = *pack[COUNT];
        int width = *pack[WIDTH];
        int height = *pack[HEIGHT];

        uint8_t **data = new uint8_t *[size_tex];

        int pos = 4 * sizeof (int);

        int total = width * height * 4;

        for (int i = 0; i < size_tex; i++) {
                data[i] = new uint8_t[total];
                memcpy (data[i], &file[pos], total);
                pos += total;
        }

	vsprites_center[asset]->tex_count = size_tex;
	vsprites_center[asset]->tex_width = width;
	vsprites_center[asset]->tex_height = height;

	vsprites_center[asset]->tex_sampler = new uint32_t[size_tex];
	glGenTextures (size_tex, vsprites_center[asset]->tex_sampler);
	

	for (int i = 0; i < size_tex; i++) {
		glBindTexture (GL_TEXTURE_2D, vsprites_center[asset]->tex_sampler[i]);
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data[i]);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glBindTexture (GL_TEXTURE_2D, 0);
                delete[] data[i];
	}

	delete[] data;

	float w, h;
	if (width > height) {
		w = static_cast<float>(1.f);
		float aspect = static_cast<float>(width) / static_cast<float>(height);
		h = w / aspect;
	} else if (width < height) {
		h = static_cast<float>(1.f);
		float aspect = static_cast<float>(height) / static_cast<float>(width);
		w = h / aspect;
	} else {
		h = w = 1.f;
	}

	float ww = static_cast<float>(w);
	float hh = static_cast<float>(h);

#if 0
	static float v[30] = {
		-ww, -hh, 0.0f, 1.0f, 1.0f,
		-ww, hh, 0.0f, 1.0f, 0.0f,
		ww, -hh, 0.0f, 0.0f, 1.0f,
		ww, -hh, 0.0f, 0.0f, 1.0f,
		ww, hh, 0.0f, 0.0f, 0.0f,
		-ww, hh, 0.0f, 1.0f, 0.0f
	};
#else
	static float v[30] = {
		0.f, 0.f, 0.0f, 1.0f, 1.0f,
		0.f, hh, 0.0f, 1.0f, 0.0f,
		ww, 0.f, 0.0f, 0.0f, 1.0f,
		ww, 0.f, 0.0f, 0.0f, 1.0f,
		ww, hh, 0.0f, 0.0f, 0.0f,
		0.f, hh, 0.0f, 1.0f, 0.0f
	};
#endif

	uint32_t count = 30;
	vsprites_center[asset]->f = new float*[1];
	vsprites_center[asset]->f[0] = new float[30];
	vsprites_center[asset]->f_count = 1;
	vsprites_center[asset]->size = 30;
	memcpy (vsprites_center[asset]->f[0], v, sizeof(float) * 30);
}

static void load_textures (const char *filename, MODEL_ASSET asset)
{
	FILE *fp = fopen (filename, "r");

	uint8_t *file;

	fseek (fp, 0, SEEK_END);
	uint64_t size_file = ftell (fp);
	fseek (fp, 0, SEEK_SET);

	file = new uint8_t[size_file];
	fread (file, size_file, 1, fp);
	fclose (fp);

	const int LTBE = 0;
        const int COUNT = 1;
        const int WIDTH = 2;
        const int HEIGHT = 3;
        int *pack[4];

        for (int i = 0; i < 4; i++) {
                pack[i] = (int *) &file[i * 4];
        }

        if (*pack[LTBE] != 1) {
                for (int i = 1; i < 4; i++) {
                        *pack[i] = swap_little_big_engian (*pack[i]);
                }
        }

        int size_tex = *pack[COUNT];
        int width = *pack[WIDTH];
        int height = *pack[HEIGHT];


        uint8_t **data = new uint8_t *[size_tex];

        int pos = 4 * sizeof (int);

        int total = width * height * 4;

        for (int i = 0; i < size_tex; i++) {
                data[i] = new uint8_t[total];
                memcpy (data[i], &file[pos], total);
                pos += total;
        }

	vdata[asset]->tex_width = width;
	vdata[asset]->tex_height = height;

	vdata[asset]->tex_count = size_tex;

	vdata[asset]->tex_sampler = new uint32_t[size_tex];
	glGenTextures (size_tex, vdata[asset]->tex_sampler);

	for (int i = 0; i < size_tex; i++) {
		glBindTexture (GL_TEXTURE_2D, vdata[asset]->tex_sampler[i]);
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data[i]);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glBindTexture (GL_TEXTURE_2D, 0);
                delete[] data[i];
	}

	delete[] data;
}

static int get_count_objects_in_level (char *file)
{
	FILE *fp = fopen (file, "r");
	fseek (fp, 0 - 4, SEEK_END);

	int count = 0;
	fread (&count, sizeof (int), 1, fp);
	fclose (fp);

	return count;
}
