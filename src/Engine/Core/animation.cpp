#include "animation.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct Anim {
	uint32_t first;
	uint32_t last;
	uint32_t cur_frame;
	uint32_t ms;
	uint32_t once;
	struct Times* tm;
};


Anim* anim_init(const int size)
{
	Anim* an = new Anim[size];
	for (int i = 0; i < size; i++) {
		an[i].tm = timer_init(1);
	}


	return an;
}

void
anim_set(Anim* an, const uint32_t index, const uint32_t first, const uint32_t last, const uint32_t milliseconds)
{
	an[index].first = first;
	an[index].last = last;
	an[index].ms = milliseconds;
	an[index].cur_frame = first;
}

uint32_t
anim_run(Anim* an, const uint32_t index, const uint32_t once)
{
	Anim* a = &an[index];
	a->once = once;

	int ret = timer_run(a->tm, 0, a->ms);
	a->cur_frame += ret;
	if (a->cur_frame > a->last) {
		a->cur_frame = a->first;
		if (a->once == 1) {
			a->once = 2;
		}
	}

	if (a->once == 2) {
		
		a->cur_frame = a->last;
		return a->last;
	}

	return a->cur_frame;
}

void
anim_stop(Anim* an, const uint32_t index)
{

}