#ifndef ENGINE_TIMER_HEADER_H
#define ENGINE_TIMER_HEADER_H

#include <stdint.h>

struct Times {
	uint64_t cur;
	uint64_t turn;
};

struct Times* timer_init(const uint32_t size);
uint32_t timer_run(struct Times* t, const uint32_t index, const uint32_t milliseconds);
void timer_clear(struct Times* t);
void timer_stop(struct Times* t, const uint32_t index);

#endif
