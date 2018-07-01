#ifndef Functions_h
#define Functions_h
#include "LogicElement.h"
#include "LEexception.h"
#include "Export.h"

namespace LE_Library {
	class Functions {
	//Funkcje pracuj�ce na uk�adzie logicznym
	public:
		//Gwarantuje zwr�cenie warto�ci tylko 0 lub 1
		static EXPORT int ParseLogic(int x);
		//Zwraca zanegowan� warto�� logiczn�
		static EXPORT int NegateLogic(int x);
		//Sprawdza stan serii po��cze� pod wzgl�dem wyst�pienia p�tli
		static EXPORT void CheckConnectedSeries(LogicElement *elem, vector<int> vecLE);
		//Rozpoczyna rekurencyjne sprawdzenie stanu serii po��cze�
		static EXPORT void CheckConnectedSeries_start(LogicElement *_elem);
		//Aktualizuje stan serii po��cze�
		static EXPORT void UpdateConnectedSeries(LogicElement *_elem);
		//Sprawdza czy elemnt o danych indeksie istnieje w kontenerze
		static EXPORT bool ElementExists(int indx, map<int, LogicElement*> container);
		//Zwraca dziesi�tn� warto�� binarnego adresu na danej linii wej�� steruj�cych
		static EXPORT int BinAddrToDec(vector<int> control_input);
	};
}
#endif