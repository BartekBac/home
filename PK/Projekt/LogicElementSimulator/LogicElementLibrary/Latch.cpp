#include "Latch.h"
#include "Functions.h"
#include <algorithm>
namespace LE_Library {

	Latch::Latch() {

		defaultValue = 0;
		elemFlag = eLatch;
		name = "Latch_";
		name += std::to_string(indx);

		IO.S = 0;
		IO.R = 0;
		IO.Q = 0;
		IO.notQ = 1;
		IO.input_status.push_back(off);
		IO.input_status.push_back(off);
	}

	void Latch::RefreshLogic()
	{
		if (IO.R == 1)
		{
			IO.Q = 0;
			IO.notQ = 1;
			return;
		}
		if (IO.S == 1)
		{
			IO.Q = 1;
			IO.notQ = 0;
			return;
		}
		//dla SR=00 stan siê nie zmienia
		//dla SR=11 dominuj¹ce jest R
	}

	int Latch::getOUT(int o)
	{
		if (o == 0)
		{
			return IO.Q;
		}
		else if (o == 1)
		{
			return IO.notQ;
		}
		else
		{
			throw IO_OutOfRange();
		}
	}
	void Latch::setIN(int value, const string lineName, const int i)
	{
		if (lineName != "input") throw IO_BadLineRequest();
		//ustawienie odpowiedniego wejœcia
		if (i == 0)
		{
			IO.S = Functions::ParseLogic(value);
		}
		else if (i == 1)
		{
			IO.R = Functions::ParseLogic(value);
		}
		else
		{
			throw IO_OutOfRange();
		}
		//odœwie¿enie wartoœci
		this->RefreshLogic();
	}
	map<string, vector<int>> Latch::ReturnAccessibleInputs()
	{
		//parsowanie wyboru wejœcia
		int countOfAccesibleInputs = count_if(IO.input_status.begin(), IO.input_status.end(), [](State s) { return s == State::off;  });
		if (countOfAccesibleInputs == 0)
			throw LEexception("Wejscia sa juz zajete");

		map<string, vector<int>> retMap;
		vector<int> accessibleInputsVector;

		for (int i = 0; i < IO.input_status.size(); i++)
		{
			if (IO.input_status[i] == State::off)
			{
				accessibleInputsVector.push_back(i);
			}
		}

		retMap.insert(pair<string, vector<int>>("input", accessibleInputsVector));
		return retMap;
	}
	vector<int> Latch::ReturnAccessibleOutputs()
	{
		vector<int> retVec;
		retVec.push_back(0);
		retVec.push_back(1);
		return retVec;
	}
	void Latch::UpdateInputState(int i, string lineName, State s)
	{
		if (lineName != "input") throw IO_BadLineRequest();

		if (i < IO.input_status.size())
		{
			IO.input_status[i] = s;
		}
		else
		{
			throw IO_OutOfRange();
		}
	}

	map<string, vector<int>> Latch::ReturnIOState()
	{
		map<string, vector<int>> retMap;
		vector<int> inVec;
		inVec.push_back(IO.S);
		inVec.push_back(IO.R);
		vector<int> outVec;
		outVec.push_back(IO.Q);
		outVec.push_back(IO.notQ);
		retMap.insert(pair<string, vector<int>>("input", inVec));
		retMap.insert(pair<string, vector<int>>("output", outVec));
		return retMap;
	}

	Latch::~Latch()
	{
		std::cout << "Destruktor Latch\n";
	}

}