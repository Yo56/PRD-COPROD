#include "PLNE.h"


PLNE::PLNE(CInput input)
{
	cout << "Initialisation PLNE ...";

	n = input.getN(); // nombre total d'opérations
	m = input.getM(); // nombre de voies
	D = input.getD(); // Horizon de planification (en heures)
	nInfra = input.getNInfra(); // nb de types d'infrastructures
	nSite = input.getNSite(); // nb sites
	nSlot = input.getNSlot(); // Nombre de créneaux horaires de travail des sites sur l’horizon
	nTrain = input.getNTrain(); // nb rames
	nAgent = input.getNAgent(); // nb agents
	nSkill = input.getNSkill();// nb compétences
	alpha = input.getAlpha(); //taux d'avance maximum par rapport à la butée

	// -------------------------- definition des données vectorielles --------------------------------------//

	p = IloNumArray(env, n);
	for (int i = 0; i < n; i++) {
		p[i] = input.getP().at(i); //initialisation des données input
	}

	pDelta = IloNumArray(env, n);
	for (int i = 0; i < n; i++) {
		pDelta[i] = input.getP().at(i); 
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
	

	//Durée de voyage pour aller de la gare g1 à la gare g2
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
		Ttrain[f] = IloArray<IloIntArray>(env, input.getTtrain().at(f).size()); // tableau qui va contenir les q creneaux de disponibilité -> pour chaque rame on dimensionne selon le nombre de creneaux
		for (int q = 0; q < input.getTtrain().at(f).size(); q++) {	//selon le cardinal de chaque ensemble
			Ttrain[f][q] = IloIntArray (env, 2);					// chaque creneau est un tableau de 2 ints 
			Ttrain[f][q][0] = input.getTtrain().at(f).at(q).at(0);	// date de debut du creneau q
			Ttrain[f][q][1] = input.getTtrain().at(f).at(q).at(1);	// date de fin du creneau q
		}
	}

	Ttrack = IloArray<IloArray<IloIntArray> >(env, m);
	for (int j = 0; j < m; j++) {
		Ttrack[j] = IloArray<IloIntArray>(env, input.getTtrack().at(j).size()); // tableau qui va contenir les q creneaux de disponibilité à ajouter au cas par cas puisque chaque voie va avoir des creneaux différents
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
			Tfj[f][j] = IloArray<IloIntArray>(env, input.getTfj().at(f).at(j).size()); //ensemble de couples [t-,t+]1, [t-,t+]2... de compatibilité de la rame f et de la voie j. Selon le cardinal de chaque ensemble
			for (int q = 0; q < input.getTfj().at(f).at(j).size(); q++) {	//selon le cardinal de chaque ensemble
				Tfj[f][j][q] = IloIntArray(env, 2);					// chaque creneau q est un tableau de 2 ints 
				Tfj[f][j][q][0] = input.getTfj().at(f).at(j).at(q).at(0);	// date de debut du creneau q
				Tfj[f][j][q][1] = input.getTfj().at(f).at(j).at(q).at(1);	// date de fin du creneau q
			}
		}
	}

	Tagent = IloArray<IloArray<IloIntArray> >(env, nAgent);
	for (int a = 0; a < nAgent; a++) {
		Tagent[a] = IloArray<IloIntArray>(env, input.getTagent().at(a).size()); // tableau qui va contenir les q creneaux de disponibilité à ajouter au cas par cas puisque chaque agent va avoir des creneaux différents
		for (int q = 0; q < input.getTagent().at(a).size(); q++) {	//selon le cardinal de chaque ensemble
			Tagent[a][q] = IloIntArray(env, 2);					// chaque creneau est un tableau de 2 ints 
			Tagent[a][q][0] = input.getTagent().at(a).at(q).at(0);	// date de debut du creneau q
			Tagent[a][q][1] = input.getTagent().at(a).at(q).at(1);	// date de fin du creneau q
		}
	}

	// -------------------------- Variables --------------------------------------//

	Y = IloArray<IloBoolVarArray>(env, nTrain);
	for (int f = 0; f < nTrain; f++) {
		Y[f] = IloBoolVarArray(env);
	}

	cout << "OK" << endl;
}


void PLNE::run() {
	cout << "========== PLNE ============" << endl << endl;
	IloEnv env; //variable d'environnement

	// -------------------------- definition des données scalaires --------------------------------------//

	IloInt n; // nombre total d'opérations
	IloInt m; // nombre de voies
	IloInt D; // Horizon de planification (en heures)
	IloInt nInfra; // nb de types d'infrastructures
	IloInt nSite; // nb sites
	IloInt nSlot; // Nombre de créneaux horaires de travail des sites sur l’horizon
	IloInt nTrain; // nb rames
	IloInt nAgent; // nb agents
	IloInt nSkill; // nb compétences
	IloNum alpha; //taux d'avance maximum par rapport à la butée

	 n = 30; // nombre total d'opérations
	 m = 2; // nombre de voies
	 D = 24; // Horizon de planification (en heures)
	 nInfra = 4; // nb de types d'infrastructures
	 nSite = 1; // nb sites
	 nSlot = 3; // Nombre de créneaux horaires de travail des sites sur l’horizon
	 nTrain = 5; // nb rames
	 nAgent = 3; // nb agents
	 nSkill = 5;// nb compétences
	 alpha = 0.10; //taux d'avance maximum par rapport à la butée

	// -------------------------- definition des données vectorielles --------------------------------------//

	//Durées complètes des opérations i
	IloIntArray p(env, n);

	//Durées diagnostiques des opérations i
	IloIntArray pDelta(env, n);

	//Possibilité de rejeter ou non les opérations i (booléen)
	IloIntArray r(env, n);

	//Dates maximum de début souhaité des opérations i (dates de rentrée souhaitée des rames)
	IloIntArray d(env, n);

	//Poids unitaire de retard des opérations i
	IloIntArray w(env, n);

	//Poids associé au rejets des opérations i
	IloIntArray u(env, n);

	//Besoin de l’opération i en infrastructure k (booléen)
	IloArray<IloBoolArray> NI_ik(env, n); 
	for (int i = 0; i < n; i++) {
		NI_ik[i] = IloBoolArray(env, nInfra);
	}

	//Équipement de la voie j en infrastructure k (booléen)
	IloArray<IloBoolArray> IN_jk(env, m);
	for (int j = 0; j < m; j++) {
		IN_jk[j] = IloBoolArray(env, nInfra);
	}

	//Nombre maximum de rentrées de rames sur le site l pendant le créneau h
	IloArray<IloIntArray> rMax_lh(env, nSite);
	for (int l = 0; l < nSite; l++) {
		rMax_lh[l] = IloIntArray(env, nSlot);
	}

	//Nombre maximum autorisé de rames en maintenance sur le réseau aux dates t
	IloIntArray rTot(env, D);

	//Durée de voyage pour aller de la gare g1 à la gare g2
	// TODO IloNumArray v(env, D);

	//Nombre d'opérations préventives par rame f
	IloIntArray nPrev(env,nTrain); //construction d'un tableau de nTrain cases

	//Nombre d'opérations correctives par rame f
	IloIntArray nCorr(env, nTrain);

	//Matrice de compatibilité des opérations i et i′(booléen)
	IloArray<IloBoolArray> CO_ii(env, n);
	for (int i = 0; i < n; i++) {
		CO_ii[i] = IloBoolArray(env, n);
	}

	//Nombre d’agents ayant la compétence s requise pour l’opération i
	IloArray<IloIntArray> NS_is (env, n);
	for (int i = 0; i < n; i++) {
		NS_is[i] = IloIntArray(env, nSkill);
	}

	//L’agent a dispose de la compétence s sur le site l (booléen)
	IloArray<IloArray<IloBoolArray> > SKL_asl(env, nAgent); // IMPORTANT : espace entre les chevrons -> >' '> 
	for (int a = 0; a < nAgent; a++) {
		SKL_asl[a] = IloArray<IloBoolArray>(env, nSkill);
		for (int s = 0; s < nSkill; s++) {
			SKL_asl[a][s] = IloBoolArray(env, nSite);
		}
	}

	// -------------------------- definition des ensembles --------------------------------------//

	//{Dates t appartenant au créneau horaire h}
	IloArray<IloIntArray> H(env, nSlot);
	for (int h = 0; h < nSlot; h++) {
		H[h] = IloIntArray(env); //taille variable pour chaque H[h]
	}

	//{Voies j appartenant au site l}
	IloArray<IloIntArray> L(env, nSite);
	for (int l = 0; l < nSite; l++) {
		L[l] = IloIntArray(env); //taille variable pour chaque L[l]
	}

	//{Opérations préventives de la rame f}
	IloArray<IloIntArray> Oprev(env, nTrain);
	for (int f = 0; f < nTrain; f++) {
		Oprev[f] = IloIntArray(env); //taille variable pour chaque Oprev[f]
	}
	//{Opérations correctives de la rame f}
	IloArray<IloIntArray> Ocorr(env, nTrain);
	for (int f = 0; f < nTrain; f++) {
		Ocorr[f] = IloIntArray(env); //taille variable pour chaque Ocorr[f]
	}

	//{Intervalles[t−;t+]q de disponibilité de la rame f}
	IloArray<IloArray<IloIntArray> > Ttrain(env, nTrain); 
	for (int f = 0; f < nTrain; f++) {
		Ttrain[f] = IloArray<IloIntArray>(env); // tableau qui va contenir les q creneaux de disponibilité à ajouter au cas par cas puisque chaque rame va avoir des creneaux différents
		// chaque creneau est un tableau de 2 ints 
	}

	//{Intervalles[t−;t+]q de disponibilité de la voie j}
	IloArray<IloArray<IloIntArray> > Ttrack(env, m); // IMPORTANT : espace entre les chevrons -> >' '> 
	for (int j = 0; j < m; j++) {
		Ttrack[j] = IloArray<IloIntArray>(env); // tableau qui va contenir les q creneaux de disponibilité à ajouter au cas par cas puisque chaque voie va avoir des creneaux différents
		// chaque creneau est un tableau de 2 ints 
	}

	//{Couples (j;[t−;t]q) de disponibilité simultanée des rames f et des voies j}
	IloArray<IloArray<IloArray<IloIntArray> > > Tfj(env, nTrain); // IMPORTANT : espace entre les chevrons -> >' '> 
	for (int f = 0; f < nTrain; f++) {
		Tfj[f] = IloArray<IloArray<IloIntArray> >(env,m); // tableau de chaque rame qui comporte l'ensemble des voies
		for (int j = 0; j < m; j++) {
			Tfj[f][j] = IloArray<IloIntArray>(env); //ensemble de couples [t-,t+]1, [t-,t+]2... de compatibilité de la rame f et de la voie j 
		}
	}

	//{Intervalles [t−;t+]q de disponibilité de l’agent a}
	IloArray<IloArray<IloIntArray> > Tagent(env, nAgent); // IMPORTANT : espace entre les chevrons -> >' '> 
	for (int a = 0; a < nAgent; a++) {
		Tagent[a] = IloArray<IloIntArray>(env); // tableau qui va contenir les q creneaux de disponibilité à ajouter au cas par cas puisque chaque agent va avoir des creneaux différents
		// chaque creneau est un tableau de 2 ints 
	}

	// -------------------------- Variables --------------------------------------//

	//Xijt

	//Yi

	//IloBoolVarArray y(env,);


	//Zait

	//Eflt

	//Eflt start

	//Si

	//Ci

	//Ei prev

	//Ti corr
}


void PLNE::print()
{
	cout << "============= instance PLNE  =============  " << endl;
	cout << "== Donnees scalaires == " << endl;
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

	cout << endl << "== Donnees vectorielles == " << endl;
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

	cout << endl << "== Donnees Ensemblistes == " << endl;
	cout << "H : " << H << endl;
	cout << "L : " << L << endl;
	cout << "Oprev : " << Oprev << endl;
	cout << "Ocorr : " << Ocorr << endl;
	cout << "Ttrain : " << Ttrain << endl;
	cout << "Ttrack : " << Ttrack << endl;
	cout << "Tfj : " << Tfj << endl;
	cout << "Tagent : " << Tagent << endl;
}

int PLNE::opY(int f, int indiceRelatifF)
{
	//cout << Ocorr << endl;
	return Ocorr[f][indiceRelatifF];
}
