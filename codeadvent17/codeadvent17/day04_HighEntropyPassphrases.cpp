#include "stdafx.h"
#include "day04_HighEntropyPassphrases.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream>

HighEntropyPassphrases::HighEntropyPassphrases()
{
}

HighEntropyPassphrases::~HighEntropyPassphrases()
{
}

unsigned HighEntropyPassphrases::compute(std::istream & input)
{
	unsigned validPassphraseCount = 0;

	std::string line;
	std::vector<std::pair<unsigned, std::string>> passphraseContents;
	while (std::getline(input, line))
	{
		bool duplicateWordFound = false;
		std::stringstream inputLine(line);
		do
		{
			std::string passphraseValue;
			std::getline(inputLine, passphraseValue, ' ');
			auto passphraseToken = std::make_pair(computeHashcode(passphraseValue), passphraseValue);

			auto iter = std::find_if(passphraseContents.begin(), passphraseContents.end(), [&](auto item) {
				return passphraseToken.first == item.first && passphraseToken.second == item.second;
			});
			
			duplicateWordFound = (iter != passphraseContents.end());
			passphraseContents.emplace_back(passphraseToken);
		} while (!inputLine.eof() && !duplicateWordFound);

		if (!duplicateWordFound)
			validPassphraseCount++;
		passphraseContents.clear();
	}

	input.clear();
	input.seekg(0, std::ios::beg);
	return validPassphraseCount;
}

unsigned HighEntropyPassphrases::computeHashcode(const std::string& value) {
	unsigned hashcode = 0;
	for (auto c : value)
		hashcode += c * 17;

	return hashcode;
}

unsigned HighEntropyPassphrases::compute_pt2(std::istream & input)
{
	unsigned validPassphraseCount = 0;

	std::string line;
	std::vector< std::string> passphraseContents;
	while (std::getline(input, line))
	{
		bool duplicateWordFound = false;
		std::stringstream inputLine(line);
		do
		{
			std::string passphraseValue;
			std::getline(inputLine, passphraseValue, ' ');
			std::sort(passphraseValue.begin(), passphraseValue.end());

			auto iter = std::find_if(passphraseContents.begin(), passphraseContents.end(), [&](auto item) {
				return item == passphraseValue;
			});

			duplicateWordFound = (iter != passphraseContents.end());
			passphraseContents.emplace_back(passphraseValue);
		} while (!inputLine.eof() && !duplicateWordFound);

		if (!duplicateWordFound)
			validPassphraseCount++;
		passphraseContents.clear();
	}

	input.clear();
	input.seekg(0, std::ios::beg);
	return validPassphraseCount;
}


std::ifstream HighEntropyPassphrases::testinput("day04_input.txt", std::ifstream::in);