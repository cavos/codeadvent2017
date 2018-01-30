#include "stdafx.h"
#include "day16_PermutationPromenade.h"

#include <iostream>
#include <map>
#include <algorithm>


PermutationPromenade::PermutationPromenade()
{
}


PermutationPromenade::~PermutationPromenade()
{
}

std::string PermutationPromenade::compute(std::istream & input, const std::string& dancersPositions)
{
	std::string dancers = dancersPositions;
	std::string danceMove;
	while (std::getline(input, danceMove, ','))	
	{
		switch (danceMove[0])
		{
			case 's':
			{
				int spinCnt = std::stoi(danceMove.substr(1));
				std::string tmp = dancers.substr(dancers.length() - spinCnt);
				dancers = dancers.substr(dancers.length() - spinCnt) + dancers.substr(0, dancers.length() - spinCnt);
			}
			break;

			case 'x':
			{
				size_t sepPos = danceMove.find('/');
				int a = std::stoi(danceMove.substr(1, sepPos));
				int b = std::stoi(danceMove.substr(sepPos + 1));
				std::iter_swap(dancers.begin() + a, dancers.begin() + b);
			}
			break;

			case 'p':
				std::iter_swap(dancers.begin() + dancers.find(danceMove[1]), dancers.begin() + dancers.find(danceMove[3]));
				break;
		}
	}

	return dancers;
}

std::string PermutationPromenade::compute_pt2(std::istream & input)
{
	std::vector<std::tuple<char, char, char>> danceMoves = parse(input);
	std::vector<std::pair<std::string, std::string>> knownDances;

	std::string dancers = "abcdefghijklmnop";
	for (unsigned long long i = 0; i < 1000; ++i)
	{
		auto it = std::find_if(knownDances.begin(), knownDances.end(), [&](auto& p) {return p.first == dancers; });
		if (it == knownDances.end())
		{
			std::string dancersOut = dance(dancers, danceMoves);
			knownDances.push_back(std::make_pair(dancers, dancersOut));
			dancers = dancersOut;
		}
		else
			dancers = it->second;
	}

	return knownDances[1000000000 % knownDances.size()].first;
}

std::vector<std::tuple<char, char, char>> PermutationPromenade::parse(std::istream& input)
{
	std::vector<std::tuple<char, char, char>> danceMoves;
	std::string danceMove;
	while (std::getline(input, danceMove, ','))
	{
		switch (danceMove[0])
		{
			case 's':
			{
				int spinCnt = std::stoi(danceMove.substr(1));
				danceMoves.emplace_back(std::make_tuple(danceMove[0], spinCnt, 0));
			}
			break;

			case 'x':
			{
				size_t sepPos = danceMove.find('/');
				int a = std::stoi(danceMove.substr(1, sepPos));
				int b = std::stoi(danceMove.substr(sepPos + 1));
				danceMoves.emplace_back(std::make_tuple(danceMove[0], a, b));
			}
			break;

			case 'p':
				danceMoves.emplace_back(std::make_tuple(danceMove[0], danceMove[1], danceMove[3]));
				break;
		}
	}

	return danceMoves;
}

std::string PermutationPromenade::dance(std::string dancers, const std::vector<std::tuple<char, char, char>>& danceMoves)
{
	for (auto danceMove : danceMoves)
	{
		switch (std::get<0>(danceMove))
		{
			case 's':
			{
				std::string tmp = dancers.substr(dancers.length() - std::get<1>(danceMove));
				dancers = dancers.substr(dancers.length() - std::get<1>(danceMove)) + dancers.substr(0, dancers.length() - std::get<1>(danceMove));
			}
			break;

			case 'x':
				std::iter_swap(dancers.begin() + std::get<1>(danceMove), dancers.begin() + std::get<2>(danceMove));
				break;

			case 'p':
				std::iter_swap(dancers.begin() + dancers.find(std::get<1>(danceMove)), dancers.begin() + dancers.find(std::get<2>(danceMove)));
				break;
		}
	}
	
	return dancers;
}

std::ifstream PermutationPromenade::input("day16_input.txt");
