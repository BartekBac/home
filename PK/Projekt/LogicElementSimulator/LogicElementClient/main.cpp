#include "LogicElement.h"
#include "AppFunctions.h"
#include <map>
#include "vld.h"

using namespace std;

int main()
{
	map<int, LogicElement*> listLE;	//g³owny kontener elemntów logicznych
	int action = 0;					//flaga dzia³ania w pêtli g³ownej programu
	bool close = false;				//flaga zamkniêcia programu
	//pêtla g³ówna programu
	while (!close)
	{
		while (action != 1 && action != 2 && action != 3 && action != 4)
		{//wybór akcji
			cout << "Wybierz akcje:\n1 - Dodaj element\n2 - Dodaj poloczenie\n3 - Pokaz stany\n4 - Zakoncz program...\n";
			cin >> action;
		}
		switch (action)	
		{//obs³u¿enie akcji
			case 1: 
			{//DODAWANIE ELEMENTU
				AddNewElement(listLE);
				break;
			}
			case 2:
			{//DODAWANIE PO£¥CZENIA
				AddNewWire(listLE);
				break;
			}
			case 3:
			{//POKAZANIE STANÓW
				ShowStates(listLE);
				break;
			}
			case 4:
			{//ZAMKNIÊCIE PROGRAMU
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