#ifndef Wire_h
#define Wire_h
#include <string>
#include "Export.h"
using namespace std;
namespace LE_Library {
	class LogicElement;

	//Klasa odpowiedzialna za prawidlowe ��czenie ze sob� element�w
	class EXPORT Wire {
		int value;				//warto�� logiczna na przewodzie
		int beginPin;			//zapami�tuje do kt�rego pinu wyj�cia elemntu pocz�tkowego pod�aczyli�my przew�d (numerowane 0 - n-1)
		int endPin;				//zapami�tuje do kt�rego pinu wej�cia elemntu ko�owego pod�aczyli�my przew�d (numerowane 0 - n-1)
		string endLineName;		//zapami�tuje nazw� wybranej linii wej�� elemntu ko�cowego
		LogicElement *beginElement;	//elemnet pocz�tkowy przewodu (nadaj�cy sygna�)
		LogicElement *endElement;	//element ko�cowy przeowdu (odbieraj�cy sygna�)
	public:
		Wire();
		bool checkPinAccessibility(LogicElement *element, string lineName, int indx); //sprawdza czy wybrane wej�cie/wyj�cie elementu jest dost�pne
		void selectBegin(LogicElement *_IN, int i); //wybiera wyj�cie elementu (kt�re b�dzie pocz�tkiem przewodu)
		void selectEnd(LogicElement *_OUT, string lineName, int o); //wybiera wej�cie elementu (kt�re b�dzie ko�cem przewodu)		
		void ResetEnd(); //resetuje stan elemntu ko�cowego do domy�lnego (przed pod��czeniem)
		void Finalize(); //finalizuje dodanie po��czenia przypisuj�c je do elementu pocz�tkowego, oraz aktualizuj�� dost�pno�� wejscia elemntu ko�cowego

		void RefreshLogic(); //od�wierza stan na przewodzie
		LogicElement *getSuccessor(); //gdy istnieje zwraca wska�nik elementu z kt�rym jest po��czony
		~Wire();
	};
}

#endif