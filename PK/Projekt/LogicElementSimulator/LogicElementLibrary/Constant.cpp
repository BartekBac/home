#include "Constant.h"
#include "Functions.h"
#include <string>
namespace LE_Library {

	Constant::Constant(int IN)
	{
		defaultValue = 1;
		value = Functions::ParseLogic(IN);
		elemFlag = eConstant;
		name = "CONST_VALUE_";
		name += std::to_string(indx);
	}
	void Constant::setIN(int value, string lineName, int i)
	{//nie powinna zaistnie� taka sytuacja
		;
	}
	int Constant::getOUT(int o)
	{
		return value;
	}
	map<string, vector<int>> Constant::ReturnAccessibleInputs()
	{//nie powinna zaistnie� taka sytuacja
		return map<string, vector<int>>();
	}
	vector<int> Constant::ReturnAccessibleOutputs()
	{
		vector<int> retVec;
		retVec.push_back(0);
		return retVec;
	}
	void Constant::UpdateInputState(int i, string lineName, State s)
	{//nie powinna zaistnie� taka sytuacja
		;
	}
	void Constant::RefreshLogic()
	{//nie powinna zaistnie� taka sytuacja
		;
	}
	std::map<string, vector<int>> Constant::ReturnIOState()
	{
		map<string, vector<int>> retMap;
		vector<int> outVec;
		outVec.push_back(value);
		retMap.insert(pair<string, vector<int>>("output", outVec));
		return retMap;
	}
	Constant::~Constant()
	{
		cout << "Destruktor stalej\n";
	}
}