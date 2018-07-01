#include "NAND.h"
namespace LE_Library {

	NAND::NAND(gateType _type) : Gate(_type) {

		defaultValue = 1;
		elemFlag = eNAND;
		name = "NAND_";
		name += std::to_string(indx);

		for (int i = 0; i < IO.input_count; i++)
		{
			IO.input.push_back(defaultValue);
		}

		this->RefreshLogic();
	}
	void NAND::RefreshLogic()
	{
		int countOfOnes = count_if(IO.input.begin(), IO.input.end(), [](int i) { return i == 1; });

		if (countOfOnes == IO.input_count)
		{
			IO.output = 0;
		}
		else
		{
			IO.output = 1;
		}
	}
	NAND::~NAND()
	{
		std::cout << "Destruktor NAND\n";
	}

}