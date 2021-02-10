

#include "pch.h"
#include <iostream>
#include <ilcplex/ilocplex.h>
//ILOSTBEGIN

using namespace std;

int main()
{
	IloEnv env; //variable d'environnement

	try {
		IloModel model(env); //modèle, on l'associe directement à l'environnement
		IloCplex cplex(model); //solveur, on l'associe directement au modèle

		// ---------- Variables --------------

		IloNumVar x1(env, 0.0, 40.0, ILOFLOAT, "x1");
		IloNumVar x2(env, -10, 20, ILOINT, "x2");
		model.add(x1);
		model.add(x2);

		//------------ Contraintes ---------------

		//1ere contrainte : 2.5 x1 +x2 >= 2
		IloRange ctr1(env, 2, 2.5 * x1 + x2, IloInfinity, "C1");
		model.add(ctr1);

		// 2nde contrainte : x1 - 3 x2 <= 10
		IloRange ctr2(env, -IloInfinity, x1 - 3 * x2, 10, "C2");
		model.add(ctr2);

		// ------------ Objectif ------------------
		IloObjective obj(env, x1 + x2, IloObjective::Minimize, "OBJ");
		model.add(obj);

		// ------------ Solveur -------------------
		cplex.exportModel("test.lp");
		cplex.solve();
		cplex.writeSolution("sol.txt");

		// récupère la solution et l'affiche à l'écran
		std::cout << " status = " << cplex.getStatus() << std::endl;
		std::cout << " objectif = " << cplex.getObjValue() << std::endl;
		std::cout << " X1 = " << cplex.getValue(x1) << std::endl;
		std::cout << " X2 = " << cplex.getValue(x2) << std::endl;
	}
	catch (IloException &e) {
		cerr << "Exception de la Concert Technology" << e << endl;
	}
	catch (...) {
		cerr << "Exception inconnue" << endl;
	}

	
	env.end(); //libération de l'environnement
	return 0;
}



