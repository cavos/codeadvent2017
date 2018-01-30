#pragma once
class DuelingGenerators
{
public:
	DuelingGenerators();
	~DuelingGenerators();

	static unsigned compute(unsigned long long seedA, unsigned long long seedB);
	static unsigned compute_pt2(unsigned long long seedA, unsigned long long seedB);
};

