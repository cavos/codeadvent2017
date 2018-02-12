#ifndef __linux__
	#include "stdafx.h"
#endif
#include "day15_DuelingGenerators.h"

#include <iostream>

DuelingGenerators::DuelingGenerators()
{
}


DuelingGenerators::~DuelingGenerators()
{
}

unsigned DuelingGenerators::compute(unsigned long long valueA, unsigned long long valueB)
{
	auto genA = [](unsigned long long value) { return (value * 16807) % 2147483647; };
	auto genB = [](unsigned long long value) { return (value * 48271) % 2147483647; };
	
	unsigned count = 0;
	for (int i = 0; i < 40000000; ++i)
	{
		valueA = genA(valueA);
		valueB = genB(valueB);
		if ((valueA & 0xFFFF) == (valueB & 0xFFFF))
			count++;
	}

	return count;
}

unsigned DuelingGenerators::compute_pt2(unsigned long long valueA, unsigned long long valueB)
{
	auto genA = [](unsigned long long value) {
		do {
			value = (value * 16807) % 2147483647;
		} while (value % 4);
		return value;
	};
	auto genB = [](unsigned long long value) {
		do {
			value = (value * 48271) % 2147483647;
		} while (value % 8);
		return value;
	};

	unsigned count = 0;
	for (int i = 0; i < 5000000; ++i)
	{
		valueA = genA(valueA);
		valueB = genB(valueB);
		if ((valueA & 0xFFFF) == (valueB & 0xFFFF))
			count++;
	}

	return count;
}
