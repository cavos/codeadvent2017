#include "stdafx.h"
#include "day03_SpiralMemory.h"


SpiralMemory::SpiralMemory()
{
}


SpiralMemory::~SpiralMemory()
{
}

void SpiralMemory::update(const unsigned dataLocation,
						  SpiralMemory::State *pState,
						  SpiralMemory::Direction *pDirection)
{
	unsigned stepsToMove;
	if (dataLocation >= pState->data + pDirection->step)
		stepsToMove = pDirection->step;
	else
		stepsToMove = dataLocation - pState->data;
		
	pState->data += stepsToMove;
	pDirection->pos += stepsToMove * pDirection->direction;
	pDirection->step -= stepsToMove;
}

unsigned SpiralMemory::compute(unsigned dataRequested)
{
	State state(1, 1);
	Direction xDir(0, 1, 1);
	Direction yDir(0, 1, 1);

	while (state.data != dataRequested)
	{
		if (xDir.step > 0)
			update(dataRequested, &state, &xDir);
		if (yDir.step > 0)
			update(dataRequested, &state, &yDir);
		if (xDir.step == 0 && yDir.step == 0) {
			state.step += 1;
			xDir.step = yDir.step = state.step;

			xDir.direction *= -1;
			yDir.direction *= -1;
		}
	}

	return abs(xDir.pos) + abs(yDir.pos);
}
