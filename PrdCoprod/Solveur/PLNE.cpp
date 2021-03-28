/*!
 * \file PLNE.cpp
 * \brief Elements permettant de construire et resoudre un probleme d'optimisation
 * \author Yohan Nouet
 * \version 1
 */

#include "PLNE.h"
using  std::cout;
using  std::endl;
//#include<algorithm>

PLNE::PLNE(CInput input)
{
	cout << "Instanciation PLNE ..." << endl;

	try {

		n = input.getN(); // nombre total d'operations
		m = input.getM(); // nombre de voies
		D = input.getD(); // Horizon de planification (en heures)
		nInfra = input.getNInfra(); // nb de types d'infrastructures
		nSite = input.getNSite(); // nb sites
		nSlot = input.getNSlot(); // Nombre de creneaux horaires de travail des sites sur l’horizon
		nTrain = input.getNTrain(); // nb rames
		nAgent = input.getNAgent(); // nb agents
		nSkill = input.getNSkill();// nb competences
		alpha = input.getAlpha(); //taux d'avance maximum par rapport a la butee

		// -------------------------- definition des donnees vectorielles --------------------------------------//

		p = IloIntArray(env, n);
		for (int i = 0; i < n; i++) {
			p[i] = input.getP().at(i); //initialisation des donnees input
		}

		pDelta = IloIntArray(env, n);
		for (int i = 0; i < n; i++) {
			pDelta[i] = input.getPDelta().at(i);
		}

		r = IloIntArray(env, n);
		for (int i = 0; i < n; i++) {
			r[i] = input.getR().at(i);
		}

		d = IloIntArray(env, n);
		for (int i = 0; i < n; i++) {
			d[i] = input.getDateDeRentree().at(i);
		}

		w = IloNumArray(env, n);
		for (int i = 0; i < n; i++) {
			w[i] = input.getW().at(i);
		}

		u = IloNumArray(env, n);
		for (int i = 0; i < n; i++) {
			u[i] = input.getU().at(i);
		}

		NI_ik = IloArray<IloBoolArray>(env, n);
		for (int i = 0; i < n; i++) {
			NI_ik[i] = IloBoolArray(env, nInfra);
			for (int k = 0; k < nInfra; k++) {
				NI_ik[i][k] = input.getNI_ik().at(i).at(k);
			}
		}

		IN_jk = IloArray<IloBoolArray>(env, m);
		for (int j = 0; j < m; j++) {
			IN_jk[j] = IloBoolArray(env, nInfra);
			for (int k = 0; k < nInfra; k++) {
				IN_jk[j][k] = input.getIN_jk().at(j).at(k);
			}
		}

		rMax_lh = IloArray<IloIntArray>(env, nSite);
		for (int l = 0; l < nSite; l++) {
			rMax_lh[l] = IloIntArray(env, nSlot);
			for (int h = 0; h < nSlot; h++) {
				rMax_lh[l][h] = input.getRMax_lh().at(l).at(h);
			}
		}

		rTot = IloIntArray(env, D);
		for (int h = 0; h < D; h++) {
			rTot[h] = input.getRTot().at(h);
		}

		//Duree de voyage pour aller de la gare g1 a la gare g2
		// TODO IloNumArray v(env, D);

		nPrev = IloIntArray(env, nTrain);  // on les laisse de coter pour voir si on en a besoin

		nCorr = IloIntArray(env, nTrain); // on les laisse de coter pour voir si on en a besoin

		CO_ii = IloArray<IloBoolArray>(env, n);
		for (int i = 0; i < n; i++) {
			CO_ii[i] = IloBoolArray(env, n);
			for (int i2 = 0; i2 < n; i2++) {
				CO_ii[i][i2] = input.getCO_ii().at(i).at(i2);
			}
		}

		NS_is = IloArray<IloIntArray>(env, n);
		for (int i = 0; i < n; i++) {
			NS_is[i] = IloIntArray(env, nSkill);
			for (int s = 0; s < nSkill; s++) {
				NS_is[i][s] = input.getNS_is().at(i).at(s);
			}
		}

		SKL_asl = IloArray<IloArray<IloBoolArray> >(env, nAgent);
		for (int a = 0; a < nAgent; a++) {
			SKL_asl[a] = IloArray<IloBoolArray>(env, nSkill);
			for (int s = 0; s < nSkill; s++) {
				SKL_asl[a][s] = IloBoolArray(env, nSite);
				for (int l = 0; l < nSite; l++) {
					SKL_asl[a][s][l] = input.getSKL_asl().at(a).at(s).at(l);
				}
			}
		}

		// -------------------------- definition des ensembles --------------------------------------//

		H = IloArray<IloIntArray>(env, nSlot);
		for (int h = 0; h < nSlot; h++) {
			H[h] = IloIntArray(env); //taille variable pour chaque H[h]
			for (int q = 0; q < input.getH().at(h).size(); q++) { //selon le cardinal de chaque slot on ajoute les valeurs
				H[h].add(input.getH().at(h).at(q));
			}
		}

		L = IloArray<IloIntArray>(env, nSite);
		for (int l = 0; l < nSite; l++) {
			L[l] = IloIntArray(env); //taille variable pour chaque L[l]
			for (int q = 0; q < input.getL().at(l).size(); q++) { //selon le cardinal de chaque ensemble
				L[l].add(input.getL().at(l).at(q));
			}
		}

		Oprev = IloArray<IloIntArray>(env, nTrain);
		for (int f = 0; f < nTrain; f++) {
			Oprev[f] = IloIntArray(env); //taille variable pour chaque Oprev[f]
			for (int q = 0; q < input.getOprev().at(f).size(); q++) { //selon le cardinal de chaque ensemble
				Oprev[f].add(input.getOprev().at(f).at(q));
			}
		}

		Ocorr = IloArray<IloIntArray>(env, nTrain);
		for (int f = 0; f < nTrain; f++) {
			Ocorr[f] = IloIntArray(env); //taille variable pour chaque Ocorr[f]
			for (int q = 0; q < input.getOcorr().at(f).size(); q++) { //selon le cardinal de chaque ensemble
				Ocorr[f].add(input.getOcorr().at(f).at(q));
			}
		}

		Ttrain = IloArray<IloArray<IloIntArray> >(env, nTrain);
		for (int f = 0; f < nTrain; f++) {
			Ttrain[f] = IloArray<IloIntArray>(env, input.getTtrain().at(f).size()); // tableau qui va contenir les q creneaux de disponibilite -> pour chaque rame on dimensionne selon le nombre de creneaux
			for (int q = 0; q < input.getTtrain().at(f).size(); q++) {	//selon le cardinal de chaque ensemble
				Ttrain[f][q] = IloIntArray(env, 2);					// chaque creneau est un tableau de 2 ints 
				Ttrain[f][q][0] = input.getTtrain().at(f).at(q).at(0);	// date de debut du creneau q
				Ttrain[f][q][1] = input.getTtrain().at(f).at(q).at(1);	// date de fin du creneau q
			}
		}

		Ttrack = IloArray<IloArray<IloIntArray> >(env, m);
		for (int j = 0; j < m; j++) {
			Ttrack[j] = IloArray<IloIntArray>(env, input.getTtrack().at(j).size()); // tableau qui va contenir les q creneaux de disponibilite a ajouter au cas par cas puisque chaque voie va avoir des creneaux differents
			for (int q = 0; q < input.getTtrack().at(j).size(); q++) {	//selon le cardinal de chaque ensemble
				Ttrack[j][q] = IloIntArray(env, 2);					// chaque creneau est un tableau de 2 ints 
				Ttrack[j][q][0] = input.getTtrack().at(j).at(q).at(0);	// date de debut du creneau q
				Ttrack[j][q][1] = input.getTtrack().at(j).at(q).at(1);	// date de fin du creneau q
			}
		}

		Tfj = IloArray<IloArray<IloArray<IloIntArray> > >(env, nTrain);
		for (int f = 0; f < nTrain; f++) {
			Tfj[f] = IloArray<IloArray<IloIntArray> >(env, m); // tableau de chaque rame qui comporte l'ensemble des voies
			for (int j = 0; j < m; j++) {
				Tfj[f][j] = IloArray<IloIntArray>(env, input.getTfj().at(f).at(j).size()); //ensemble de couples [t-,t+]1, [t-,t+]2... de compatibilite de la rame f et de la voie j. Selon le cardinal de chaque ensemble
				for (int q = 0; q < input.getTfj().at(f).at(j).size(); q++) {	//selon le cardinal de chaque ensemble
					Tfj[f][j][q] = IloIntArray(env, 2);					// chaque creneau q est un tableau de 2 ints 
					Tfj[f][j][q][0] = input.getTfj().at(f).at(j).at(q).at(0);	// date de debut du creneau q
					Tfj[f][j][q][1] = input.getTfj().at(f).at(j).at(q).at(1);	// date de fin du creneau q
				}
			}
		}

		Tagent = IloArray<IloArray<IloIntArray> >(env, nAgent);
		for (int a = 0; a < nAgent; a++) {
			Tagent[a] = IloArray<IloIntArray>(env, input.getTagent().at(a).size()); // tableau qui va contenir les q creneaux de disponibilite a ajouter au cas par cas puisque chaque agent va avoir des creneaux differents
			for (int q = 0; q < input.getTagent().at(a).size(); q++) {	//selon le cardinal de chaque ensemble
				Tagent[a][q] = IloIntArray(env, 2);					// chaque creneau est un tableau de 2 ints 
				Tagent[a][q][0] = input.getTagent().at(a).at(q).at(0);	// date de debut du creneau q
				Tagent[a][q][1] = input.getTagent().at(a).at(q).at(1);	// date de fin du creneau q
			}
		}

		// -------------------------- Variables --------------------------------------//
		//modele CPLEX
		model = IloModel(env);
		cplex = IloCplex(model);

		//////////////////////////////// variable X //////////////////////////////////

		X = IloArray< IloArray< IloArray<IloBoolVarArray> > >(env, nTrain);

		//boucle sur les rames
		for (int f = 0; f < nTrain; f++) {

			int cardPrev = Oprev[f].getSize(); //nombre d'operations preventives
			int cardCorr = Ocorr[f].getSize(); //nombre d'operations correctives

			X[f] = IloArray< IloArray<IloBoolVarArray> >(env, cardPrev + cardCorr);

			//boucle sur les operations prev + corr
			for (int i = 0; i < cardPrev + cardCorr; i++) {
				X[f][i] = IloArray<IloBoolVarArray>(env, m);

				//boucle sur les voies
				for (int j = 0; j < m; j++) {
					X[f][i][j] = IloBoolVarArray(env);

					//int nbCreneaux = Tfj[f][j].getSize();
					//
					////boucle sur les creneaux
					//for (int c = 0; c < nbCreneaux; c++) {
					//	int debut = Tfj[f][j][c][0];
					//	int fin = Tfj[f][j][c][1];
					//
					//	//on cree (fin - debut+1) variables qui sont ajoutees a X[f][i][j]
					//	for (int t = 0; t < fin - debut+1; t++) {
					//		IloBoolVar variable(env);
					//		X[f][i][j].add(variable);
					//
					//		//ajout au model CPLEX
					//		model.add(variable);
					//
					//	}
					//}

					//boucle sur le temps
					for (int t = 0; t < D; t++) {
						IloBoolVar variable(env);
						X[f][i][j].add(variable);

						//ajout au model CPLEX
						model.add(variable);
					}
				}
			}
		}

		//////////////////////////////// variable Y //////////////////////////////////

		Y = IloArray<IloBoolVarArray>(env, nTrain);

		//boucle sur les rames
		for (int f = 0; f < nTrain; f++) {

			Y[f] = IloBoolVarArray(env, Ocorr[f].getSize()); //chaque Y[f] est dimensionne selon le nombre d'operations contenues dans Ocorr[f]

			for (int i = 0; i < Ocorr[f].getSize(); i++) {
				model.add(Y[f][i]); //ajout de la variabe au modele cplex
			}
		}

		//////////////////////////////// variable Z //////////////////////////////////

		Z = IloArray< IloArray< IloArray<IloBoolVarArray> > >(env, nAgent);

		//boucle sur les agents
		for (int a = 0; a < nAgent; a++) {
			Z[a] = IloArray< IloArray<IloBoolVarArray> >(env, nTrain);

			//recuperation du nombre de creneau de l'agent
			int nbCreneaux = Tagent[a].getSize();

			//boucle sur les rames
			for (int f = 0; f < nTrain; f++) {

				int cardPrev = Oprev[f].getSize(); //nombre d'operations preventives
				int cardCorr = Ocorr[f].getSize(); //nombre d'operations correctives

				Z[a][f] = IloArray<IloBoolVarArray>(env, cardPrev + cardCorr);

				//boucle sur les operations
				for (int i = 0; i < cardPrev + cardCorr; i++) {

					Z[a][f][i] = IloBoolVarArray(env);

					////boucle sur les creneaux
					//for (int c = 0; c < nbCreneaux; c++) {
					//	int debut = Tagent[a][c][0];
					//	int fin = Tagent[a][c][1];
					//
					//	//on cree (fin - debut) variables qui sont ajoutees a A[a][f][i]
					//	for (int t = 0; t < fin - debut; t++) {
					//		IloBoolVar variable(env);
					//		Z[a][f][i].add(variable);
					//
					//		//ajout au model CPLEX
					//		model.add(variable);
					//
					//	}
					//}

					//boucle sur le temps
					for (int t = 0; t < D; t++) {
						IloBoolVar variable(env);
						Z[a][f][i].add(variable);

						//ajout au model CPLEX
						model.add(variable);
					}
				}
			}
		}

		//////////////////////////////// variable E //////////////////////////////////

		E = IloArray< IloArray<IloBoolVarArray> >(env, nTrain);

		//boucle sur les rames
		for (int f = 0; f < nTrain; f++) {
			E[f] = IloArray<IloBoolVarArray>(env, nSite);

			//boucle sur les sites
			for (int l = 0; l < nSite; l++) {
				E[f][l] = IloBoolVarArray(env, D); //PAS SUR DU D

				for (int t = 0; t < D; t++)
					model.add(E[f][l][t]); //ajout de la variabe au modele cplex
			}
		}

		//////////////////////////////// variable Estart //////////////////////////////////

		Estart = IloArray<IloBoolVarArray>(env, nTrain);

		//boucle sur les rames
		for (int f = 0; f < nTrain; f++) {
			Estart[f] = IloBoolVarArray(env, nSite);

			//boucle sur les sites
			for (int l = 0; l < nSite; l++) {
				model.add(Estart[f][l]); //ajout de la variabe au modele cplex
			}
		}

		//////////////////////////////// variable S //////////////////////////////////

		S = IloArray<IloIntVarArray>(env, nTrain);

		//boucle sur les rames
		for (int f = 0; f < nTrain; f++) {
			int cardPrev = Oprev[f].getSize(); //nombre d'operations preventives
			int cardCorr = Ocorr[f].getSize(); //nombre d'operations correctives
			S[f] = IloIntVarArray(env, cardPrev + cardCorr, 0, D);

			//boucle sur les operations
			for (int i = 0; i < cardPrev + cardCorr; i++) {
				model.add(S[f][i]); //ajout de la variabe au modele cplex
			}
		}

		//////////////////////////////// variable C //////////////////////////////////

		C = IloArray<IloIntVarArray>(env, nTrain);

		//boucle sur les rames
		for (int f = 0; f < nTrain; f++) {
			int cardPrev = Oprev[f].getSize(); //nombre d'operations preventives
			int cardCorr = Ocorr[f].getSize(); //nombre d'operations correctives
			C[f] = IloIntVarArray(env, cardPrev + cardCorr, 0, D);

			//boucle sur les operations
			for (int i = 0; i < cardPrev + cardCorr; i++) {
				model.add(C[f][i]); //ajout de la variabe au modele cplex
			}
		}

		//////////////////////////////// variable Eprev //////////////////////////////////

		Eprev = IloArray<IloIntVarArray>(env, nTrain);

		//boucle sur les rames
		for (int f = 0; f < nTrain; f++) {

			Eprev[f] = IloIntVarArray(env, Oprev[f].getSize()); //pour les IloBoolVarArray, la declaration du tableau comme ici suffit a instancier les variables, ici il est necessaire de le faire.

			//boucle sur les operations preventives
			for (int i = 0; i < Oprev[f].getSize(); i++) {
				Eprev[f][i] = IloIntVar(env); //declaration de la variable
				model.add(Eprev[f][i]);
			}
		}

		//////////////////////////////// variable Tcorr //////////////////////////////////

		Tcorr = IloArray<IloIntVarArray>(env, nTrain);

		//boucle sur les rames
		for (int f = 0; f < nTrain; f++) {

			Tcorr[f] = IloIntVarArray(env, Ocorr[f].getSize()); //pour les IloBoolVarArray, la declaration du tableau comme ici suffit a instancier les variables, ici il est necessaire de le faire.

			//boucle sur les operations correctives
			for (int i = 0; i < Ocorr[f].getSize(); i++) {
				Tcorr[f][i] = IloIntVar(env); //declaration de la variable
				model.add(Tcorr[f][i]);
			}
		}

		// -------------------------------- Contraintes ------------------------------------//
		// l'ajout des contraintes est deplace dans des methodes separees
			
	} //fin try
	catch(IloException&e){
		cerr<<"ConcertException: "<<e<<endl;
	}
	catch(...){
		cerr<<"Autre Exception "<<endl;
	}

	cout << "Instanciation PLNE : OK" << endl;
}

void PLNE::addContrainte1() {
	cout << "+ Ajout contrainte 1 au modele" << endl;
	
	IloNum EPSILON = 0.5;

	// boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbCorr = Ocorr[f].getSize();

		// boucle sur les operations correctives de la rame
		for (int i = 0; i < nbCorr; i++) {
			// contrainte :
			model.add(Y[f][i] * u[getIndiceGeneralFromOperationCorrective(f, i)] <= EPSILON);
		}
	}
}

void PLNE::addContrainte2() {
	cout << "+ Ajout contrainte 2 au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();


		// boucle sur les operations correctives de la rame
		for (int i = 0; i < nbCorr; i++) {
			// contrainte :
			model.add(Tcorr[f][i] >= S[f][nbPrev + i] - d[getIndiceGeneralFromOperationCorrective(f, i)]);
		}
	}
}

void PLNE::addContrainte3() {
	cout << "+ Ajout contrainte 3 au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();

		//boucle sur les operations preventives de la rame
		for (int i = 0; i < nbPrev; i++) {
			// contrainte
			model.add(Eprev[f][i] >= d[getIndiceGeneralFromOperationPreventive(f, i)] - C[f][i]);
		}
	}
}

void PLNE::addContrainte4() {
	cout << "+ Ajout contrainte 4 au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations preventives
		for (int i = 0; i < nbPrev; i++) {
			//contrainte (4.1)
			model.add(C[f][i] == S[f][i] + p[getIndiceGeneralFromOperationPreventive(f, i)]);
		}

		//boucle sur les operations correctives
		for (int i = nbPrev; i < nbPrev + nbCorr; i++) {
			//contrainte (4.2)
			model.add(C[f][i] == S[f][i] + pDelta[getIndiceGeneralFromOperation(f, i)] + (1 - Y[f][i - nbPrev])*p[getIndiceGeneralFromOperation(f, i)]);
		}
	}
}

void PLNE::addContrainte5() {
	cout << "+ Ajout contrainte 5prev au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations prev de la rame f
		for (int i = 0; i < nbPrev; i++) {

			// expression qui va servir a sommer les variables de la contrainte
			IloExpr sommeExpr(env);

			//boucle sur les voies
			for (int j = 0; j < m; j++) {

				// nombre de couples de dispo de la rame f et voie j
				int nbCouples = Tfj[f][j].getSize();

				// parcourt les couples
				for (int q = 0; q < nbCouples; q++) {

					int debut = Tfj[f][j][q][0];
					int fin = Tfj[f][j][q][1];

					//TODO cas a traiter ou fin - p[getIndiceGeneralFromOperation(f, i)] + 1 plus petit que debut

					// parcourt le temps du couple
					for (int t = debut; t <= fin - p[getIndiceGeneralFromOperation(f, i)] + 1; t++) {

						// ajout a la partie somme de la contrainte
						sommeExpr += X[f][i][j][t] * t;//sommeExpr += X[f][i][j][getIndiceTempsFromValeur(f, j, q, t)] * t;
					}
				}
			}
			// contrainte
			model.add(S[f][i] >= sommeExpr);
		}
	}

	/////////////// Contrainte 5 correctif

	cout << "+ Ajout contrainte 5corr au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations corr de la rame f
		for (int i = nbPrev; i < nbPrev + nbCorr; i++) {

			// expression qui va servir a sommer les variables de la contrainte
			IloExpr sommeExpr(env);

			//boucle sur les voies
			for (int j = 0; j < m; j++) {

				// nombre de couples de dispo de la rame f et voie j
				int nbCouples = Tfj[f][j].getSize();

				// parcourt les couples
				for (int q = 0; q < nbCouples; q++) {

					int debut = Tfj[f][j][q][0];
					int fin = Tfj[f][j][q][1];

					//TODO cas a traiter ou fin - p[getIndiceGeneralFromOperation(f, i)] + 1 plus petit que debut

					// parcourt le temps du couple
					for (int t = debut; t <= fin - pDelta[getIndiceGeneralFromOperation(f, i)] + 1; t++) {

						// ajout a la partie somme de la contrainte
						sommeExpr += X[f][i][j][t] * t;
					}
				}
			}
			// contrainte
			model.add(S[f][i] >= sommeExpr);
		}
	}
}

void PLNE::addContrainte6() {
	cout << "+ Ajout contrainte 6prev au modele" << endl;
	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations prev de la rame f
		for (int i = 0; i < nbPrev; i++) {

			// expression qui va servir a sommer les variables de la contrainte
			IloExpr sommeExpr(env);

			//boucle sur les voies
			for (int j = 0; j < m; j++) {

				// nombre de couples de dispo de la rame f et voie j
				int nbCouples = Tfj[f][j].getSize();

				// parcourt les couples
				for (int q = 0; q < nbCouples; q++) {

					int debut = Tfj[f][j][q][0];
					int fin = Tfj[f][j][q][1];
					
					//TODO cas a traiter ou fin - p[getIndiceGeneralFromOperation(f, i)] + 1 plus petit que debut

					// parcourt le temps du couple
					for (int t = debut; t <= fin - p[getIndiceGeneralFromOperation(f, i)] + 1; t++) {
						
						// si t > alpha*di
						if (t > alpha* d[getIndiceGeneralFromOperationPreventive(f, i)]) {
							//ajout a la partie somme de la contrainte
							sommeExpr += X[f][i][j][t]; 
						}
					}
				}
			}
			// contrainte
			model.add(sommeExpr == 1 );
		}
	}
	/////////////// Contrainte 6 correctif

	cout << "+ Ajout contrainte 6corr au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations corr de la rame f
		for (int i = nbPrev; i < nbPrev + nbCorr; i++) {

			// expression qui va servir a sommer les variables de la contrainte
			IloExpr sommeExpr(env);

			//boucle sur les voies
			for (int j = 0; j < m; j++) {

				// nombre de couples de dispo de la rame f et voie j
				int nbCouples = Tfj[f][j].getSize();

				// parcourt les couples
				for (int q = 0; q < nbCouples; q++) {

					int debut = Tfj[f][j][q][0];
					int fin = Tfj[f][j][q][1];
					
					//TODO cas a traiter ou fin - p[getIndiceGeneralFromOperation(f, i)] + 1 plus petit que debut

					// parcourt le temps du couple
					for (int t = debut; t <= fin - p[getIndiceGeneralFromOperation(f, i)] + 1; t++) {
						
						// ajout a la partie somme de la contrainte
						sommeExpr += X[f][i][j][t];
					}
				}
			}
			// contrainte
			model.add(1 >= sommeExpr >= 1 - Y[f][i - nbPrev]);
		}
	}	
}

void PLNE::addContrainte7() {
	cout << "+ Ajout contrainte 7 au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations corr de la rame f
		for (int i = nbPrev; i < nbPrev + nbCorr; i++) {

			// expression qui va servir a sommer les variables de la contrainte
			IloExpr sommeExpr(env);

			//boucle sur les voies
			for (int j = 0; j < m; j++) {

				// nombre de couples de dispo de la rame f et voie j
				int nbCouples = Tfj[f][j].getSize();

				// parcourt les couples
				for (int q = 0; q < nbCouples; q++) {

					int debut = Tfj[f][j][q][0];
					int fin = Tfj[f][j][q][1];

					// parcourt le temps du couple
					for (int t = debut; t <= fin - pDelta[getIndiceGeneralFromOperation(f, i)] + 1; t++) {

						// ajout a la partie somme de la contrainte
						sommeExpr += X[f][i][j][t];
					}
				}
			}
			// contrainte
			model.add((2 + Y[f][i - nbPrev])/2 >= sommeExpr >= Y[f][i - nbPrev]);
		}
	}
}

void PLNE::addContrainte8() {
	cout << "+ Ajout contrainte 8prev au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations prev de la rame f
		for (int i = 0; i < nbPrev; i++) {

			//boucle sur les voies
			for (int j = 0; j < m; j++) {

				//boucle sur les infrastructures
				for (int k = 0; k < nInfra; k++) {

					// expression qui va servir a sommer les variables de la contrainte
					IloExpr sommeExpr(env);

					// nombre de couples de dispo de la rame f et voie j
					int nbCouples = Tfj[f][j].getSize();

					// parcourt les couples
					for (int q = 0; q < nbCouples; q++) {

						int debut = Tfj[f][j][q][0];
						int fin = Tfj[f][j][q][1];

						// parcourt le temps du couple
						for (int t = debut; t <= fin - p[getIndiceGeneralFromOperation(f, i)] + 1; t++) {

							//ajout a la partie somme de la contrainte
							sommeExpr += X[f][i][j][t]; 
						}
					}
					// contrainte
					model.add(NI_ik[getIndiceGeneralFromOperationPreventive(f, i)][k]*sommeExpr <= IN_jk[j][k]);
				}
			}
		}
	}
	/////////////// Contrainte 8 correctif
	cout << "+ Ajout contrainte 8corr au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations corr de la rame f
		for (int i = nbPrev; i < nbPrev + nbCorr; i++) {

			//boucle sur les voies
			for (int j = 0; j < m; j++) {

				//boucle sur les infrastructures
				for (int k = 0; k < nInfra; k++) {

					// expression qui va servir a sommer les variables de la contrainte
					IloExpr sommeExpr(env);

					// nombre de couples de dispo de la rame f et voie j
					int nbCouples = Tfj[f][j].getSize();

					// parcourt les couples
					for (int q = 0; q < nbCouples; q++) {

						int debut = Tfj[f][j][q][0];
						int fin = Tfj[f][j][q][1];

						// parcourt le temps du couple
						for (int t = debut; t <= fin - pDelta[getIndiceGeneralFromOperation(f, i)] + 1; t++) {

							//ajout a la partie somme de la contrainte
							sommeExpr += X[f][i][j][t]; 
						}
					}
					// contrainte
					model.add(NI_ik[getIndiceGeneralFromOperation(f, i)][k] * sommeExpr <= IN_jk[j][k]);
				}
			}
		}
	}
}

void PLNE::addContrainte9() {
	cout << "+ Ajout contrainte 9 au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations corr de la rame f
		for (int i = nbPrev; i < nbPrev + nbCorr; i++) {

			//boucle sur les voies
			for (int j = 0; j < m; j++) {

				// nombre de couples de dispo de la rame f et voie j
				int nbCouples = Tfj[f][j].getSize();

				// parcourt les couples
				for (int q = 0; q < nbCouples; q++) {

					int debut = Tfj[f][j][q][0];
					int fin = Tfj[f][j][q][1];
					
					// parcourt le temps du couple
					for (int t = debut; t <= fin; t++) {

						// expression qui va servir a sommer les variables de la contrainte
						IloExpr sommeExpr(env);

						// DEBUT DE LA CONTRAINTE (PREMIERES SOMMES)

						// Boucle f' sur les rames
						for(int f2 = 0; f2 < nTrain; f2++) {

							if (f2 != f) {

								int nbPrev2 = Oprev[f2].getSize();
								int nbCorr2 = Ocorr[f2].getSize();

								//boucle sur toutes les operations de f2
								for (int i2 = 0; i2 < nbPrev2 + nbCorr2; i2++) {

									// nombre de couples de dispo de la rame f2 et voie j
									int nbCouplesf2 = Tfj[f2][j].getSize();

									//boucle sur les couples de f2
									for (int q2 = 0; q2 < nbCouplesf2; q2++) {

										//boucle sur le temps
										for (int t2 = t; t2 <= t + pDelta[getIndiceGeneralFromOperation(f, i)] - 1; t2++) {
											// Ajout des Xi',j,t' a la contrainte
											sommeExpr += X[f2][i2][j][t2];
										}
									}
								}
							}
						}
						// SUITE CONTRAINTE (2EMES SOMMES)

						//boucle sur i', operations correctives et preventives de f dont COi,i' == 0
						for (int i2 = 0; i2 < nbPrev + nbCorr; i2++) {

							// non compatibilite des operations 
							if (CO_ii[i][i2] == 0) {

								//boucle sur le temps
								for (int t2 = t; t2 <= t + pDelta[getIndiceGeneralFromOperation(f, i)] - 1; t2++) {
									// Ajout des Xi',j,t' a la contrainte
									sommeExpr += X[f][i2][j][t2]; 
								}
							}
						}
						// AJOUT CONTRAINTE AU MODELE
						model.add(sommeExpr <= (1 - X[f][i][j][t])*n );
					}
				}
			}
		}
	}
}

void PLNE::addContrainte10() {

	cout << "+ Ajout contrainte 10prev au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations prev de la rame f
		for (int i = 0; i < nbPrev ; i++) {

			//boucle sur les voies
			for (int j = 0; j < m; j++) {

				// nombre de couples de dispo de la rame f et voie j
				int nbCouples = Tfj[f][j].getSize();

				// parcourt les couples
				for (int q = 0; q < nbCouples; q++) {
			
					int debut = Tfj[f][j][q][0];
					int fin = Tfj[f][j][q][1];

					// parcourt le temps du couple
					for (int t = debut; t <= fin; t++) { 

						// expression qui va servir a sommer les variables de la contrainte
						IloExpr sommeExpr(env);

						// DEBUT DE LA CONTRAINTE (PREMIERES SOMMES)

						// Boucle f' sur les rames
						for (int f2 = 0; f2 < nTrain; f2++) {
							if (f2 != f) {

								int nbPrev2 = Oprev[f2].getSize();
								int nbCorr2 = Ocorr[f2].getSize();
								
								//boucle sur toutes les operations de f2
								for (int i2 = 0; i2 < nbPrev2 + nbCorr2; i2++) {
									
									// nombre de couples de dispo de la rame f2 et voie j
									int nbCouplesf2 = Tfj[f2][j].getSize();
									
									//boucle sur les couples de f2
									for (int q2 = 0; q2 < nbCouplesf2; q2++) {

										//boucle sur le temps
										for (int t2 = t; t2 <= t + p[getIndiceGeneralFromOperation(f, i)] - 1; t2++) {
											
											// Ajout des Xi',j,t' a la contrainte
											sommeExpr += X[f2][i2][j][t2]; 
										}
									}
								}
							}
						}
						// SUITE CONTRAINTE (2EMES SOMMES)

						//boucle sur i', operations correctives et preventives de f dont COi,i' == 0
						for (int i2 = 0; i2 < nbPrev + nbCorr; i2++) {

							// non compatibilite des operations 
							if (CO_ii[i][i2] == 0) {

								//boucle sur le temps
								for (int t2 = t; t2 <= t + p[getIndiceGeneralFromOperation(f, i)] - 1; t2++) {
									// Ajout des Xi',j,t' a la contrainte
									sommeExpr += X[f][i2][j][t2]; 
								}
							}
						}
						// AJOUT CONTRAINTE AU MODELE
						model.add(sommeExpr <= (1 - X[f][i][j][t])*n);
					}
				}
			}
		}
	}
	/////////////////////////////////  Contrainte 10 correctif   ///////////////////////////////// 

	cout << "+ Ajout contrainte 10corr au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations corr de la rame f
		for (int i = nbPrev; i < nbPrev + nbCorr; i++) {

			//boucle sur les voies
			for (int j = 0; j < m; j++) {

				// nombre de couples de dispo de la rame f et voie j
				int nbCouples = Tfj[f][j].getSize();

				// parcourt les couples
				for (int q = 0; q < nbCouples; q++) {

					int debut = Tfj[f][j][q][0];
					int fin = Tfj[f][j][q][1];

					// parcourt le temps du couple
					for (int t = debut; t <= fin ; t++) {

						// expression qui va servir a sommer les variables de la contrainte
						IloExpr sommeExpr(env);

						// DEBUT DE LA CONTRAINTE (PREMIERES SOMMES)

						// Boucle f' sur les rames
						for (int f2 = 0; f2 < nTrain; f2++) {

							if (f2 != f) {

								int nbPrev2 = Oprev[f2].getSize();
								int nbCorr2 = Ocorr[f2].getSize();

								//boucle sur toutes les operations de f2
								for (int i2 = 0; i2 < nbPrev2 + nbCorr2; i2++) {

									// nombre de couples de dispo de la rame f2 et voie j
									int nbCouplesf2 = Tfj[f2][j].getSize();
									
									//boucle sur les couples de dispo de f2 sur j
									for (int q2 = 0; q2 < nbCouplesf2; q2++) {

										//boucle sur le temps
										for (int t2 = t + pDelta[getIndiceGeneralFromOperation(f, i)]; t2 <= t + p[getIndiceGeneralFromOperation(f, i)] - 1; t2++) {
											// Ajout des Xi',j,t' a la contrainte
											sommeExpr += X[f2][i2][j][t2];
										}
									}
								}
							}
						}
						// SUITE CONTRAINTE (2EMES SOMMES)

						//boucle sur i', operations correctives et preventives de f dont COi,i' == 0
						for (int i2 = 0; i2 < nbPrev + nbCorr; i2++) {

							// non compatibilite des operations 
							if (CO_ii[i][i2] == 0) {

								//boucle sur le temps
								for (int t2 = t + pDelta[getIndiceGeneralFromOperation(f, i)]; t2 <= t + p[getIndiceGeneralFromOperation(f, i)] - 1; t2++) {
									// Ajout des Xi',j,t' a la contrainte
									sommeExpr += X[f][i2][j][t2];
								}
							}
						}
						// AJOUT CONTRAINTE AU MODELE
						model.add(sommeExpr <= (Y[f][i - nbPrev] - X[f][i][j][t] + 1)*n);
					}
				}
			}
		}
	}
}

void PLNE::addContrainte11() {
	cout << "+ Ajout contrainte 11 au modele" << endl;

	//boucle sur l'ensemble du temps
	for (int t = 0; t < D; t++) {

		// expression qui va servir a sommer les variables de la contrainte
		IloExpr sommeExpr(env);

		//boucle sur les sites
		for (int l = 0; l < nSite; l++) {

			//boucle sur les rames
			for (int f = 0; f < nTrain; f++) {
				sommeExpr += E[f][l][t];
			}
		}
		//Contrainte
		model.add(sommeExpr <= rTot[t]);
	}
}

void PLNE::addContrainte12() {
	cout << "+ Ajout contrainte 12prev au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		//boucle sur les sites
		for (int l = 0; l < nSite; l++) {

			//boucle sur le temps
			for (int t = 0; t < D; t++) {

				int nbPrev = Oprev[f].getSize();

				//boucle sur les operations
				for (int i = 0; i < nbPrev; i++) {

					// expression qui va servir a sommer les variables de la contrainte
					IloExpr sommeExpr(env);

					//nombre de voies surle site l
					int nbVoies = L[l].getSize();

					//parcourt des voies du site l
					for (int j = 0; j < nbVoies; j++) {
						
						//parcourt le temps
						int tMax = 0;
						
						if (t - p[getIndiceGeneralFromOperation(f, i)] + 1 > tMax) {
							tMax = t - p[getIndiceGeneralFromOperation(f, i)] + 1;
						}

						for (int t2 = tMax; t2 <= t; t2++) {
							sommeExpr += X[f][i][getIndiceVoieGeneralFromIndiceDansL(l, j)][t2];
						}
					}
					model.add(E[f][l][t] >= sommeExpr);
				}
			}
		}
	}
	/////////////////////////////////  Contrainte 12 correctif (1)   ///////////////////////////////// 

	cout << "+ Ajout contrainte 12corr-1 au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {
		
		//boucle sur les sites
		for (int l = 0; l < nSite; l++) {
			
			//boucle sur le temps
			for (int t = 0; t < D; t++) {
				
				int nbPrev = Oprev[f].getSize();
				int nbCorr = Ocorr[f].getSize();

				//boucle sur les operations correctives
				for (int i = nbPrev; i < nbPrev+nbCorr; i++) {
					
					// expression qui va servir a sommer les variables de la contrainte
					IloExpr sommeExpr(env);

					//nombre de voies surle site l
					int nbVoies = L[l].getSize();

					//parcourt des voies du site l
					for (int j = 0; j < nbVoies; j++) {

						//parcourt le temps 
						int tMax = 0;
						
						if (t - pDelta[getIndiceGeneralFromOperation(f, i)] + 1 > tMax) {
							tMax = t - pDelta[getIndiceGeneralFromOperation(f, i)] + 1;
						}

						for (int t2 = tMax; t2 <= t; t2++) {

							sommeExpr += X[f][i][getIndiceVoieGeneralFromIndiceDansL(l, j)][t2]; 
						}
					}
					model.add(E[f][l][t] >= sommeExpr);
				}
			}
		}
	}
	/////////////////////////////////  Contrainte 12 correctif (2)   ///////////////////////////////// 

	cout << "+ Ajout contrainte 12corr-2 au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		//boucle sur les sites
		for (int l = 0; l < nSite; l++) {

			//boucle sur le temps
			for (int t = 0; t < D; t++) {

				int nbPrev = Oprev[f].getSize();
				int nbCorr = Ocorr[f].getSize();

				//boucle sur les operations correctives
				for (int i = nbPrev; i < nbPrev + nbCorr; i++) {

					// expression qui va servir a sommer les variables de la contrainte
					IloExpr sommeExpr(env);

					//nombre de voies surle site l
					int nbVoies = L[l].getSize();

					//parcourt des voies du site l
					for (int j = 0; j < nbVoies; j++) {

						//parcourt le temps de tMax a tMaxSup
						int tMax = 0;
						if (t - p[getIndiceGeneralFromOperation(f, i)] + 1 > tMax) {
							tMax = t - p[getIndiceGeneralFromOperation(f, i)] + 1;
						}

						int tMaxSup = 0;
						if (t - pDelta[getIndiceGeneralFromOperation(f, i)] > tMaxSup) {
							tMaxSup = t - pDelta[getIndiceGeneralFromOperation(f, i)];
						}

						for (int t2 = tMax; t2 <= tMaxSup; t2++) {

							sommeExpr += X[f][i][getIndiceVoieGeneralFromIndiceDansL(l, j)][t2];
						}
					}
					model.add(E[f][l][t] >= -Y[f][i - nbPrev] + sommeExpr);
				}
			}
		}
	}
}

void PLNE::addContrainte14() {
	cout << "+ Ajout contrainte 14 au modele" << endl;

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//boucle sur les operations de la rame f
		for (int i = 0; i < nbPrev + nbCorr; i++) {

			//boucle sur les competences
			for (int s = 0; s < nSkill; s++) {

				//boucle sur le temps
				for (int t = 0; t < D; t++) {

					//  DEBUT MEMBRE DE GAUCHE

					// expression qui va servir a sommer les variables de la contrainte
					IloExpr sommeExprGauche(env);

					//boucle sur les sites
					for (int l = 0; l < nSite; l++) {

						//boucle sur les agents
						for (int a = 0; a < nAgent; a++) {
							//contrainte
							sommeExprGauche += SKL_asl[a][s][l] * Z[a][f][i][t];
						}
					}
					// DEBUT MEMBRE DE DROITE

					// expression qui va servir a sommer les variables de la contrainte
					IloExpr sommeExprDroite(env);

					//boucle sur les voies
					for (int j = 0; j < m; j++) {

						//parcourt du temps
						int tMax = 0;
						if (t - p[getIndiceGeneralFromOperation(f, i)] + 1 > 0) {
							tMax = t - p[getIndiceGeneralFromOperation(f, i)] + 1;
						}

						for (int t2 = tMax; t2 <= t; t2++) {
							//contrainte
							sommeExprDroite += X[f][i][j][t2];
						}
					}
					// AJOUT CONTRAINTE
					model.add(sommeExprGauche >= sommeExprDroite * NS_is[getIndiceGeneralFromOperation(f, i)][s]);
				}
			}
		}
	}
}

void PLNE::addContrainte15() {
	cout << "+ Ajout contrainte 15 au modele" << endl;

	//boucle sur le temps
	for (int t = 0; t < D; t++) {

		//boucle sur les agents
		for (int a = 0; a < nAgent; a++) {

			// MEMBRE DE GAUCHE
			// expression qui va servir a sommer les variables de la contrainte
			IloExpr sommeExpr(env);

			//boucle sur les rames
			for (int f = 0; f < nTrain; f++) {

				int nbPrev = Oprev[f].getSize();
				int nbCorr = Ocorr[f].getSize();

				//boucle sur les operations de la rame f
				for (int i = 0; i < nbPrev + nbCorr; i++) {
					sommeExpr += Z[a][f][i][t];
				}
			}
			// AJOUT CONTRAINTE
			model.add(sommeExpr <= 1);
		}
	}
}

void PLNE::addContrainte16() {
	cout << "+ Ajout contrainte 16 au modele" << endl;

	//boucle sur les agents
	for (int a = 0; a < nAgent; a++) {

		//boucle sur le temps
		for (int t = 0; t < D; t++) {

			// si l'agent n'est pas disponible a l'heure t
			if (agentDisponibleAUnInstant(a, t) == false) {

				// expression qui va servir a sommer les variables de la contrainte
				IloExpr sommeExpr(env);

				//boucle sur les rames
				for (int f = 0; f < nTrain; f++) {

					int nbPrev = Oprev[f].getSize();
					int nbCorr = Ocorr[f].getSize();

					//boucle sur les operations de la rame f
					for (int i = 0; i < nbPrev + nbCorr; i++) {
						sommeExpr += Z[a][f][i][t];
					}
				}
				// AJOUT CONTRAINTE
				model.add(sommeExpr == 0);
			}
		}
	}
}

void PLNE::addAllContraintes() {
	cout << "Ajout de toutes les contraintes au modele :" << endl;
	addContrainte1(); 
	addContrainte2(); 
	addContrainte3(); 
	addContrainte4();
	addContrainte5(); 
	addContrainte6(); 
	addContrainte7(); 
	addContrainte8(); 

	addContrainte9(); 
	addContrainte10();

	addContrainte11();
	addContrainte12();
	//addContrainte14(); provoque une infaisabilite 
	addContrainte15();
	addContrainte16();

	cout << "Nombre de contraintes total dans le modele (NRows) : " << cplex.getNrows() << endl;
}

void PLNE::addObjectif() {
	cout << "+ Ajout de l'objectif au modele" << endl;

	// expression qui va servir a sommer les composantes de la fonction obj
	IloExpr sommeExpr(env);

	//boucle sur les rames
	for (int f = 0; f < nTrain; f++) {

		int nbPrev = Oprev[f].getSize();
		int nbCorr = Ocorr[f].getSize();

		//PREVENTIF -> boucle sur les operations
		for (int i = 0; i < nbPrev; i++) {
			sommeExpr += w[getIndiceGeneralFromOperationCorrective(f, i)] * Eprev[f][i];
		}


		//CORRECTIF -> boucle sur les operations
		for (int i = 0; i < nbCorr; i++) {
			sommeExpr += w[getIndiceGeneralFromOperationCorrective(f, i)] * Tcorr[f][i];
		}
	}

	// OBJECTIF
	model.add(IloMinimize(env, sommeExpr));
}

void PLNE::printInfo()
{
	cout << endl << "================== instance PLNE : affichage du contenu ==================  " << endl << endl;
	cout << "======== Donnees scalaires ======== " << endl;
	cout << "n : " << n << endl;
	cout << "m : " << m << endl;
	cout << "D : " << D << endl;
	cout << "nInfra : " << nInfra << endl;
	cout << "nSite : " << nSite << endl;
	cout << "nSlot : " << nSlot << endl;
	cout << "nTrain : " << nTrain << endl;
	cout << "nAgent : " << nAgent << endl;
	cout << "nSkill : " << nSkill << endl;
	cout << "alpha : " << alpha << endl ;

	cout << endl << "======== Donnees vectorielles ======== " << endl;
	cout << "p : " << p << endl;
	cout << "pDelta : " << pDelta << endl;
	cout << "r : " << r << endl;
	cout << "d : " << d << endl;
	cout << "w : " << w << endl;
	cout << "u : " << u << endl;
	cout << "NI_ik : " << NI_ik << endl;
	cout << "IN_jk : " << IN_jk << endl;
	cout << "rMax_lh : " << rMax_lh << endl;
	cout << "rTot : " << rTot << endl;
	cout << "CO_ii : " << CO_ii << endl;
	cout << "NS_is : " << NS_is << endl;
	cout << "SKL_asl : " << SKL_asl << endl;

	cout << endl << "======== Donnees Ensemblistes ======== " << endl;
	cout << "H : " << H << endl;
	cout << "L : " << L << endl;
	cout << "Oprev : " << Oprev << endl;
	cout << "Ocorr : " << Ocorr << endl;
	cout << "Ttrain : " << Ttrain << endl;
	cout << "Ttrack : " << Ttrack << endl;
	cout << "Tfj : " << Tfj << endl;
	cout << "Tagent : " << Tagent << endl;

	cout << endl << "======== Variables ======== " << endl;
	cout << endl << "X : " << endl << X << endl;
	cout << endl << "Y : " << endl << Y << endl;
	cout << endl << "Z : " << endl << Z << endl;
	cout << endl << "E : " << endl << E << endl;
	cout << endl << "Estart : " << endl << Estart << endl;
	cout << endl << "S : " << endl << S << endl;
	cout << endl << "C : " << endl << C << endl;
	cout << endl << "Eprev : " << endl << Eprev << endl;
	cout << endl << "Tcorr : " << endl << Tcorr << endl;

	cout << endl << endl;
}

void PLNE::exportationModele(string nom) {
	string nomComplet = nom + ".lp";

	cplex.exportModel(nomComplet.c_str());
	cout << "Exportation du modele " << nomComplet << " OK." << endl;
}

void PLNE::solve() {
	try{
		cplex.solve();
		cout << " status = " << cplex.getStatus() << endl;
		cout << " objectif = " << cplex.getObjValue() << endl;
		cplex.writeSolution("BBBBBBB.txt");
	}
	catch (IloException &e) {
		cerr << "Exception de la Concert Technology" << e << endl;
	}
	catch (...) {
		cerr << "Exception inconnue" << endl;
	}
}

int PLNE::opY(int f, int indice)
{
	if (Y.getSize() > f) {

		if (Y[f].getSize() > indice) {
			return Ocorr[f][indice];
		}
		else {
			//Gestion des erreurs si l'indice depasse le nombre d'operations de la rame f
			if (Ocorr[f].getSize() == 0) {
				cout << "Erreur : la rame " << f << " ne contient aucune operation corrective." << endl;
			}
			else {
				cout << "Erreur : la rame " << f << " ne contient que " << Ocorr[f].getSize() << " operation(s) corrective(s), atteignable(s) avec les indices [0," << Ocorr[f].getSize() - 1 << "]" << endl;
			}
			return -1;
		}
	}
	else {
		cout << "Erreur : depassement de taille du nombre de rames." << endl;
	}
	return -1;
}

int PLNE::opX(int f, int indice)
{
	//verification de la borne max
	if (f < nTrain) {

		//on recupere le cardinal de Oprev et Ocorr
		int cardPrev = Oprev[f].getSize(); //nombre d'operations preventives
		int cardCorr = Ocorr[f].getSize(); //nombre d'operations correctives

		//verification de la borne max
		if (indice < cardPrev + cardCorr){

			// valeur a retourner contenue dans Oprev ou Ocorr
			int idOperation = NULL;

			// soit l'operation est preventive
			if (indice < cardPrev) {
				cout << "OP preventive" << endl;
				idOperation = Oprev[f][indice];
			}

			// soit l'operation est corrective
			if (indice >= cardPrev && indice < cardPrev+cardCorr) {
				cout << "OP Corrective" << endl;
				idOperation = Ocorr[f][indice-cardPrev];
			}

			cout << "Id Operation : "<<idOperation << endl;
			return idOperation;
		}
		else {
			// dans ce cas, l'indice depasse le nombre d'operations de la rame
			//affichage d'un message d'erreur
			if (cardPrev + cardCorr == 0) {
				cout << "Erreur : la rame " << f << " ne contient aucune operation." << endl;
			}
			else {
				cout << "Erreur : la rame " << f << " ne contient que " << cardPrev + cardCorr << " operation(s), atteignable(s) avec les indices [0," << cardPrev + cardCorr - 1 << "]" << endl;
			}
			return -1;
		}
	}
	else {
		cout << "Erreur : depassement de taille du nombre de rames." << endl;
	}
	return -1;
}

int PLNE::getIndiceGeneralFromOperationCorrective(int fParam, int iParam) {

	int compte = 0;

	// verification de la saisie
	if (fParam < nTrain) {

		int f = 0;// indice de la rame

		// on parcour les operations qui precedent la rame fParam
		while (f < fParam) {
			// on ajoute les nombres d'operations preventive et corrective de la rame au total
			compte = compte + Oprev[f].getSize() + Ocorr[f].getSize();
			f++;
		}

		// on ajoute les operations preventives
		compte = compte + Oprev[fParam].getSize();

		// on ajoute les operations correctives jusqu'a iParam
		compte = compte + iParam;

		//retourne la position dans globale de l'operation dans [0, n[
		return compte;

	}
	else {
		cout << "Erreur : depassement de taille du nombre de rames." << endl;
		return -1;
	}
}

int PLNE::getIndiceGeneralFromOperationPreventive(int fParam, int iParam) {

	int compte = 0;

	// verification de la saisie
	if (fParam < nTrain) {

		int f = 0;// indice de la rame

		// on parcour les operations qui precedent la rame fParam
		while (f < fParam) {
			// on ajoute les nombres d'operations preventive et corrective de la rame au total
			compte = compte + Oprev[f].getSize() + Ocorr[f].getSize();
			f++;
		}

		// on ajoute les operations preventives jusqu'a iParam
		compte = compte + iParam;

		//retourne la position dans globale de l'operation dans [0, n[
		return compte;
	}
	else {
		cout << "Erreur : depassement de taille du nombre de rames." << endl;
		return -1;
	}
}

int PLNE::getIndiceGeneralFromOperation(int fParam, int iParam) {

	int compte = 0;

	// verification de la saisie
	if (fParam < nTrain) {

		int f = 0;// indice de la rame

		// on parcour les operations qui precedent la rame fParam
		while (f < fParam) {
			// on ajoute les nombres d'operations preventive et corrective de la rame au total
			compte = compte + Oprev[f].getSize() + Ocorr[f].getSize();
			f++;
		}

		// on ajoute les operations jusqu'a iParam
		compte = compte + iParam;

		//retourne la position dans globale de l'operation dans [0, n[
		return compte;
	}
	else {
		cout << "Erreur : depassement de taille du nombre de rames." << endl;
		return -1;
	}
}

//retourne l'indice d une heure de dispo dans le tableau Xijt a partir de l heure
//int PLNE::getIndiceTempsFromValeur(int fParam, int jParam, int creneauParam, int tParam) {
//
//	// verification de la saisie
//	if (fParam < nTrain) {
//
//		int compteur = 0;
//
//		int nbCreneaux = Tfj[fParam][jParam].getSize();
//
//		//pour tous les creneaux precedents -> on incremente le compteur
//		for (int creneau = 0; creneau < creneauParam; creneau++) {
//
//			// on recupere les heures de debut et fin du creneau
//			int debut = Tfj[fParam][jParam][creneau][0];
//			int fin = Tfj[fParam][jParam][creneau][1];
//
//			compteur = compteur + (fin - debut);
//		}
//
//		// Pour le creneau en question on recupere la date de debut et on l'ajoute au compteur
//		int debut = Tfj[fParam][jParam][creneauParam][0];
//		compteur = compteur + tParam - debut;
//
//		//on retourne la position de ce t dans la liste
//		return compteur;
//	}
//	else {
//		cout << "Erreur : depassement de taille du nombre de rames." << endl;
//		return -1;
//	}
//}

//retourne l'indice d une heure de dispo dans le tableau Xijt a partir de l heure sans tenir compte du creneau horaire (=> 1 heure ne doit pas apparaitre dans des creneaux differents pour un meme couple train|voie)
//int PLNE::getIndiceTempsGeneralFromValeur(int fParam, int jParam, int tParam) {
//
//	// verification de la saisie
//	if (fParam < nTrain) {
//
//		int compteur = 0;
//
//		int nbCreneaux = Tfj[fParam][jParam].getSize();
//
//		//pour tous les creneaux  -> on incremente le compteur tant que l'heure t n'est pas trouvee
//		for (int creneau = 0; creneau < nbCreneaux; creneau++) {
//
//			// on recupere les heures de debut et fin du creneau
//			int debut = Tfj[fParam][jParam][creneau][0];
//			int fin = Tfj[fParam][jParam][creneau][1];
//
//			for (int t = debut; t <= fin; t++) {
//				if (t == tParam) {
//					return compteur;
//				}
//				compteur++;
//			}
//		}
//
//		cout << "Valeur introuvable" << endl;
//		return -1;
//	}
//	else {
//		cout << "Erreur : depassement de taille du nombre de rames." << endl;
//		return -1;
//	}
//}

int PLNE::getIndiceVoieGeneralFromIndiceDansL(int lParam, int jParam) {
	// verification de la saisie
	if (lParam < nSite) {

		// compte le nombre de voie dans L jusqu'a la voie recherchee
		int compte = 0;

		// on compte le nombre de voie sur les autres sites
		for (int l = 0; l < lParam; l++) {
			compte += L[l].getSize();
		}

		//on ajoute le nombre de voie sur le site lParam
		compte += jParam;

		return compte;
	}
	else {
		cout << "Erreur : depassement de taille du nombre de sites." << endl;
		return -1;
	}
}

bool PLNE::agentDisponibleAUnInstant(int agent, int tParam) {

	//recuperes les heures de travail de l'agent
	int nbCreneaux = Tagent[agent].getSize();

	for (int creneau = 0; creneau < nbCreneaux; creneau++) {
		int debut = Tagent[agent][creneau][0];
		int fin = Tagent[agent][creneau][1];

		for (int t = debut; t <= fin; t++) {
			if (t == tParam) {
				return true;
			}
		}
	}

	return false;
}