#ifndef Constant_h
#define Constant_h

#include "LogicElement.h"
#include "Export.h"
using namespace std;
 
namespace LE_Library {
	class Constant : public LogicElement {
		int value;	//wartoœæ sta³ej
	public:
		EXPORT Constant(int IN = 0);

		void setIN(int value, const string lineName = "input", const int i = 1);
		int getOUT(int o = 1);
		map<string, vector<int>> ReturnAccessibleInputs();
		vector<int> ReturnAccessibleOutputs();
		void UpdateInputState(int i, string lineName, State s);
		void RefreshLogic();
		map<string, vector<int>> ReturnIOState();

		~Constant();
	};
}


#endif // !Constant_h
