#ifndef __linux__
	#include "stdafx.h"
#endif
#include "day03_SpiralMemory.h"

#include <utility>
#include <map>
#include <iostream>

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

unsigned SpiralMemory::compute_pt2(unsigned puzzleInput) {
	State state(1, 1);
	Direction xDir(0, 1, 1);
	Direction yDir(0, 1, 1);

	while (state.data < puzzleInput)
	{
		if (xDir.step > 0) {
			state.currentX += xDir.direction;
			--xDir.step;
		}			
		else if (yDir.step > 0) {
			state.currentY += yDir.direction;
			--yDir.step;
		}

		auto position = std::make_pair(state.currentY, state.currentX);
		state.data = computeValue(state.memory, position);
		state.memory[position] = state.data;

		if (xDir.step == 0 && yDir.step == 0) {
			state.step += 1;
			xDir.step = yDir.step = state.step;
			xDir.direction *= -1;
			yDir.direction *= -1;
		}
	}

	return state.data;
}

unsigned SpiralMemory::computeValue(std::map<std::pair<int, int>, unsigned>& memory, std::pair<int, int>& pos)
{
	unsigned sum = 0;
	for (int y = -1; y <= 1; ++y)
		for (int x = -1; x <= 1; ++x)
			sum += memory[std::make_pair(pos.first + y, pos.second + x)];
	return sum;
}
