
#include "MathTest.h"
#include "MathTestIspc.h"

namespace GE
{
	void BatchAdd(std::vector<float> &a, std::vector<float> &b, std::vector<float> &c)
	{
		ispc::BatchAdd(a.data(), b.data(), c.data(), a.size());
	}
}
