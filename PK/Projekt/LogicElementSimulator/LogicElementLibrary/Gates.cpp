#include "Gates.h"
#include "Functions.h"

namespace LE_Library {

	GateIO::GateIO(gateType _type)
	{//kontruktor uzupe³niaj¹cy wejœcia/wyjœcia na podstawie danego typu
		if (_type == gateType::two_input)
		{
			input_count = 2;
		}
		else if (_type == gateType::three_input)
		{
			input_count = 3;
		}
		else if (_type == gateType::four_input)
		{
			input_count = 4;
		}
		else
		{
			throw WrongConstructorParameter();
		}

		for (int i = 0; i < input_count; i++)
		{
			input_status.push_back(State::off);
		}
	}
	GateIO::~GateIO()
	{
		input.clear();
		input_status.clear();
	}


	Gate::Gate(gateType _type) : IO(GateIO(_type)) {}

	int Gate::getOUT(int o)
	{
		return IO.output;
	}
	void Gate::setIN(int value, const string lineName, const int i)
	{
		if (lineName != "input") throw IO_BadLineRequest();

		if (IO.input_count > i)
		{//gdy wybrane wejœcie istnieje, ustawiamy wybran¹ wartoœæ
			IO.input[i] = Functions::ParseLogic(value);
		}
		else
		{//inaczej wyrzucamy wyj¹tek
			throw IO_OutOfRange();
		}
		//automatycznie oœwierzamy wartoœæ na wyjœciu
		this->RefreshLogic();
	}
	map<string, vector<int>> Gate::ReturnAccessibleInputs()
	{
		//parsowanie wyboru wejœcia
		int countOfAccesibleInputs = count_if(IO.input_status.begin(), IO.input_status.end(), [](State s) { return s == State::off;  });
		if (countOfAccesibleInputs == 0)
			throw LEexception("Wejscia sa juz zajete");

		map<string, vector<int>> retMap;
		vector<int> accessibleInputsVector;

		for (int i = 0; i < IO.input_count; i++)
		{
			if (IO.input_status[i] == State::off)
			{
				accessibleInputsVector.push_back(i);
			}
		}

		retMap.insert(pair<string, vector<int>>("input", accessibleInputsVector));
		return retMap;
	}
	vector<int> Gate::ReturnAccessibleOutputs()
	{
		vector<int> retVec;
		retVec.push_back(0);
		return retVec;
	}
	void Gate::UpdateInputState(int i, string lineName, State s)
	{
		if (lineName != "input") throw IO_BadLineRequest();

		if (IO.input_count > i)
		{
			IO.input_status[i] = s;
		}
		else
		{
			throw IO_OutOfRange();
		}
	}

	map<string, vector<int>> Gate::ReturnIOState()
	{
		map<string, vector<int>> retMap;
		vector<int> outVec;
		outVec.push_back(IO.output);
		retMap.insert(pair<string, vector<int>>("input", IO.input));
		retMap.insert(pair<string, vector<int>>("output", outVec));
		return retMap;
	}

	Gate::~Gate()
	{
		std::cout << "Destruktor Gate\n";
	}

}
