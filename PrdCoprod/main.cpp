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

	//vector<CChantier> chantiers = CAcquisition::chantiers("data/Chantier.csv");
	//for (auto ch = chantiers.begin(); ch != chantiers.end(); ++ch) {
	//cout << *ch << endl;
	//}

	//vector<COperation> operations = CAcquisition::operations("data/op.csv");
	/*for (auto op = operations.begin(); op != operations.end(); ++op) {
		cout << *op << endl;
	}*/
	
	//PLNE2 plne2;
	//cout << plne2.opY(0, 0) <<endl;

	///////////			construction jeu de données		//////////////
	//		2 operations : op[0] = preventif, op[1] = correctif

	const int nbOperations = 2;

	double p[nbOperations] = {1.5,2};
	vector<double> p_ { 0,0.5 };
	double pDelta[nbOperations] = { 0,0.5};
	
	int r[nbOperations] = { 0,1 };
	int d[nbOperations] = { 12,14 };
	double w[nbOperations] = { 0.1,0.2 };
	double u[nbOperations] = { 0,0.5 };

	CInput input(4,2,24,1,1,3,2,3,2,0.10,p_);
	input.print();

	PLNE plne(input);
	plne.print();
	cout << plne.opY(0, 1) << endl;

	return 0;
}



