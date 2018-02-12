#pragma once

#include <istream>
#include <map>
#include <utility>

class SpiralMemory
{
public:
	SpiralMemory();
	~SpiralMemory();

	static unsigned compute(unsigned dataLocation);
	static unsigned compute_pt2(unsigned dataLocation);

private:
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

	struct State {
		unsigned data;
		unsigned step;
		std::map<std::pair<int, int>, unsigned> memory;
		int currentX = 0;
		int currentY = 0;

		State(unsigned data, unsigned step) {
			this->data = data;
			this->step = step;

			memory[std::make_pair(0, 0)] = 1;
		}
	};

	static void update(const unsigned dataLocation,
					   State *pState,
					   Direction *pDirection);

	static unsigned computeValue(std::map<std::pair<int, int>, unsigned> &memory, std::pair<int, int>& position);
};

