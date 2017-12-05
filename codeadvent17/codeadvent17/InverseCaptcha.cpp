#include "stdafx.h"
#include "InverseCaptcha.h"

InverseCaptcha::InverseCaptcha()
{
}


InverseCaptcha::~InverseCaptcha()
{
}

unsigned InverseCaptcha::compute(std::istream& inputStream)
{
	int current = inputStream.get() - 48;
	int first = current;
	int next = inputStream.get() - 48;
	unsigned sum = 0;
	while (!inputStream.eof())
	{	
		if (current == next)
			sum += current;

		current = next;
		next = inputStream.get() - 48;
	}

	if (first == current)
		sum += first;

	return sum;
}
