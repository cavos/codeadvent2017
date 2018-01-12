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
#include "day09_StreamProcessing.h"
#include "day10_KnotHash.h"
#include "day11_HexEd.h"
#include "day12_DigitalPlumber.h"

int main()
{
	InverseCaptcha inv;
	std::cout << "day01: " << InverseCaptcha::compute(InverseCaptcha::testinput) << "\n";
	std::cout << "day01.2: " << InverseCaptcha::compute_pt2(InverseCaptcha::testinput) << "\n";
	std::cout << "day02: " << CorruptionChecksum::compute(CorruptionChecksum::testinput) << "\n";
	std::cout << "day02.2: " << CorruptionChecksum::compute_pt2(CorruptionChecksum::testinput) << "\n";
	std::cout << "day03: " << SpiralMemory::compute(361527) << "\n";
	std::cout << "day03.2: " << SpiralMemory::compute_pt2(361527) << "\n";
	std::cout << "day04: " << HighEntropyPassphrases::compute(HighEntropyPassphrases::testinput) << "\n";
	std::cout << "day04.2: " << HighEntropyPassphrases::compute_pt2(HighEntropyPassphrases::testinput) << "\n";
	std::cout << "day05: " << TwistyTrampolines::compute(TwistyTrampolines::testinput, false) << "\n";
//	std::cout << "day05.2: " << TwistyTrampolines::compute(TwistyTrampolines::testinput/*std::stringstream("0\n3\n0\n1\n-3")*/, true) << "\n";
	auto day6 = MemoryReallocation::compute(MemoryReallocation::testinput);
	std::cout << "day06: " << day6.first << "\n";
	std::cout << "day06.2: " << day6.second << "\n";
	std::cout << "day07: " << RecurisveCircus::compute(RecurisveCircus::testinput2) << "\n";
	std::cout << "day07.2: " << RecurisveCircus::compute_pt2(RecurisveCircus::testinput2) << "\n";
	std::cout << "day08: " << RegisterProcessor::compute(RegisterProcessor::inputtest) << "\n";
	std::cout << "day09: " << StreamProcessing::compute(StreamProcessing::puzzleInput) << "\n";
	//std::cout << "day10: " << KnotHash::compute(256, KnotHash::puzzleInput) << "\n";
	std::cout << "day10.2: " << KnotHash::compute_pt2(KnotHash::puzzleInput /* std::stringstream("1,2,3") */) << "\n";
	auto day11 = HexEd::compute(std::ifstream(HexEd::testInput));
	std::cout << "day11: " << day11.first << "\n";
	std::cout << "day11.2: " << day11.second << "\n";
	auto day12 = DigitalPlumber::compute(std::ifstream(DigitalPlumber::testInput));
	std::cout << "day12: " << day12.first << "\n";
	std::cout << "day12.2: " << day12.second << "\n";
	
	system("pause");

    return 0;
}

