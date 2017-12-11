#pragma once

#include <istream>
#include <fstream>

class HighEntropyPassphrases
{
public:
	HighEntropyPassphrases();
	~HighEntropyPassphrases();

	static unsigned compute(std::istream& input);
	static unsigned compute_pt2(std::istream& input);

	static std::ifstream testinput;

private:
	static unsigned computeHashcode(const std::string& value);
};

