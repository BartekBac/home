#include "NOR.h"
namespace LE_Library {

	NOR::NOR(gateType _type) : Gate(_type) {

		defaultValue = 1;
		elemFlag = eNOR;
		name = "NOR_";
		name += std::to_string(indx);

		for (int i = 0; i < IO.input_count; i++)
		{
			IO.input.push_back(defaultValue);
		}

		this->RefreshLogic();
	}
	void NOR::RefreshLogic()
	{
		int countOfZeros = count_if(IO.input.begin(), IO.input.end(), [](int i) { return i == 0; });

		if (countOfZeros == IO.input_count)
		{
			IO.output = 1;
		}
		else
		{
			IO.output = 0;
		}
	}
	NOR::~NOR()
	{
		std::cout << "Destruktor NOR\n";
	}

}