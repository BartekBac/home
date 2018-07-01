#ifndef Wire_h
#define Wire_h
#include <string>
#include "Export.h"
using namespace std;
namespace LE_Library {
	class LogicElement;

	//Klasa odpowiedzialna za prawidlowe ³¹czenie ze sob¹ elementów
	class EXPORT Wire {
		int value;				//wartoœæ logiczna na przewodzie
		int beginPin;			//zapamiêtuje do którego pinu wyjœcia elemntu pocz¹tkowego pod³aczyliœmy przewód (numerowane 0 - n-1)
		int endPin;				//zapamiêtuje do którego pinu wejœcia elemntu koñowego pod³aczyliœmy przewód (numerowane 0 - n-1)
		string endLineName;		//zapamiêtuje nazwê wybranej linii wejœæ elemntu koñcowego
		LogicElement *beginElement;	//elemnet pocz¹tkowy przewodu (nadaj¹cy sygna³)
		LogicElement *endElement;	//element koñcowy przeowdu (odbieraj¹cy sygna³)
	public:
		Wire();
		bool checkPinAccessibility(LogicElement *element, string lineName, int indx); //sprawdza czy wybrane wejœcie/wyjœcie elementu jest dostêpne
		void selectBegin(LogicElement *_IN, int i); //wybiera wyjœcie elementu (które bêdzie pocz¹tkiem przewodu)
		void selectEnd(LogicElement *_OUT, string lineName, int o); //wybiera wejœcie elementu (które bêdzie koñcem przewodu)		
		void ResetEnd(); //resetuje stan elemntu koñcowego do domyœlnego (przed pod³¹czeniem)
		void Finalize(); //finalizuje dodanie po³¹czenia przypisuj¹c je do elementu pocz¹tkowego, oraz aktualizuj¹æ dostêpnoœæ wejscia elemntu koñcowego

		void RefreshLogic(); //odœwierza stan na przewodzie
		LogicElement *getSuccessor(); //gdy istnieje zwraca wskaŸnik elementu z którym jest po³¹czony
		~Wire();
	};
}

#endif