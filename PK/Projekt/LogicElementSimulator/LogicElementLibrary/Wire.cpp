#include "Wire.h"
#include "Gates.h"
#include "Constant.h"
#include "LEexception.h"
namespace LE_Library {

	Wire::Wire()
	{
		value = 0;
		beginPin = 0;
		endLineName = "";
		endPin = 0;
		beginElement = nullptr;
		endElement = nullptr;
	}
	void Wire::RefreshLogic()
	{
		value = beginElement->getOUT(beginPin);
		endElement->setIN(value, endLineName, endPin);
	}
	void Wire::selectBegin(LogicElement *_IN, int i)
	{
		beginElement = _IN;
		beginPin = i;
	}
	void Wire::selectEnd(LogicElement *_OUT, string lineName, int o)
	{
		endElement = _OUT;
		endLineName = lineName;
		endPin = o;
	}
	bool Wire::checkPinAccessibility(LogicElement *element, string lineName, int indx)
	{
		if (element == nullptr) // gdy element nie istnieje
			return false;
		
		vector<int> accessiblePins;

		if (lineName == "output")
		{//gdy sprawdzamy liniê wyjœæ
			accessiblePins = element->ReturnAccessibleOutputs();
		}
		else
		{//gdy sprawdzamy jedn¹ z linii wejœæ
			auto accessibleInputLines = element->ReturnAccessibleInputs();
			auto selectedLine = accessibleInputLines.find(lineName);
			if (selectedLine != accessibleInputLines.end())
			{//gdy znajdziemy
				accessiblePins = selectedLine->second;
			}
			else
			{//nie am takiej linii wejœæ
				return false;
			}
		}
		auto selectedPin = find(accessiblePins.begin(), accessiblePins.end(), indx);
		if (selectedPin != accessiblePins.end())
		{//gdy znajdziemy wœród dostêpnych pinów o wybranym indeksie
			return true;
		}
		else
		{//gdy nie znjadziemy danego indeksu pinu
			return false;
		}
	}
	void Wire::ResetEnd()
	{
		if (endElement != nullptr)
		{//odœwierzenie wartoœci na elemencie koñcowym
			endElement->setIN(endElement->getDefaultValue(), endLineName, endPin);
			endElement->UpdateInputState(endPin, endLineName, State::off);
			endElement = nullptr;
		}
	}
	void Wire::Finalize()
	{
		beginElement->connectList.push_back(this);
		endElement->UpdateInputState(endPin, endLineName, State::on);
	}
	LogicElement* Wire::getSuccessor()
	{
		return endElement; //jak nullptr, to zwróci nullptr
	}
	Wire::~Wire()
	{
		std::cout << "Destruktor Wire\n";
		endElement = nullptr;
		beginElement = nullptr;
	}

}