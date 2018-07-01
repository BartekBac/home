#ifndef Gates_h
#define Gates_h

#include "LogicElement.h"
#include "LEexception.h"
#include <algorithm>
#include "Export.h"
using namespace std; 

namespace LE_Library {	

	struct GateIO {
		vector<int> input;			//wejœcia
		vector<State> input_status;	//stany wejœæ
		int output;					//wyjœcie
		int input_count;			//liczba wejœæ
		GateIO(gateType _type);
		~GateIO();
	};

	//KLASA BAZOWA BRAMEK
	class Gate : public LogicElement {
	protected:
		GateIO IO;

	public:
		EXPORT Gate(gateType _type);

		void setIN(int value, const string lineName = "input", const int i = 1);
		int getOUT(int o = 1);
		void UpdateInputState(int i, string lineName, State s);
		vector<int> ReturnAccessibleOutputs();
		map<string, vector<int>> ReturnAccessibleInputs();
		map<string, vector<int>> ReturnIOState();

		virtual ~Gate();
	};
}

#endif