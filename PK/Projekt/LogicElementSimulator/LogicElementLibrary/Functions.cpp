#include "Functions.h"

namespace LE_Library {

	int Functions::ParseLogic(int x) 
	{//dla warto�ci r�nych od 0 zwraca 1
		if (x == 0)
			return 0;
		else
			return 1;
	}

	int Functions::NegateLogic(int x)
	{//negacja logiczna
		if (x == 0)
			return 1;
		else
			return 0;
	}

	void Functions::UpdateConnectedSeries(LogicElement *_elem)
	{//rekurencyjne aktualizowanie ca�ej po��czonej serii
		for (int i = 0; i < _elem->connectList.size(); i++)
		{
			_elem->connectList[i]->RefreshLogic();
			UpdateConnectedSeries(_elem->connectList[i]->getSuccessor());
		}
	}

	void Functions::CheckConnectedSeries_start(LogicElement *_elem)
	{//gwarantuje utworzenie i usuni�cie kontenera sprawdzaj�cego po��czenia
		if (_elem->connectList.size() > 0)
		{
			vector<int> _vecLE;
			CheckConnectedSeries(_elem, _vecLE);
			_vecLE.clear();
		}
	}
	void Functions::CheckConnectedSeries(LogicElement *elem, vector<int> vecLE)
	{
		for (int i = 0; i < vecLE.size(); i++)
		{
			if (vecLE[i] == elem->getIndex()) //sprawdzamy czy p�tla
			{ // je�li wykryto p�tle wyrzucamy wyj�tek
				vecLE.clear(); //usuni�cie vectora
				throw RaceCondition(); //zawiadomienie o wyst�pieniu wy�cigu w uk�adzie
			}
		}

		for (int i = 0; i < elem->connectList.size(); i++)
		{//dla wszytsko po�aczonych element�w do aktualnego
			vecLE.push_back(elem->getIndex()); //dajemy do vectora index aktualnego elementu, jak ma dalsze przewody
			CheckConnectedSeries(elem->connectList[i]->getSuccessor(), vecLE); //wywo�anie rekurencyjne dla nast�pnych elemnt�w po��czonej serii
			vecLE.pop_back(); //po rekurencyjnym powrocie zwalniamy wrzucony indeks (opuszczamy t� ga��� przewod�w)
		}
	}

	bool Functions::ElementExists(int indx, map<int, LogicElement*> container)
	{
		auto selectedItem = container.find(indx);
		if (selectedItem == container.end()) return false;
		else return true;
	}

	int Functions::BinAddrToDec(vector<int> control_input)
	{
		int decimalValue = 0;	//warto�� dziesi�tna
		for (int i = 0; i < control_input.size(); i++)
		{
			if (control_input[i] == 1)
			{
				decimalValue += pow(2, i);
			}
		}
		return decimalValue;
	}

}