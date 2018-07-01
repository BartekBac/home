#include "MUX.h"
#include "Functions.h"
namespace LE_Library {

	muxIO::muxIO(muxType _type)
	{//kontruktor uzupe³niaj¹cy wejœcia/wyjœcia na podstawie danego typu
		if (_type == muxType::_1x2)
		{
			data_input_count = 2;
			control_input_count = 1;
		}
		else if (_type == muxType::_2x4)
		{
			data_input_count = 4;
			control_input_count = 2;
		}
		else if (_type == muxType::_3x8)
		{
			data_input_count = 8;
			control_input_count = 3;
		}
		else if (_type == muxType::_4x16)
		{
			data_input_count = 16;
			control_input_count = 4;
		}
		else
		{
			throw WrongConstructorParameter();
		}

		for (int i = 0; i < data_input_count; i++)
		{
			data_input_status.push_back(State::off);
		}

		for (int i = 0; i < control_input_count; i++)
		{
			control_input_status.push_back(State::off);
		}
	}
	muxIO::~muxIO()
	{
		data_input.clear();
		control_input.clear();
		data_input_status.clear();
		control_input_status.clear();
	}


	MUX::MUX(muxType _type) : IO(muxIO(_type)) {

		defaultValue = 0;
		elemFlag = eMUX;
		name = "MUX_";
		name += std::to_string(indx);

		for (int i = 0; i < IO.data_input_count; i++)
		{
			IO.data_input.push_back(defaultValue);
		}

		for (int i = 0; i < IO.control_input_count; i++)
		{
			IO.control_input.push_back(defaultValue);
		}
	}

	void MUX::RefreshLogic()
	{//przekierowanie wejœcia danych z adresu wejœæ steruj¹cych na wyjœcie
		int addr = Functions::BinAddrToDec(IO.control_input);
		IO.output = IO.data_input[addr];
	}

	int MUX::getOUT(int o)
	{
		return IO.output;
	}
	void MUX::setIN(int value, const string lineName, const int i)
	{
		//wybór linii wejœæ
		if (lineName == "data_input")
		{
			//wybór odpowiedniego wejscia w linii (numerowane 1-n)
			if (IO.data_input_count > i)
			{
				IO.data_input[i] = Functions::ParseLogic(value);
			}
			else
			{
				throw IO_OutOfRange();
			}
		}
		else if (lineName == "control_input")
		{
			if (IO.control_input_count > i)
			{
				IO.control_input[i] = Functions::ParseLogic(value);
			}
			else
			{
				throw IO_OutOfRange();
			}
		}
		else //gdy nie ma podanej linii
		{
			throw IO_BadLineRequest();
		}

		//odœwierzenie wyjœcia
		this->RefreshLogic();
	}
	map<string, vector<int>> MUX::ReturnAccessibleInputs()
	{
		//parsowanie wyboru wejœcia
		int countOfAccesibleDataInputs = count_if(IO.data_input_status.begin(), IO.data_input_status.end(), [](State s) { return s == State::off;  });
		int countOfAccesibleControlInputs = count_if(IO.control_input_status.begin(), IO.control_input_status.end(), [](State s) { return s == State::off;  });

		if (countOfAccesibleDataInputs == 0 && countOfAccesibleControlInputs == 0)
			throw LEexception("Wejscia sa juz zajete");

		map<string, vector<int>> retMap;			//mapa wszytskich linii dostepnych wejœæ
		vector<int> accessibleDataInputsVector;		//vector pinów dostêpnych wejœæ danych
		vector<int> accessibleControlInputsVector;	//vector pinów dostepnych wejœc steruj¹cych

		for (int i = 0; i < IO.data_input_count; i++)
		{
			if (IO.data_input_status[i] == State::off)
			{
				accessibleDataInputsVector.push_back(i);
			}
		}
		for (int i = 0; i < IO.control_input_count; i++)
		{
			if (IO.control_input_status[i] == State::off)
			{
				accessibleControlInputsVector.push_back(i);
			}
		}

		//wstawiamy do mapy, tylko jak s¹ jakieœ dostepne wejœcia w danej linii
		if (countOfAccesibleDataInputs > 0)
		{
			retMap.insert(pair<string, vector<int>>("data_input", accessibleDataInputsVector));
		}
		if (countOfAccesibleControlInputs > 0)
		{
			retMap.insert(pair<string, vector<int>>("control_input", accessibleControlInputsVector));
		}
		return retMap;
	}
	vector<int> MUX::ReturnAccessibleOutputs()
	{
		vector<int> retVec;
		retVec.push_back(0);
		return retVec;
	}
	void MUX::UpdateInputState(int i, string lineName, State s)
	{
		if (lineName == "data_input") //update statusu wejsc linii danych
		{
			//(numerowane 0 - n-1)
			if (IO.data_input_count > i)
			{
				IO.data_input_status[i] = s;
			}
			else
			{
				throw IO_OutOfRange();
			}
		}
		else if (lineName == "control_input") //update statusu wejsc linii adresowej
		{
			if (IO.control_input_count > i)
			{
				IO.control_input_status[i] = s;
			}
			else
			{
				throw IO_OutOfRange();
			}
		}
		else //gdy nie ma podanej linii
		{
			throw IO_BadLineRequest();
		}
	}

	map<string, vector<int>> MUX::ReturnIOState()
	{
		map<string, vector<int>> retMap;
		vector<int> outVec;
		outVec.push_back(IO.output);
		retMap.insert(pair<string, vector<int>>("data_input", IO.data_input));
		retMap.insert(pair<string, vector<int>>("control_input", IO.control_input));
		retMap.insert(pair<string, vector<int>>("output", outVec));
		return retMap;
	}

	MUX::~MUX()
	{
		std::cout << "Destruktor MUX\n";
	}

}
