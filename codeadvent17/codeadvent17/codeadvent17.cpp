// codeadvent17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "day01_InverseCaptcha.h"
#include "day02_CorruptionChecksum.h"
#include "day03_SpiralMemory.h"
#include "day04_HighEntropyPassphrases.h"
#include "day05_TwistyTrampolines.h"
#include "day06_MemoryReallocation.h"
#include "day07_RecursiveCircus.h"
#include "day08_RegisterProcessor.h"

int main()
{
	InverseCaptcha inv;
	std::cout << "day01: " << InverseCaptcha::compute(InverseCaptcha::testinput) << "\n";
	std::cout << "day01.2: " << InverseCaptcha::compute_pt2(InverseCaptcha::testinput) << "\n";
	std::cout << "day02: " << CorruptionChecksum::compute(CorruptionChecksum::testinput) << "\n";
	std::cout << "day02.2: " << CorruptionChecksum::compute_pt2(CorruptionChecksum::testinput) << "\n";
	std::cout << "day03: " << SpiralMemory::compute(361527) << "\n";
	std::cout << "day04: " << HighEntropyPassphrases::compute(HighEntropyPassphrases::testinput) << "\n";
	std::cout << "day05: " << TwistyTrampolines::compute(TwistyTrampolines::testinput) << "\n";
	std::cout << "day06: " << MemoryReallocation::compute(MemoryReallocation::testinput) << "\n";
	std::cout << "day07: " << RecurisveCircus::compute(RecurisveCircus::testinput2) << "\n";
	std::cout << "day08: " << RegisterProcessor::compute(RegisterProcessor::inputtest) << "\n";
	system("pause");

    return 0;
}

