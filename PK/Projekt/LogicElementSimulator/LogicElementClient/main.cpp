#include "LogicElement.h"
#include "AppFunctions.h"
#include <map>
#include "vld.h"

using namespace std;

int main()
{
	map<int, LogicElement*> listLE;	//g�owny kontener elemnt�w logicznych
	int action = 0;					//flaga dzia�ania w p�tli g�ownej programu
	bool close = false;				//flaga zamkni�cia programu
	//p�tla g��wna programu
	while (!close)
	{
		while (action != 1 && action != 2 && action != 3 && action != 4)
		{//wyb�r akcji
			cout << "Wybierz akcje:\n1 - Dodaj element\n2 - Dodaj poloczenie\n3 - Pokaz stany\n4 - Zakoncz program...\n";
			cin >> action;
		}
		switch (action)	
		{//obs�u�enie akcji
			case 1: 
			{//DODAWANIE ELEMENTU
				AddNewElement(listLE);
				break;
			}
			case 2:
			{//DODAWANIE PO��CZENIA
				AddNewWire(listLE);
				break;
			}
			case 3:
			{//POKAZANIE STAN�W
				ShowStates(listLE);
				break;
			}
			case 4:
			{//ZAMKNI�CIE PROGRAMU
				if (CloseApp(listLE))
				{
					close = true;
				}
				else
				{
					break;
				}
			}
		}
		action = 0;
	}
	return 0;
}