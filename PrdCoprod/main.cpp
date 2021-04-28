#include <iostream>
#include <ilcplex/ilocplex.h>
#include <vector>

#include "Solveur/PLNE.h"
#include "Donnees/CAcquisition.h"
#include "Donnees/CJeuDonnees.h"


using namespace std;

int main()
{
	// -------------------------------- Header --------------------------------
	cout << "==============================================================================================" << endl;
	cout << "		OUTIL D'AIDE A LA DECISION - SNCF - COPROD" << endl;
	cout << "		Projets de Recherche & Developpement - Polytech Tours - 2020/2021" << endl;
	cout << "		PRD Yohan Nouet" << endl;
	cout << "==============================================================================================" << endl << endl;


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

	//affichage des donnees instanciees
	plne.printInfo();
	
	//ajout des contraintes et objectif
	plne.addAllContraintes();
	plne.addObjectif();

	//export du modele
	//plne.exportationModele("AAAAAAAAAAA");
	
	//resolution
	plne.solve();

	return 0;
}