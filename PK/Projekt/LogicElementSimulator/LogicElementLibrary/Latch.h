#ifndef Latch_h
#define Latch_h

#include "LogicElement.h"
#include "LEexception.h"
#include "Export.h"
using namespace std;

namespace LE_Library {
	struct LatchIO {
		int S, R, Q, notQ;
		vector<State> input_status;
	};

	//KLASA BAZOWA BRAMEK
	class Latch : public LogicElement {
	protected:
		LatchIO IO;

	public:
		EXPORT Latch();

		void setIN(int value, const std::string lineName = "input", const int i = 1);
		int getOUT(int o = 1);
		void RefreshLogic();
		void UpdateInputState(int i, string lineName, State s);
		vector<int> ReturnAccessibleOutputs();
		map<string, vector<int>> ReturnAccessibleInputs(); //wyrzuca wyj¹tek LEexception gdy nie ma ju¿ dostepnych wejœæ
		map<string, vector<int>> ReturnIOState();

		~Latch();
	};
}
#endif