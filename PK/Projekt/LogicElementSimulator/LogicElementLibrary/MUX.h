#ifndef MUX_h
#define MUX_h

#include "LogicElement.h"
#include "LEexception.h"
#include <algorithm>
#include "Export.h"
using namespace std;

namespace LE_Library {
	struct muxIO {
		vector<int> data_input;				//wej�cia danych
		vector<int> control_input;			//wej�cia steruj�ce
		vector<State> data_input_status;	//stany wej�� danych
		vector<State> control_input_status;	//stany wej�� steruj�cych
		int output;							//wyj�cie
		int data_input_count;				//liczba wej�� danych
		int control_input_count;			//liczba wej�� steruj�cych
		muxIO(muxType _type);
		~muxIO();
	};

	class MUX : public LogicElement {
	protected:
		muxIO IO;

	public:
		EXPORT MUX(muxType _type);

		void setIN(int value, const string lineName = "input", const int i = 1);
		int getOUT(int o = 1);
		void RefreshLogic();
		void UpdateInputState(int i, string lineName, State s);
		vector<int> ReturnAccessibleOutputs();
		map<string, vector<int>> ReturnAccessibleInputs();
		map<string, vector<int>> ReturnIOState();

		~MUX();
	};
}

#endif