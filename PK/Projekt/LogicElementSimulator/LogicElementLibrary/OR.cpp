#include "OR.h"
namespace LE_Library {

	OR::OR(gateType _type) : Gate(_type) {

		defaultValue = 0;
		elemFlag = eOR;
		name = "OR_";
		name += std::to_string(indx);

		for (int i = 0; i < IO.input_count; i++)
		{
			IO.input.push_back(defaultValue);
		}

		this->RefreshLogic();
	}
	void OR::RefreshLogic()
	{
		int countOfZeros = count_if(IO.input.begin(), IO.input.end(), [](int i) { return i == 0; });

		if (countOfZeros == IO.input_count)
		{
			IO.output = 0;
		}
		else
		{
			IO.output = 1;
		}
	}
	OR::~OR()
	{
		std::cout << "Destruktor OR\n";
	}

}