
#include "Math/MathTest.h"

#include <iostream>

int main()
{
	std::vector<float> a = { 1,2,3,4 };
	std::vector<float> b = { 1,2,3,4 };
	std::vector<float> c = { 0,0,0,0 };
	GE::BatchAdd(a, b, c);
	for (auto cc : c)
	{
		std::cout << cc << std::endl;
	}
	return 0;
}