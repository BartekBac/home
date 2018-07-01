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
	int enumElem = 0;	//flaga wyboru z puli dostêpnych elemntów
	while (enumElem != 1 && enumElem != 2 && enumElem != 3 && enumElem != 4 && enumElem != 5 && enumElem != 6 && enumElem != 7 && enumElem != 8 && enumElem != 9)
	{//parsowanie wyboru elemntu
		cout << "Wybierz element:\n1 - CONST_VALUE\n2 - AND\n3 - OR\n4 - XOR\n5 - NAND\n6 - NOR\n7 - Latch\n8 - MUX\n9 - DMUX\n";
		cin >> enumElem;
	}
	LogicElement *nElem = nullptr;	//wska¿nik nowotworzonego elemntu
	switch (enumElem)
	{//dodanie wybranego elementu
	case 1:
	{//STA£A
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
	//pobranie wyjœæ elemntu pocz¹tkowego
	vector<int> accessibleOutputs = inLE->ReturnAccessibleOutputs(); 
	//pobranie wszytskich linii wejœæ elemntu koñcowego
	map<string, vector<int>> accessibleInputsMap = outLE->ReturnAccessibleInputs(); //wyrzuca wyj¹tek LEexception gdy nie ma dostêpnych wejœæ
	//iterator wybranej linii wejœæ elemntu koñcowego
	map<string, vector<int>>::iterator selectedEndLineIterator;
	//wektor wybranej linii wejœæ elementu koñcowego
	vector<int> accessibleInputs;

	//FLAGI i ZMIENNE
	bool mustSelectBegin = true;	//flaga poprawnoœci wyboru pocz¹tku przewodu
	bool mustSelectEnd = true;		//flaga poprawnoœci wyboru koñca przewodu
	int countOfAccessibleOutputs = accessibleOutputs.size();	//liczb¹ dostêpnych pinów wyjœæ elemntu pocz¹tkowego
	int countOfAccessibleInputs = 0;//liczba dostêpnych pinów wejœæ elemntu koñcowego
	int selectedBegin = 0;			//numer wybranego pinu wyjœcia elemntu pocz¹tkowego
	int selectedEnd = 0;			//numer wybranego pinu wejœcia elemntu koñcowego

	//sprawdzanie koniecznoœci wyboru pocz¹tku przewodu
	try
	{
		//sprawdza czy element pocz¹tkowy to bramka
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

	//sprawdza czy elemnt pocz¹tkowy to sta³a
	if (inLE->getElemFlag() == Element::eConstant) 
	{
		selectedBegin = accessibleOutputs[0];
		mustSelectBegin = false;
	}

	//wybieranie pinu pocz¹tku przewodu
	while (mustSelectBegin)
	{
		cout << "Wybierz pocz¹tek poloczenia (wpisz to co po dwukropku):\n";
		//wypisanie wszytskich dostêpnych wyjœæ
		for (int i = 0; i < countOfAccessibleOutputs; i++)
		{
			cout << "wyjscie " << accessibleOutputs[i] << ": " << accessibleOutputs[i] << endl;
		}
		cout << "anuluj: -1\n";
		cin >> selectedBegin;
		if (selectedBegin == -1) throw CancelEx();
		//sprawdzenie poprawnoœci wybrania przez u¿ytkownika
		for (int i = 0; i < countOfAccessibleOutputs; i++)
		{
			if (selectedBegin == accessibleOutputs[i])
			{
				mustSelectBegin = false;
			}
		}
	}

	//sprawdzanie koniecznoœci/poprawnoœci wyboru koñca przewodu
	if (outLE->getElemFlag() == Element::eConstant)
	{
		throw LEexception("Nie mozna podlaczyc przewodu do stalej");
	}

	//wybieranie linii wejœæ koñca przewodu
	if (accessibleInputsMap.size() > 1)
	{//trzeba wybraæ liniê wejœæ
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
			//sprawdzenie poprawnoœci wyboru u¿ytkownika
			auto selectedInputLine = inputLines.find(selectedLine);
			if (selectedInputLine != inputLines.end())
			{
				selectedEndLineIterator = selectedInputLine->second;
				mustSelectLine = false;
			}
		}
	}
	else
	{//mamy tylko jedn¹ liniê do wyboru
		selectedEndLineIterator = accessibleInputsMap.begin();
	}

	//ustalenie wybranej linii wejœæ (odpowiedniego wektora)
	accessibleInputs = selectedEndLineIterator->second;
	countOfAccessibleInputs = accessibleInputs.size();

	//wybieranie pinu koñca przewodu
	while (mustSelectEnd)
	{
		cout << "Wybierz koniec poloczenia (wpisz to co po dwukropku)\n";
		cout << "Linia " << TranslateIOName(selectedEndLineIterator->first) <<":\n";
		//wypisanie wszytskich dostêpnych wejœæ
		for (int i = 0; i < countOfAccessibleInputs; i++)
		{
			cout << "wejscie " << accessibleInputs[i] << ": " << accessibleInputs[i] << endl;
		}
		cout << "anuluj: -1\n";
		cin >> selectedEnd;
		if (selectedEnd == -1) throw CancelEx();
		//sprawdzenie poprawnoœci wybrania przez u¿ytkownika
		for (int i = 0; i < countOfAccessibleInputs; i++)
		{
			if (selectedEnd == accessibleInputs[i])
			{
				mustSelectEnd = false;
			}
		}
	}
	//utworzenie w³asciwgo po³¹czenia
	_wire->selectBegin(inLE, selectedBegin);
	_wire->selectEnd(outLE,selectedEndLineIterator->first, selectedEnd);
	//zaktualizowanie informacji o utworzonym po³¹czeniu
	_wire->Finalize();
}
void AddNewWire(map<int, LogicElement*> &container)
{
	if (container.size() < 2)
	{
		cout << "Niewystarczajaca ilosc elementow\n";
		return;
	}
	int indxIn = -1;	//index elemntu pocz¹tkowego
	int indxOut = -1;	//index elemntu koñcowego
	cout << "Lista dostepnych elementow:\n";
	int i = 0;
	for (auto it = container.begin(); it != container.end(); it++)
	{
		cout << it->second->getName() << ": " << it->second->getIndex() << endl;
	}
	cout << "Wybierz poczatek poloczenia (wpisz to co po dwukropku): ";
	//wybór elemntu pocz¹tkowego przewodu
	bool wellSelectedFlag = false;
	while (!wellSelectedFlag)
	{
		cin >> indxIn;
		wellSelectedFlag = Functions::ElementExists(indxIn, container);
	}
	//wybór elemntu koñcowego przewodu
	wellSelectedFlag = false;
	cout << "Wybierz koniec poloczenia: ";
	while (!wellSelectedFlag || indxOut == indxIn)
	{
		cin >> indxOut;
		wellSelectedFlag = Functions::ElementExists(indxOut, container);
	}
	//dodawanie po³¹czeñ na zasadzie wskaŸników
	Wire *nWire= new Wire();
	try
	{
		MakeWire(nWire, container.at(indxIn), container.at(indxOut)); //wyrzuca wyj¹tki LEexception i CancelEx
		try
		{
			Functions::CheckConnectedSeries_start(container[indxIn]); //wyrzuca wyj¹tek RaceCondition
		}
		catch (RaceCondition &e)
		{//gdy znajdziemy pêtlê w uk³adzie
			container[indxIn]->connectList.pop_back(); //usuniêcie wadliwego po³¹czenia
			nWire->ResetEnd();	//odwieszenie wartoœci na wejœciu elementu koñcowego
			throw; //resztê ob³u¿yæ jeszcze ni¿ej
		}
		//jak nie napotkano awarii, zaktualiozwaæ seriê
		Functions::UpdateConnectedSeries(container[indxIn]);
		cout << "Utworzono poloczenie\n";
	}
	catch (LEexception &e)
	{//MakeWire rzuca wyj¹tki: LEexception i CancelEx		
		cout << e.GetMessage() << endl;
		delete nWire;
		cout << "Nie utworzono poloczenia\n";
	}
}
void ShowLogicElementState(map<string, vector<int>> _map)
{
	//wypisanie zawartoœci mapy stanów wejœæ/wyjœæ (zwracana przez metodê ReturnIOState) elemntu logicznego
	for (map<string, vector<int>>::iterator it = _map.begin(); it != _map.end(); ++it)
	{
		cout << TranslateIOName(it->first) << ": "; //wypisanie rodziaju wejœæ/wyjœæ
		for (int i = 0; i < it->second.size(); i++)
		{
			cout << it->second.at(i) << " "; //wypisanie wartoœci wszytskich elemntów tego rodzaju
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
	int confirm = -1; //flaga potwierdzaj¹ca zamkniêcie programu
	do
	{
		cout << "Czy na pewno zamknac program?\n0 - Nie\n1 - Tak\n";
		cin >> confirm; //pobranie decyzji od u¿ytkownika
		if (confirm == 1)
		{
			//opró¿nienie wszytskich wskaŸników
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