#pragma once
#include <string>
#include <iostream>
//G�OWNA KLASA WYJ�TK�W
class LEexception {
	std::string message_text;
public:
	LEexception(const std::string &msg = "Wykryto nieznany wyj�tek") : message_text(msg) {}
	std::string GetMessage() { return message_text; }
	~LEexception() {}
};

//KLASY POCHODNE WYJ�TK�W
class CancelEx : public LEexception { //klasa anulowania jakiego� wyboru
public:
	CancelEx() : LEexception("Anulowano wybor") {}
};

class RaceCondition : public LEexception { //klasa wyj�tku wykrycia p�tli w uk�adzie
public:
	RaceCondition() : LEexception("Wykryto petle w ukladzie") {}
};

class WrongConstructorParameter : public LEexception {
public:
	WrongConstructorParameter() : LEexception("Podany argument w knstruktorze jest niepoprawny") {}
};

class IO_OutOfRange : public LEexception {
public:
	IO_OutOfRange() : LEexception("Przekroczono zakres wejsc/wyjsc elemntu logicznego") {}
};

class IO_BadLineRequest : public LEexception {
public:
	IO_BadLineRequest() : LEexception("Zla linia wejsc/wyjsc elemntu logicznego") {}
};