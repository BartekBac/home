#include "AppFunctions.h"

string TranslateIOName(const string name)
{
	if (name == "input") return "wejscia";
	else if (name == "data_input") return "wejscia danych";
	else if (name == "control_input") return "wejscia sterujace";
	else if (name == "output") return "wyjscia";
	else return name;
}
gateType SelectGateType()
{
	int gType = 0;
	while (gType != 1 && gType != 2 && gType != 3)
	{//parsowanie wyboru typu bramki
		cout << "Wybierz typ bramki:\n1 - dwu-wejsciowa\n2 - trzy-wejsciowa\n3 - cztero-wejsciowa\n";
		cin >> gType;
	}
	//zwraca zrzutowany wynik
	return gateType(gType-1);
}
muxType SelectMuxType()
{
	int mType = 0;
	while (mType != 1 && mType != 2 && mType != 3 && mType != 4)
	{//parsowanie wyboru typu multipleksera/demultipleksera
		cout << "Wybierz typ komutatora:\n1 - 1 x 2\n2 - 2 x 4\n3 - 3 x 8\n4 - 4 x 16\n";
		cin >> mType;
	}
	//zwraca zrzutowany wynik
	return muxType(mType-1);
}
void AddNewElement(map<int, LogicElement*> &container)
{
	int enumElem = 0;	//flaga wyboru z puli dost�pnych elemnt�w
	while (enumElem != 1 && enumElem != 2 && enumElem != 3 && enumElem != 4 && enumElem != 5 && enumElem != 6 && enumElem != 7 && enumElem != 8 && enumElem != 9)
	{//parsowanie wyboru elemntu
		cout << "Wybierz element:\n1 - CONST_VALUE\n2 - AND\n3 - OR\n4 - XOR\n5 - NAND\n6 - NOR\n7 - Latch\n8 - MUX\n9 - DMUX\n";
		cin >> enumElem;
	}
	LogicElement *nElem = nullptr;	//wska�nik nowotworzonego elemntu
	switch (enumElem)
	{//dodanie wybranego elementu
	case 1:
	{//STA�A
		int val = 0;
		std::cout << "Podaj wartosc stalej: ";
		std::cin >> val;
		nElem = new Constant(val);
		break;
	}
	case 2:
	{//AND
		gateType gType = SelectGateType();
		nElem = new AND(gType);
		break;
	}
	case 3:
	{//OR
		gateType gType = SelectGateType();
		nElem = new OR(gType);
		break;
	}
	case 4:
	{//XOR
		gateType gType = SelectGateType();
		nElem = new XOR(gType);
		break;
	}
	case 5:
	{//NAND
		gateType gType = SelectGateType();
		nElem = new NAND(gType);
		break;
	}
	case 6:
	{//NOR
		gateType gType = SelectGateType();
		nElem = new NOR(gType);
		break;
	}
	case 7:
	{//Latch
		nElem = new Latch();
		break;
	}
	case 8:
	{//Multiplexer
		muxType mType = SelectMuxType();
		nElem = new MUX(mType);
		break;
	}
	case 9:
	{//Demultiplexer
		muxType dType = SelectMuxType();
		nElem = new DMUX(dType);
		break;
	}
	}
	container.insert(pair<int, LogicElement*>(nElem->getIndex(), nElem));
	cout << "Dodano element: " << nElem->getName() << endl;
}
void MakeWire(Wire *_wire, LogicElement* inLE, LogicElement* outLE)
{
	//KONTENERY
	//pobranie wyj�� elemntu pocz�tkowego
	vector<int> accessibleOutputs = inLE->ReturnAccessibleOutputs(); 
	//pobranie wszytskich linii wej�� elemntu ko�cowego
	map<string, vector<int>> accessibleInputsMap = outLE->ReturnAccessibleInputs(); //wyrzuca wyj�tek LEexception gdy nie ma dost�pnych wej��
	//iterator wybranej linii wej�� elemntu ko�cowego
	map<string, vector<int>>::iterator selectedEndLineIterator;
	//wektor wybranej linii wej�� elementu ko�cowego
	vector<int> accessibleInputs;

	//FLAGI i ZMIENNE
	bool mustSelectBegin = true;	//flaga poprawno�ci wyboru pocz�tku przewodu
	bool mustSelectEnd = true;		//flaga poprawno�ci wyboru ko�ca przewodu
	int countOfAccessibleOutputs = accessibleOutputs.size();	//liczb� dost�pnych pin�w wyj�� elemntu pocz�tkowego
	int countOfAccessibleInputs = 0;//liczba dost�pnych pin�w wej�� elemntu ko�cowego
	int selectedBegin = 0;			//numer wybranego pinu wyj�cia elemntu pocz�tkowego
	int selectedEnd = 0;			//numer wybranego pinu wej�cia elemntu ko�cowego

	//sprawdzanie konieczno�ci wyboru pocz�tku przewodu
	try
	{
		//sprawdza czy element pocz�tkowy to bramka
		Gate *checkIfItsGate = dynamic_cast<Gate*>(inLE);
		if (checkIfItsGate != nullptr)
		{
			selectedBegin = accessibleOutputs[0];
			mustSelectBegin = false;
		}
	}
	catch (std::bad_cast)
	{
		mustSelectBegin = true;
	}

	//sprawdza czy elemnt pocz�tkowy to sta�a
	if (inLE->getElemFlag() == Element::eConstant) 
	{
		selectedBegin = accessibleOutputs[0];
		mustSelectBegin = false;
	}

	//wybieranie pinu pocz�tku przewodu
	while (mustSelectBegin)
	{
		cout << "Wybierz pocz�tek poloczenia (wpisz to co po dwukropku):\n";
		//wypisanie wszytskich dost�pnych wyj��
		for (int i = 0; i < countOfAccessibleOutputs; i++)
		{
			cout << "wyjscie " << accessibleOutputs[i] << ": " << accessibleOutputs[i] << endl;
		}
		cout << "anuluj: -1\n";
		cin >> selectedBegin;
		if (selectedBegin == -1) throw CancelEx();
		//sprawdzenie poprawno�ci wybrania przez u�ytkownika
		for (int i = 0; i < countOfAccessibleOutputs; i++)
		{
			if (selectedBegin == accessibleOutputs[i])
			{
				mustSelectBegin = false;
			}
		}
	}

	//sprawdzanie konieczno�ci/poprawno�ci wyboru ko�ca przewodu
	if (outLE->getElemFlag() == Element::eConstant)
	{
		throw LEexception("Nie mozna podlaczyc przewodu do stalej");
	}

	//wybieranie linii wej�� ko�ca przewodu
	if (accessibleInputsMap.size() > 1)
	{//trzeba wybra� lini� wej��
		bool mustSelectLine = true;
		while (mustSelectLine)
		{
			map<int, map<string, vector<int>>::iterator> inputLines; //pomocnicza zmienna wyboru
			int selectedLine = 0;
			int i = 1;
			cout << "Wybierz linie wejsc konca poloczenia (wpisz to co po dwukropku):\n";
			for (auto it = accessibleInputsMap.begin(); it != accessibleInputsMap.end(); it++, i++)
			{
				cout << TranslateIOName(it->first) << ": " << i << endl;
				inputLines.insert(pair<int, map<string, vector<int>>::iterator>(i, it));
			}
			cout << "anuluj: -1\n";
			cin >> selectedLine;
			if (selectedLine == -1) throw CancelEx();
			//sprawdzenie poprawno�ci wyboru u�ytkownika
			auto selectedInputLine = inputLines.find(selectedLine);
			if (selectedInputLine != inputLines.end())
			{
				selectedEndLineIterator = selectedInputLine->second;
				mustSelectLine = false;
			}
		}
	}
	else
	{//mamy tylko jedn� lini� do wyboru
		selectedEndLineIterator = accessibleInputsMap.begin();
	}

	//ustalenie wybranej linii wej�� (odpowiedniego wektora)
	accessibleInputs = selectedEndLineIterator->second;
	countOfAccessibleInputs = accessibleInputs.size();

	//wybieranie pinu ko�ca przewodu
	while (mustSelectEnd)
	{
		cout << "Wybierz koniec poloczenia (wpisz to co po dwukropku)\n";
		cout << "Linia " << TranslateIOName(selectedEndLineIterator->first) <<":\n";
		//wypisanie wszytskich dost�pnych wej��
		for (int i = 0; i < countOfAccessibleInputs; i++)
		{
			cout << "wejscie " << accessibleInputs[i] << ": " << accessibleInputs[i] << endl;
		}
		cout << "anuluj: -1\n";
		cin >> selectedEnd;
		if (selectedEnd == -1) throw CancelEx();
		//sprawdzenie poprawno�ci wybrania przez u�ytkownika
		for (int i = 0; i < countOfAccessibleInputs; i++)
		{
			if (selectedEnd == accessibleInputs[i])
			{
				mustSelectEnd = false;
			}
		}
	}
	//utworzenie w�asciwgo po��czenia
	_wire->selectBegin(inLE, selectedBegin);
	_wire->selectEnd(outLE,selectedEndLineIterator->first, selectedEnd);
	//zaktualizowanie informacji o utworzonym po��czeniu
	_wire->Finalize();
}
void AddNewWire(map<int, LogicElement*> &container)
{
	if (container.size() < 2)
	{
		cout << "Niewystarczajaca ilosc elementow\n";
		return;
	}
	int indxIn = -1;	//index elemntu pocz�tkowego
	int indxOut = -1;	//index elemntu ko�cowego
	cout << "Lista dostepnych elementow:\n";
	int i = 0;
	for (auto it = container.begin(); it != container.end(); it++)
	{
		cout << it->second->getName() << ": " << it->second->getIndex() << endl;
	}
	cout << "Wybierz poczatek poloczenia (wpisz to co po dwukropku): ";
	//wyb�r elemntu pocz�tkowego przewodu
	bool wellSelectedFlag = false;
	while (!wellSelectedFlag)
	{
		cin >> indxIn;
		wellSelectedFlag = Functions::ElementExists(indxIn, container);
	}
	//wyb�r elemntu ko�cowego przewodu
	wellSelectedFlag = false;
	cout << "Wybierz koniec poloczenia: ";
	while (!wellSelectedFlag || indxOut == indxIn)
	{
		cin >> indxOut;
		wellSelectedFlag = Functions::ElementExists(indxOut, container);
	}
	//dodawanie po��cze� na zasadzie wska�nik�w
	Wire *nWire= new Wire();
	try
	{
		MakeWire(nWire, container.at(indxIn), container.at(indxOut)); //wyrzuca wyj�tki LEexception i CancelEx
		try
		{
			Functions::CheckConnectedSeries_start(container[indxIn]); //wyrzuca wyj�tek RaceCondition
		}
		catch (RaceCondition &e)
		{//gdy znajdziemy p�tl� w uk�adzie
			container[indxIn]->connectList.pop_back(); //usuni�cie wadliwego po��czenia
			nWire->ResetEnd();	//odwieszenie warto�ci na wej�ciu elementu ko�cowego
			throw; //reszt� ob�u�y� jeszcze ni�ej
		}
		//jak nie napotkano awarii, zaktualiozwa� seri�
		Functions::UpdateConnectedSeries(container[indxIn]);
		cout << "Utworzono poloczenie\n";
	}
	catch (LEexception &e)
	{//MakeWire rzuca wyj�tki: LEexception i CancelEx		
		cout << e.GetMessage() << endl;
		delete nWire;
		cout << "Nie utworzono poloczenia\n";
	}
}
void ShowLogicElementState(map<string, vector<int>> _map)
{
	//wypisanie zawarto�ci mapy stan�w wej��/wyj�� (zwracana przez metod� ReturnIOState) elemntu logicznego
	for (map<string, vector<int>>::iterator it = _map.begin(); it != _map.end(); ++it)
	{
		cout << TranslateIOName(it->first) << ": "; //wypisanie rodziaju wej��/wyj��
		for (int i = 0; i < it->second.size(); i++)
		{
			cout << it->second.at(i) << " "; //wypisanie warto�ci wszytskich elemnt�w tego rodzaju
		}
		cout << endl;
	}
}
void ShowStates(map<int, LogicElement*> container)
{
	for (auto it = container.begin(); it != container.end(); ++it)
	{
		cout << it->second->getName() << endl;
		ShowLogicElementState(it->second->ReturnIOState());
	}
}
bool CloseApp(map<int, LogicElement*> &container)
{
	int confirm = -1; //flaga potwierdzaj�ca zamkni�cie programu
	do
	{
		cout << "Czy na pewno zamknac program?\n0 - Nie\n1 - Tak\n";
		cin >> confirm; //pobranie decyzji od u�ytkownika
		if (confirm == 1)
		{
			//opr�nienie wszytskich wska�nik�w
			for (auto it = container.begin(); it != container.end(); it++)
			{
				delete it->second;
			}
			container.clear();
			return true;
		}
		if(confirm == 0)
		{
			return false;
		}
	} while (confirm != 0 || confirm != 1);
}