#include <iostream>
#include <Windows.h>
//#include <cstdio>
#include <ilcplex/ilocplex.h>

#include "Tuto.h"
#include "PLNE.h"
#include "PLNE2.h"
#include "CChantier.h"
#include "CAcquisition.h"
#include <vector>
#include "CJeuDonnees.h"

//ILOSTBEGIN

using namespace std;

int main()
{
	//SetConsoleOutputCP(65001);
	//SetConsoleOutputCP(CP_UTF8);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);

	//Tuto::basic();
	//PLNE::run();

	//cout << "====================== Acquisition ===================" << endl << endl;
	//
	//vector<CChantier> chantiers = CAcquisition::chantiers("data/Chantier.csv");
	//for (auto ch = chantiers.begin(); ch != chantiers.end(); ++ch) {
	//cout << *ch << endl;
	//}
	//
	//vector<COperation> operations = CAcquisition::operations("data/op.csv");
	//for (auto op = operations.begin(); op != operations.end(); ++op) {
	//	cout << *op << endl;
	//}

	// génération d'un jeu de données 
	CInput input = CJeuDonnees::version1();
	//input.print();

	// instanciation du modèle Cplex à partir du jeu de données
	PLNE plne(input);
	plne.printInfo();

	int valeur = plne.opX(1,0);

	cout <<" valeur : "<< valeur << endl;

	cout << plne.opY(1, 0) << endl;

	return 0;
}



