#ifndef AppFunctions_h
#define AppFunctions_h
#include "LogicElement.h"
#include "DMUX.h"
#include "MUX.h"
#include "Latch.h"
#include "Gates.h"
#include "AND.h"
#include "OR.h"
#include "XOR.h"
#include "NAND.h"
#include "NOR.h"
#include "Constant.h"
#include "LEexception.h"
#include "Functions.h"

using namespace LE_Library;

//Funkcje Konsolowe

//Zwraca Polskie t�umaczenie linii pin�w element�w logicznych
string TranslateIOName(const string name);
//Zwraca wybrany rozmiar bramki
gateType SelectGateType();
//Zwraca wybrany rozmiar multipleksera/demultipleksera
muxType SelectMuxType();
//Dodaje nowy element do kontenera
void AddNewElement(map<int, LogicElement*> &container);
//Tworzy po��czenie mi�dzy dwoma wybranymi elementami
void MakeWire(Wire *_wire, LogicElement* inLE, LogicElement* outLE);
//Dodaje po��czenie mi�dzy elementami kontenera
void AddNewWire(map<int, LogicElement*> &container);
//Pokazuje stan logiczny wej��/wyj�� danego elemntu
void ShowLogicElementState(map<string, vector<int>> _IOmap);
//Pokazuje stany wszytskich element�w kontenera
void ShowStates(map<int, LogicElement*> container);
//Zwraca true gdy zamyka program, flase gdy pozostawia w��czony
bool CloseApp(map<int, LogicElement*> &container);
#endif