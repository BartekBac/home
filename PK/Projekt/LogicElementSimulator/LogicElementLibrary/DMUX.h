#ifndef DMUX_h
#define DMUX_h

#include "LogicElement.h"
#include "LEexception.h"
#include <algorithm>
#include "Export.h"
using namespace std;

namespace LE_Library {
	
	struct dmuxIO 
	{//struktura wej��/wyj�� demultipleksera
		int input;					//wejscie informacyjne
		State input_status;			//stan wej�cia informacyjnego
		vector<int> control_input;	//wej�cia steruj�ce
		vector<State> control_input_status;//stany wej�� steruj�cych
		vector<int> output;			//wyj�cia
		int control_input_count;	//liczba wej�� steruj�cych
		int output_count;			//liczba wyj��
		dmuxIO(muxType _type);
		~dmuxIO();
	};

	class DMUX : public LogicElement {
	protected:
		dmuxIO IO;

	public:
		EXPORT DMUX(muxType _type);

		void setIN(int value, const std::string lineName = "input", const int i = 1);
		int getOUT(int o = 1);
		void RefreshLogic();
		void UpdateInputState(int i, string lineName, State s);
		vector<int> ReturnAccessibleOutputs();
		map<string, vector<int>> ReturnAccessibleInputs();
		map<string, vector<int>> ReturnIOState();

		~DMUX();
	};
}
#endif