#include <iostream>
#include <Windows.h>
//#include <cstdio>
#include <ilcplex/ilocplex.h>

#include "Tuto.h"
#include "PLNE.h"
#include "CChantier.h"
#include "CAcquisition.h"
#include <vector>

//ILOSTBEGIN

using namespace std;

int main()
{
	//SetConsoleOutputCP(65001);
	//SetConsoleOutputCP(CP_UTF8);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);

	Tuto::basic();
	PLNE::run();

	cout << "====================== Acquisition ===================" << endl << endl;

	vector<CChantier> chantiers = CAcquisition::chantiers("data/Chantier.csv");
	for (auto ch = chantiers.begin(); ch != chantiers.end(); ++ch) {
	cout << *ch << endl;
	}

	return 0;
}



