#include "PLNE2.h"

IloEnv env; //variable d'environnement

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

// -------------------------- definition des données vectorielles --------------------------------------//
//
////Durées complètes des opérations i
//IloIntArray p(env, n);
//
////Durées diagnostiques des opérations i
//IloIntArray pDelta(env, n);
//
////Possibilité de rejeter ou non les opérations i (booléen)
//IloIntArray r(env, n);
//
////Dates maximum de début souhaité des opérations i (dates de rentrée souhaitée des rames)
//IloIntArray d(env, n);
//
////Poids unitaire de retard des opérations i
//IloIntArray w(env, n);
//
////Poids associé au rejets des opérations i
//IloIntArray u(env, n);
//
////Besoin de l’opération i en infrastructure k (booléen)
//IloArray<IloBoolArray> NI_ik(env, n);
//
////Équipement de la voie j en infrastructure k (booléen)
//IloArray<IloBoolArray> IN_jk(env, m);
//
////Nombre maximum de rentrées de rames sur le site l pendant le créneau h
//IloArray<IloIntArray> rMax_lh(env, nSite);
//
////Nombre maximum autorisé de rames en maintenance sur le réseau aux dates t
//IloIntArray rTot(env, D);
//
////Durée de voyage pour aller de la gare g1 à la gare g2
//// TODO IloNumArray v(env, D);
//
////Nombre d'opérations préventives par rame f
//IloIntArray nPrev(env, nTrain); //construction d'un tableau de nTrain cases
//
////Nombre d'opérations correctives par rame f
//IloIntArray nCorr(env, nTrain);
//
////Matrice de compatibilité des opérations i et i′(booléen)
//IloArray<IloBoolArray> CO_ii(env, n);
//
////Nombre d’agents ayant la compétence s requise pour l’opération i
//IloArray<IloIntArray> NS_is(env, n);
//
////L’agent a dispose de la compétence s sur le site l (booléen)
//IloArray<IloArray<IloBoolArray> > SKL_asl(env, nAgent); 
//
//// -------------------------- definition des ensembles --------------------------------------//
//
////{Dates t appartenant au créneau horaire h}
//IloArray<IloIntArray> H(env, nSlot);
//
////{Voies j appartenant au site l}
//IloArray<IloIntArray> L(env, nSite);
//
////{Opérations préventives de la rame f}
//IloArray<IloIntArray> Oprev(env, nTrain);

//{Opérations correctives de la rame f}
IloArray<IloIntArray> Ocorr(env,8);

////{Intervalles[t−;t+]q de disponibilité de la rame f}
//IloArray<IloArray<IloIntArray> > Ttrain(env, nTrain);
//
////{Intervalles[t−;t+]q de disponibilité de la voie j}
//IloArray<IloArray<IloIntArray> > Ttrack(env, m);
//
////{Couples (j;[t−;t]q) de disponibilité simultanée des rames f et des voies j}
//IloArray<IloArray<IloArray<IloIntArray> > > Tfj(env, nTrain);
//
////{Intervalles [t−;t+]q de disponibilité de l’agent a}
//IloArray<IloArray<IloIntArray> > Tagent(env, nAgent);

PLNE2::PLNE2()
{
	int toto = 0;

	n = 6; // nombre total d'opérations
	m = 5; // nombre de voies
	D = 24; // Horizon de planification (en heures)
	nInfra = 3; // nb de types d'infrastructures
	nSite = 1; // nb sites
	nSlot = 3; // Nombre de créneaux horaires de travail des sites sur l’horizon
	nTrain = 2; // nb rames
	nAgent = 8; // nb agents
	nSkill = 5;// nb compétences
	alpha = 0.10; //taux d'avance maximum par rapport à la butée

	cout << "Step " + toto << endl;
	toto++;
	// -------------------------- definition des données vectorielles --------------------------------------//
	////Besoin de l’opération i en infrastructure k (booléen)
	//for (int i = 0; i < n; i++) {
	//	NI_ik[i] = IloBoolArray(env, nInfra);
	//}

	////Équipement de la voie j en infrastructure k (booléen)
	//for (int j = 0; j < m; j++) {
	//	IN_jk[j] = IloBoolArray(env, nInfra);
	//}

	////Nombre maximum de rentrées de rames sur le site l pendant le créneau h
	//for (int l = 0; l < nSite; l++) {
	//	rMax_lh[l] = IloIntArray(env, nSlot);
	//}

	////Nombre maximum autorisé de rames en maintenance sur le réseau aux dates t

	////Durée de voyage pour aller de la gare g1 à la gare g2
	//// TODO IloNumArray v(env, D);

	////Nombre d'opérations préventives par rame f

	////Nombre d'opérations correctives par rame f

	////Matrice de compatibilité des opérations i et i′(booléen)
	//for (int i = 0; i < n; i++) {
	//	CO_ii[i] = IloBoolArray(env, n);
	//}

	////Nombre d’agents ayant la compétence s requise pour l’opération i
	//for (int i = 0; i < n; i++) {
	//	NS_is[i] = IloIntArray(env, nSkill);
	//}

	////L’agent a dispose de la compétence s sur le site l (booléen)
	//for (int a = 0; a < nAgent; a++) {
	//	SKL_asl[a] = IloArray<IloBoolArray>(env, nSkill);
	//	for (int s = 0; s < nSkill; s++) {
	//		SKL_asl[a][s] = IloBoolArray(env, nSite);
	//	}
	//}
	//cout << "Step " + toto << endl;
	//toto++;
	//// -------------------------- definition des ensembles --------------------------------------//

	////{Dates t appartenant au créneau horaire h}
	//for (int h = 0; h < nSlot; h++) {
	//	H[h] = IloIntArray(env); //taille variable pour chaque H[h]
	//}

	////{Voies j appartenant au site l}
	//for (int l = 0; l < nSite; l++) {
	//	L[l] = IloIntArray(env); //taille variable pour chaque L[l]
	//}

	////{Opérations préventives de la rame f}
	//for (int f = 0; f < nTrain; f++) {
	//	Oprev[f] = IloIntArray(env); //taille variable pour chaque Oprev[f]
	//}
	//{Opérations correctives de la rame f}
	IloArray<IloIntArray> Ocorr(env, nTrain);
	for (int f = 0; f < nTrain; f++) {
		Ocorr[f] = IloIntArray(env); //taille variable pour chaque Ocorr[f] //ici chaque rame necessite 3 operations
	}
	//ajoute des valeurs
	Ocorr[0].add(4);
	Ocorr[0].add(7);
	Ocorr[0].add(8);
	Ocorr[0].add(9);
	Ocorr[1].add(5);
	Ocorr[1].add(2);

	////{Intervalles[t−;t+]q de disponibilité de la rame f}
	//for (int f = 0; f < nTrain; f++) {
	//	Ttrain[f] = IloArray<IloIntArray>(env); // tableau qui va contenir les q creneaux de disponibilité à ajouter au cas par cas puisque chaque rame va avoir des creneaux différents
	//	// chaque creneau est un tableau de 2 ints 
	//}
	//
	////{Intervalles[t−;t+]q de disponibilité de la voie j}
	//for (int j = 0; j < m; j++) {
	//	Ttrack[j] = IloArray<IloIntArray>(env); // tableau qui va contenir les q creneaux de disponibilité à ajouter au cas par cas puisque chaque voie va avoir des creneaux différents
	//	// chaque creneau est un tableau de 2 ints 
	//}
	
	////{Couples (j;[t−;t]q) de disponibilité simultanée des rames f et des voies j}
	//for (int f = 0; f < nTrain; f++) {
	//	Tfj[f] = IloArray<IloArray<IloIntArray> >(env, m); // tableau de chaque rame qui comporte l'ensemble des voies
	//	for (int j = 0; j < m; j++) {
	//		Tfj[f][j] = IloArray<IloIntArray>(env); //ensemble de couples [t-,t+]1, [t-,t+]2... de compatibilité de la rame f et de la voie j 
	//	}
	//}

	////{Intervalles [t−;t+]q de disponibilité de l’agent a}
	//for (int a = 0; a < nAgent; a++) {
	//	Tagent[a] = IloArray<IloIntArray>(env); // tableau qui va contenir les q creneaux de disponibilité à ajouter au cas par cas puisque chaque agent va avoir des creneaux différents
	//	// chaque creneau est un tableau de 2 ints 
	//}
	//cout << "Step " + toto << endl;
	//toto++;
}

void PLNE2::print() {
}

int PLNE2::opY(int f, int indiceRelatifF)
{
	cout << Ocorr << endl;
	return Ocorr[f][indiceRelatifF];
}

PLNE2::~PLNE2()
{
}
