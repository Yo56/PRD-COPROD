#include <iostream>
//#include <Windows.h>
//#include <cstdio>
#include <ilcplex/ilocplex.h>
#include <vector>

#include "Solveur/Tuto.h"
#include "Solveur/PLNE.h"
#include "Donnees/CAcquisition.h"
#include "Donnees/CJeuDonnees.h"


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

	// generation d'un jeu de donnees 
	CInput input = CJeuDonnees::version1();
	//input.print();

	// instanciation du modele Cplex a partir du jeu de donnees
	PLNE plne(input);
	//plne.printInfo();
	plne.addAllContraintes();

	int valeur = plne.opX(1,0);

	cout <<" valeur : "<< valeur << endl;

	cout << plne.opY(1, 0) << endl;

	cout << "#### " << plne.getIndiceGeneralFromOperationCorrective(1, 0) << endl;
	cout << "#### " << plne.getIndiceGeneralFromOperationPreventive(0, 0) << endl;
	cout << "#### " << plne.getIndiceGeneralFromOperation(1, 0) << endl;
	

	return 0;
}



