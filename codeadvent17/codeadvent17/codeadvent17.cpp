// codeadvent17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "day01_InverseCaptcha.h"
#include "day02_CorruptionChecksum.h"
#include "day03_SpiralMemory.h"
#include "day04_HighEntropyPassphrases.h"

int main()
{
	InverseCaptcha inv;
	std::cout << "day01: " << InverseCaptcha::compute(InverseCaptcha::testinput) << "\n";
	std::cout << "day02: " << CorruptionChecksum::compute(CorruptionChecksum::testinput) << "\n";
	std::cout << "day03: " << SpiralMemory::compute(361527) << "\n";
	std::cout << "day04: " << HighEntropyPassphrases::compute(HighEntropyPassphrases::testinput) << "\n";
	system("pause");

    return 0;
}

