#ifndef ENGINE_DOWNLOADER_HEADER_H
#define ENGINE_DOWNLOADER_HEADER_H

#include <stdint.h>
#include "vdata.h"


typedef enum {
	MODEL_TILE_GROUND,
	MODEL_TILE_GRASS,
	MODEL_TILE_BUSHES,
	MODEL_TILE_RIVER,
	MODEL_TILE_TREE,
	MODEL_HUMAN,
	MODEL_BERRY,
	MODEL_CARD,
	MODEL_ENEMY_WOLF,
	N_ASSETS
} MODEL_ASSET;

typedef enum {
	FIGHT_START,
	SLEEP_ATTACK,
	N_SPRITE_ASSETS
} SPRITE_ASSET;

typedef enum {
	PARTICLE_TEST,
	SLEEP_CLOUD,
	N_PARTICLE_ASSETS
} PARTICLE_ASSET;

typedef enum {
	LEVEL_BASE,
	N_LEVELS
} LEVEL_ASSET;


Vdata *downloader_object_load (MODEL_ASSET asset);
Vdata *downloader_load_sprite (SPRITE_ASSET asset);
Vdata *downloader_load_sprite_center (SPRITE_ASSET asset);

Vdata *downloader_load_particle_texture (PARTICLE_ASSET asset);

#endif
