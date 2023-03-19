#ifndef ENGINE_ANIMATION_HEADER_H
#define ENGINE_ANIMATION_HEADER_H

#include <stdint.h>

struct Anim;

Anim* anim_init(const int size);
void anim_set(struct Anim* an, const uint32_t index, const uint32_t first, const uint32_t last, const uint32_t milliseconds);
uint32_t anim_run(struct Anim* an, const uint32_t index, const uint32_t once);
void anim_stop(struct Anim* an, const uint32_t index);

#endif
