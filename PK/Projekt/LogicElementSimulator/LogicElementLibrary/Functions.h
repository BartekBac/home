#ifndef Functions_h
#define Functions_h
#include "LogicElement.h"
#include "LEexception.h"
#include "Export.h"

namespace LE_Library {
	class Functions {
	//Funkcje pracuj¹ce na uk³adzie logicznym
	public:
		//Gwarantuje zwrócenie wartoœci tylko 0 lub 1
		static EXPORT int ParseLogic(int x);
		//Zwraca zanegowan¹ wartoœæ logiczn¹
		static EXPORT int NegateLogic(int x);
		//Sprawdza stan serii po³¹czeñ pod wzglêdem wyst¹pienia pêtli
		static EXPORT void CheckConnectedSeries(LogicElement *elem, vector<int> vecLE);
		//Rozpoczyna rekurencyjne sprawdzenie stanu serii po³¹czeñ
		static EXPORT void CheckConnectedSeries_start(LogicElement *_elem);
		//Aktualizuje stan serii po³¹czeñ
		static EXPORT void UpdateConnectedSeries(LogicElement *_elem);
		//Sprawdza czy elemnt o danych indeksie istnieje w kontenerze
		static EXPORT bool ElementExists(int indx, map<int, LogicElement*> container);
		//Zwraca dziesiêtn¹ wartoœæ binarnego adresu na danej linii wejœæ steruj¹cych
		static EXPORT int BinAddrToDec(vector<int> control_input);
	};
}
#endif