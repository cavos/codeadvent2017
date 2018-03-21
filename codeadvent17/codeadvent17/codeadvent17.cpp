// codeadvent17.cpp : Defines the entry point for the console application.
//

#ifndef __linux__
	#include "stdafx.h"
#endif
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
#include "day14_DiskDefragmentation.h"
#include "day17_Spinlock.h"
#include "day18_Duet.h"
#include "day19_SeriesOfTubes.h"
#include "day20_ParticleSwarm.hpp"

int main()
{
	//InverseCaptcha inv;
// 	std::cout << "day01: " << InverseCaptcha::compute(InverseCaptcha::testinput) << "\n";
// 	std::cout << "day01.2: " << InverseCaptcha::compute_pt2(InverseCaptcha::testinput) << "\n";
// 	std::cout << "day02: " << CorruptionChecksum::compute(CorruptionChecksum::testinput) << "\n";
// 	std::cout << "day02.2: " << CorruptionChecksum::compute_pt2(CorruptionChecksum::testinput) << "\n";
// 	std::cout << "day03: " << SpiralMemory::compute(361527) << "\n";
// 	std::cout << "day03.2: " << SpiralMemory::compute_pt2(361527) << "\n";
// 	std::cout << "day04: " << HighEntropyPassphrases::compute(HighEntropyPassphrases::testinput) << "\n";
// 	std::cout << "day04.2: " << HighEntropyPassphrases::compute_pt2(HighEntropyPassphrases::testinput) << "\n";
// 	std::cout << "day05: " << TwistyTrampolines::compute(TwistyTrampolines::testinput, false) << "\n";
// //	std::cout << "day05.2: " << TwistyTrampolines::compute(TwistyTrampolines::testinput/*std::stringstream("0\n3\n0\n1\n-3")*/, true) << "\n";
// 	auto day6 = MemoryReallocation::compute(MemoryReallocation::testinput);
// 	std::cout << "day06: " << day6.first << "\n";
// 	std::cout << "day06.2: " << day6.second << "\n";
// 	std::cout << "day07: " << RecurisveCircus::compute(RecurisveCircus::testinput2) << "\n";
// 	std::cout << "day07.2: " << RecurisveCircus::compute_pt2(RecurisveCircus::testinput2) << "\n";
// 	std::cout << "day08: " << RegisterProcessor::compute(RegisterProcessor::inputtest) << "\n";
// 	std::cout << "day09: " << StreamProcessing::compute(StreamProcessing::puzzleInput) << "\n";
// 	//std::cout << "day10: " << KnotHash::compute(256, KnotHash::puzzleInput) << "\n";
// 	std::cout << "day10.2: " << KnotHash::compute_pt2(KnotHash::puzzleInput /* std::stringstream("1,2,3") */) << "\n";
// 	auto day11 = HexEd::compute(std::ifstream(HexEd::testInput));
// 	std::cout << "day11: " << day11.first << "\n";
// 	std::cout << "day11.2: " << day11.second << "\n";
// 	auto day12 = DigitalPlumber::compute(std::ifstream(DigitalPlumber::testInput));
// 	std::cout << "day12: " << day12.first << "\n";
// 	std::cout << "day12.2: " << day12.second << "\n";
	// auto d14 = DiskDefragmentation::compute(std::string("flqrgnkx"));
	// std::cout << "day14-1: "  << d14.first << '\n';
 	// std::cout << "day14-2: "  << d14.second << '\n';
	// std::cout << "day17: " << Spinlock::compute(304) << '\n';
	// std::cout << "day17.2: " << Spinlock::compute_pt2(304) << '\n';

// std::stringstream d18in("snd 1\nsnd 2\nsnd p\nrcv a\nrcv b\nrcv c\nrcv d");
// 	std::cout << "day18: " << Duet::compute_pt2(Duet::test_input) << '\n';
	// std::cout << "day18: " << Duet::compute_pt2(d18in) << '\n';
	// auto d19in = std::ifstream("day19_input.txt");
	// std::cout << "day19: " << SeriesOfTubes::compute(d19in);
	std::stringstream d20test("p=<3,0,0>, v=<2,0,0>, a=<-1,0,0>\np=<4,0,0>, v=<0,0,0>, a=<-2,0,0>");
	auto d20input = std::ifstream("day20_input.txt");
	std::cout << "day20: " << ParticleSwarm::compute_pt2(d20input);

#ifndef __linux__	
	system("pause");
#else
	std::cout << '\n';
#endif

    return 0;
}

