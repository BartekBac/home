#ifndef LogicElement_h
#define LogicElement_h

#include <iostream>
#include <vector>
#include <map>
#include "Wire.h"
#include "Export.h"

namespace LE_Library {

	//TYPY WYLICZENIOWE
	enum State { off = 0, on = 1 };	//stan pinu wejœcia off-wolny, on-zajêty
	enum Element { eAND, eOR, eXOR, eNAND, eNOR, eMUX, eDMUX, eLatch, eConstant };	//typy puli elementów logicznych
	enum gateType { two_input, three_input, four_input };	//rozmiar bramki (w zale¿noœci od iloœci wejœæ)
	enum muxType { _1x2, _2x4, _3x8, _4x16 };				//rozmiar multi/demulti-pleksera (w zale¿noœci od iloœci wejœæ)
	
	/*
	STANDARYZOWANA TERMINOLOGIA linii wejœæ/wyjœæ dla map I/O
	input - zwyk³e wejœcia - gdy uk³ad ma tylko jedn¹ liniê wejœæ (bramki, przerzutnik)
	data_input - wejœcia danych (multiplekser)
	control_input - wejœcia steruj¹ce (multiplekser, przerzutniki (set,reset))
	output - wyjœcia
	NUMEROWANIE (je¿eli istnieje kilka wejœæ/wyjœæ na jednej linii)
	rosn¹co od 0:
	- od lewej do prawej
	- od góry do do³u
	ka¿da linia ma w³asne numerowanie (rozpoczynane od 0)
	jezli jest jedno wejœcie/wyjœcie ma numer 0
	*/
	
	//Klasa bazowa wszytskich elementów logicznych
	class LogicElement {
	protected:
		Element elemFlag;	//flaga elementu logicznego
		int indx;			//unikalny index elementu
		std::string name;	//nazwa elementu
		int defaultValue;	//domyœlnie ustawione wartoœci logiczne na wejœciach
	public:
		std::vector<Wire*> connectList; //vector wszystkich po³¹czeñ wyjœciowych bramki
		static int globIndex;			//globalny index gwarantuj¹cy unikalnoœæ elemntów
		EXPORT LogicElement();
		
		//Ustawia i-te wejscie odpowieniej linii na dan¹ wartoœæ
			//wyrzuca wyj¹tek IO_OutOfRange - gdy index pinu poza zakresem
			//wyrzuca wyj¹tek IO_BadLineRequest - gdy nie posiada danej linii pinów
		virtual EXPORT void setIN(int value, const string lineName = "input", const int i = 1) = 0;
		//Zwraca wartoœæ o-tego wyjœcia (zawsze jest tylko jedna linia wyjœæ)
			//wyrzuca wyj¹tek IO_OutOfRange - gdy index pinu poza zakresem
		virtual EXPORT int getOUT(const int o = 1) = 0;		
		//Odœwie¿a logiczny stan bramki
		virtual EXPORT void RefreshLogic() = 0;
		//Aktualizuje dostêpnoœæ wejœæ
		virtual EXPORT void UpdateInputState(int i, string lineName, State s) = 0;
		//Zwraca vector indexów dostêpnych wyjœæ (zawsze jedna linia)
		virtual EXPORT vector<int> ReturnAccessibleOutputs() = 0;
		//Zwraca mapê linii dostêpnych wejœæ (mo¿e byæ wiêcej ni¿ jedna linia np. MUX)
			//wyrzuca wyj¹tek LEException - gdy nie ma dostêpnych wejœæ
		virtual EXPORT std::map<std::string, std::vector<int>> ReturnAccessibleInputs() = 0;
		//Zwraca mapê stanów na wejœciach/wyjœciach dowolnego elementu logicznego
		virtual EXPORT std::map<std::string, std::vector<int>> ReturnIOState() = 0;
	
		EXPORT Element getElemFlag();	//zwraca flagê jaki to jest element
		EXPORT int getIndex();			//zwraca index elementu
		EXPORT std::string getName();	//zwraca nazwê elementu
		EXPORT int getDefaultValue();	//zwraca domyœln¹ wartoœæ logiczn¹ na wejœciu
	
		virtual EXPORT ~LogicElement();
	};
	
}
#endif