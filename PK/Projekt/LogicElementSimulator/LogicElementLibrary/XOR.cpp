#include "XOR.h"
namespace LE_Library {

	XOR::XOR(gateType _type) : Gate(_type) {

		defaultValue = 0;
		elemFlag = eXOR;
		name = "XOR_";
		name += std::to_string(indx);

		for (int i = 0; i < IO.input_count; i++)
		{
			IO.input.push_back(defaultValue);
		}

		this->RefreshLogic();
	}
	void XOR::RefreshLogic()
	{
		int countOfOnes = count_if(IO.input.begin(), IO.input.end(), [](int i) { return i == 1; });

		if (countOfOnes % 2 == 1)
		{
			IO.output = 1;
		}
		else
		{
			IO.output = 0;
		}
	}
	XOR::~XOR()
	{
		std::cout << "Destruktor XOR\n";
	}

}