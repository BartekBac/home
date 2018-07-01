#ifndef LogicElement_h
#define LogicElement_h

#include <iostream>
#include <vector>
#include <map>
#include "Wire.h"
#include "Export.h"

namespace LE_Library {

	//TYPY WYLICZENIOWE
	enum State { off = 0, on = 1 };	//stan pinu wej�cia off-wolny, on-zaj�ty
	enum Element { eAND, eOR, eXOR, eNAND, eNOR, eMUX, eDMUX, eLatch, eConstant };	//typy puli element�w logicznych
	enum gateType { two_input, three_input, four_input };	//rozmiar bramki (w zale�no�ci od ilo�ci wej��)
	enum muxType { _1x2, _2x4, _3x8, _4x16 };				//rozmiar multi/demulti-pleksera (w zale�no�ci od ilo�ci wej��)
	
	/*
	STANDARYZOWANA TERMINOLOGIA linii wej��/wyj�� dla map I/O
	input - zwyk�e wej�cia - gdy uk�ad ma tylko jedn� lini� wej�� (bramki, przerzutnik)
	data_input - wej�cia danych (multiplekser)
	control_input - wej�cia steruj�ce (multiplekser, przerzutniki (set,reset))
	output - wyj�cia
	NUMEROWANIE (je�eli istnieje kilka wej��/wyj�� na jednej linii)
	rosn�co od 0:
	- od lewej do prawej
	- od g�ry do do�u
	ka�da linia ma w�asne numerowanie (rozpoczynane od 0)
	jezli jest jedno wej�cie/wyj�cie ma numer 0
	*/
	
	//Klasa bazowa wszytskich element�w logicznych
	class LogicElement {
	protected:
		Element elemFlag;	//flaga elementu logicznego
		int indx;			//unikalny index elementu
		std::string name;	//nazwa elementu
		int defaultValue;	//domy�lnie ustawione warto�ci logiczne na wej�ciach
	public:
		std::vector<Wire*> connectList; //vector wszystkich po��cze� wyj�ciowych bramki
		static int globIndex;			//globalny index gwarantuj�cy unikalno�� elemnt�w
		EXPORT LogicElement();
		
		//Ustawia i-te wejscie odpowieniej linii na dan� warto��
			//wyrzuca wyj�tek IO_OutOfRange - gdy index pinu poza zakresem
			//wyrzuca wyj�tek IO_BadLineRequest - gdy nie posiada danej linii pin�w
		virtual EXPORT void setIN(int value, const string lineName = "input", const int i = 1) = 0;
		//Zwraca warto�� o-tego wyj�cia (zawsze jest tylko jedna linia wyj��)
			//wyrzuca wyj�tek IO_OutOfRange - gdy index pinu poza zakresem
		virtual EXPORT int getOUT(const int o = 1) = 0;		
		//Od�wie�a logiczny stan bramki
		virtual EXPORT void RefreshLogic() = 0;
		//Aktualizuje dost�pno�� wej��
		virtual EXPORT void UpdateInputState(int i, string lineName, State s) = 0;
		//Zwraca vector index�w dost�pnych wyj�� (zawsze jedna linia)
		virtual EXPORT vector<int> ReturnAccessibleOutputs() = 0;
		//Zwraca map� linii dost�pnych wej�� (mo�e by� wi�cej ni� jedna linia np. MUX)
			//wyrzuca wyj�tek LEException - gdy nie ma dost�pnych wej��
		virtual EXPORT std::map<std::string, std::vector<int>> ReturnAccessibleInputs() = 0;
		//Zwraca map� stan�w na wej�ciach/wyj�ciach dowolnego elementu logicznego
		virtual EXPORT std::map<std::string, std::vector<int>> ReturnIOState() = 0;
	
		EXPORT Element getElemFlag();	//zwraca flag� jaki to jest element
		EXPORT int getIndex();			//zwraca index elementu
		EXPORT std::string getName();	//zwraca nazw� elementu
		EXPORT int getDefaultValue();	//zwraca domy�ln� warto�� logiczn� na wej�ciu
	
		virtual EXPORT ~LogicElement();
	};
	
}
#endif