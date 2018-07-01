#include "AND.h"
namespace LE_Library {

	AND::AND(gateType _type) : Gate(_type) {

		defaultValue = 0;
		elemFlag = eAND;
		name = "AND_";
		name += std::to_string(indx);

		for (int i = 0; i < IO.input_count; i++)
		{
			IO.input.push_back(defaultValue);
		}

		this->RefreshLogic();
	}
	void AND::RefreshLogic()
	{
		int countOfOnes = count_if(IO.input.begin(), IO.input.end(), [](int i) { return i == 1; });

		if (countOfOnes == IO.input_count)
		{
			IO.output = 1;
		}
		else
		{
			IO.output = 0;
		}
	}
	AND::~AND()
	{
		std::cout << "Destruktor AND\n";
	}

}