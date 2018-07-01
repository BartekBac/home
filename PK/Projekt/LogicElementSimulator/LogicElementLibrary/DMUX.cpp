#include "DMUX.h"
#include "Functions.h"
namespace LE_Library {

	dmuxIO::dmuxIO(muxType _type)
	{//kontruktor uzupe³niaj¹cy wejœcia/wyjœcia na podstawie danego typu
		if (_type == muxType::_1x2)
		{
			output_count = 2;
			control_input_count = 1;
		}
		else if (_type == muxType::_2x4)
		{
			output_count = 4;
			control_input_count = 2;
		}
		else if (_type == muxType::_3x8)
		{
			output_count = 8;
			control_input_count = 3;
		}
		else if (_type == muxType::_4x16)
		{
			output_count = 16;
			control_input_count = 4;
		}
		else
		{
			throw WrongConstructorParameter();
		}

		for (int i = 0; i < output_count; i++)
		{
			//wyjœcia zanegowane
			output.push_back(1);
		}

		input_status = State::off;
		for (int i = 0; i < control_input_count; i++)
		{
			control_input_status.push_back(State::off);
		}

	}
	dmuxIO::~dmuxIO()
	{
		control_input.clear();
		control_input_status.clear();
		output.clear();
	}


	DMUX::DMUX(muxType _type) : IO(dmuxIO(_type)) {

		defaultValue = 0;
		elemFlag = eDMUX;
		name = "DMUX_";
		name += std::to_string(indx);

		IO.input = defaultValue;

		for (int i = 0; i < IO.control_input_count; i++)
		{
			IO.control_input.push_back(defaultValue);
		}
		this->RefreshLogic();
	}

	void DMUX::RefreshLogic()
	{
		//wyjœcia zanegowane, czyli na wszytskich 1
		//na wybranym przez wejœcia adresowe negacja wejœcia x
		for (int i = 0; i < IO.output_count; i++)
		{
			IO.output[i] = 1;
		}
		int addr = Functions::BinAddrToDec(IO.control_input);
		IO.output[addr] = Functions::NegateLogic(IO.input);
	}
	int DMUX::getOUT(int o)
	{
		//wybór odpowiedniego wyjœcia indeksy(0 - n-1)
		if (IO.output_count > o)
		{
			return IO.output[o];
		}
		else
		{
			throw IO_OutOfRange();
		}
	}
	void DMUX::setIN(int value, const string lineName, const int i)
	{
		//wybór linii wejœæ
		if (lineName == "input")
		{
			IO.input = Functions::ParseLogic(value);
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
	map<string, vector<int>> DMUX::ReturnAccessibleInputs()
	{
		//parsowanie wyboru wejœcia
		int countOfAccesibleControlInputs = count_if(IO.control_input_status.begin(), IO.control_input_status.end(), [](State s) { return s == State::off; });

		if (IO.input_status == State::on && countOfAccesibleControlInputs == 0)
			throw LEexception("Wejscia sa juz zajete");

		map<string, vector<int>> retMap;			//mapa wszytskich dostêpnych wejœæ
		vector<int> accessibleDataInputsVector;		//vector dostêpnych wejœæ danych
		vector<int> accessibleControlInputsVector;	//vecotr dostêpnych wejœæ steruj¹cych

		if (IO.input_status == State::off)
		{
			accessibleDataInputsVector.push_back(0);
			//wstawiamy tylko jeœli wejœcie x jest dostêpne
			retMap.insert(pair<string, vector<int>>("input", accessibleDataInputsVector));
		}
		for (int i = 0; i < IO.control_input_count; i++)
		{
			if (IO.control_input_status[i] == State::off)
			{
				accessibleControlInputsVector.push_back(i);
			}
		}

		//gdyby tylko wejscie x by³o dostêpne
		if (countOfAccesibleControlInputs > 0)
		{
			retMap.insert(pair<string, vector<int>>("control_input", accessibleControlInputsVector));
		}
		return retMap;
	}
	vector<int> DMUX::ReturnAccessibleOutputs()
	{
		vector<int> retVec;
		for (int i = 0; i < IO.output_count; i++)
		{
			retVec.push_back(i);
		}
		return retVec;
	}
	void DMUX::UpdateInputState(int i, string lineName, State s)
	{
		if (lineName == "input") //update statusu jednego wejœcia danych
		{
			IO.input_status = s;
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

	map<string, vector<int>> DMUX::ReturnIOState()
	{
		map<string, vector<int>> retMap;
		vector<int> inVec;
		inVec.push_back(IO.input);
		retMap.insert(pair<string, vector<int>>("input", inVec));
		retMap.insert(pair<string, vector<int>>("control_input", IO.control_input));
		retMap.insert(pair<string, vector<int>>("output", IO.output));
		return retMap;
	}

	DMUX::~DMUX()
	{
		std::cout << "Destruktor DMUX\n";
	}
}