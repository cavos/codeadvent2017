#pragma once

#include <istream>

class SpiralMemory
{
public:
	SpiralMemory();
	~SpiralMemory();

	static unsigned compute(unsigned dataLocation);

private:
	struct State {
		int data;
		int step;

		State(int data, int step) {
			this->data = data;
			this->step = step;
		}
	};

	struct Direction{
		int pos;
		int step;
		int direction;

		Direction(int pos, int step, int direction) {
			this->pos = pos;
			this->step = step;
			this->direction = direction;
		}
	};

	static void update(const unsigned dataLocation,
					   State *pState,
					   Direction *pDirection);
};

