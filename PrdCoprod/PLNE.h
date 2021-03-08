#pragma once
#include <iostream>
#include <ilcplex/ilocplex.h>
#include <vector>
#include "COperation.h"
#include "CInput.h"

using namespace std;

class PLNE
{
private:

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

	//Durées complètes des opérations i
	IloNumArray p;

	//Durées diagnostiques des opérations i
	IloNumArray pDelta;

	//Possibilité de rejeter ou non les opérations i (booléen)
	IloIntArray r;

	//Dates maximum de début souhaité des opérations i (dates de rentrée souhaitée des rames)
	IloIntArray d;

	//Poids unitaire de retard des opérations i
	IloNumArray w;

	//Poids associé au rejets des opérations i
	IloNumArray u;

	//Besoin de l’opération i en infrastructure k (booléen)
	IloArray<IloBoolArray> NI_ik;

	//Équipement de la voie j en infrastructure k (booléen)
	IloArray<IloBoolArray> IN_jk;

	//Nombre maximum de rentrées de rames sur le site l pendant le créneau h
	IloArray<IloIntArray> rMax_lh;


	//Nombre maximum autorisé de rames en maintenance sur le réseau aux dates t
	IloIntArray rTot;

	//Durée de voyage pour aller de la gare g1 à la gare g2
	// TODO IloNumArray v(env, D);

	//Nombre d'opérations préventives par rame f
	IloIntArray nPrev; //construction d'un tableau de nTrain cases

	//Nombre d'opérations correctives par rame f
	IloIntArray nCorr;

	//Matrice de compatibilité des opérations i et i′(booléen)
	IloArray<IloBoolArray> CO_ii;

	//Nombre d’agents ayant la compétence s requise pour l’opération i
	IloArray<IloIntArray> NS_is;

	//L’agent a dispose de la compétence s sur le site l (booléen)
	IloArray<IloArray<IloBoolArray> > SKL_asl; 

	// -------------------------- definition des ensembles --------------------------------------//

	//{Dates t appartenant au créneau horaire h}
	IloArray<IloIntArray> H;

	//{Voies j appartenant au site l}
	IloArray<IloIntArray> L;

	//{Opérations préventives de la rame f}
	IloArray<IloIntArray> Oprev;
	
	//{Opérations correctives de la rame f}
	IloArray<IloIntArray> Ocorr;

	//{Intervalles[t−;t+]q de disponibilité de la rame f}
	IloArray<IloArray<IloIntArray> > Ttrain;

	//{Intervalles[t−;t+]q de disponibilité de la voie j}
	IloArray<IloArray<IloIntArray> > Ttrack; 

	//{Couples (j;[t−;t]q) de disponibilité simultanée des rames f et des voies j}
	IloArray<IloArray<IloArray<IloIntArray> > > Tfj; 
	
	//{Intervalles [t−;t+]q de disponibilité de l’agent a}
	IloArray<IloArray<IloIntArray> > Tagent;

	// -------------------------- Variables --------------------------------------//

	//Xijt

	//Yi
	IloArray<IloBoolVarArray> Y;

	//IloBoolVarArray y(env,);


	//Zait

	//Eflt

	//Eflt start

	//Si

	//Ci

	//Ei prev

	//Ti corr

	vector<int> operationsPrev;
	vector<int> operationsCorr;

public:

	//PLNE();
	PLNE(CInput input);
	
	static void run();
	void print();
	int opY(int f, int indice); //retourne l'indice de l'opération Of(indice) uniquement correctif
};

