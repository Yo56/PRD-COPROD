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

	//double p_[nbOperations] = {1.5,2};
	vector<double> p { 2,1.5 };
	vector<double> pDelta {0,0.5};
	
	vector<int> r { 0,1 };
	vector<int> d { 12,14 };
	vector<double> w { 0.1,0.2 };
	vector<double> u { 0,0.5 };

	vector <vector<int> > NI_ik { {1,0}, {0,1} };
	vector <vector<int> > IN_jk { {1,1}, {1,0} };
	vector <vector<int> > rMax_lh { {4,4,4} };
	vector<int> rTot { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	vector <vector<int> > CO_ii { {1,1}, {1,1} };
	vector <vector<int> >NS_is { {3,3},{3,3} };

	vector <vector <vector<int> > > SKL_asl{ {{1},{0}},   { {0}, {1} },   { {1}, {1} } };

	vector <vector<int> > H { {7,8,9,10,11,12,13,14}, {15,16,17,18,19,20,21,21}, {23,0,1,2,3,4,5,6} };
	vector <vector<int> > L { {22,56} }; //{ {0,1} };

	vector <vector<int> > Oprev { {5},{} };
	vector <vector<int> > Ocorr { {},{8} };

									//	 		  TrainA			   TrainB
									//		    cren1   cren2		   cren1
	vector <vector <vector<int> > > Ttrain { { {10,16}, {18,22} },   { {8,20} } };

									//	 		 VoieA			   VoieB
	vector <vector <vector<int> > > Ttrack { { {8,20}, {22,23} },   { {9,17}, {20,21}, {22,23} } };
	
									//	 							TrainA									TrainB
									//	 					voie1			   voie2				  voie1		voie2
									// creneaux dispo		  A|1				A|2					  B|1		 B|2
	vector < vector <vector <vector<int> > > > Tfj{ { {{10,16}, {18,20}},{{10,16}, {20,21}} },    { {{8,20}}, {{9,17}} } };
	
	vector <vector <vector<int> > > Tagent{ { {8,10}, {11,18} }, { {8,16} } , { {9,18}  } };
	
	//creation de l'objet Input
	CInput input(nbOperations,2,24,2,1,3,2,3,2,0.10,p, pDelta,
		r,d,w,u, NI_ik, IN_jk, rMax_lh,rTot,CO_ii, NS_is, SKL_asl,H, L,
		Oprev, Ocorr, Ttrain, Ttrack, Tfj,Tagent);

	//input.print();


	PLNE plne(input);
	plne.print();

	//cout << plne.opY(0, 1) << endl;

	return 0;
}



