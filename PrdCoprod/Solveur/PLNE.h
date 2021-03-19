/*!
 * \file PLNE.h
 * \brief Elements permettant de resoudre un probleme d'optimisation
 * \author Yohan Nouet
 * \version 1
 */

#pragma once
#include <iostream>
#include <ilcplex/ilocplex.h>
#include <vector>
//#include "Modele/COperation.h"
#include "../Donnees/CInput.h"

using namespace std;

/*! \class PLNE
   * \brief Classe PLNE
   *
   *  La classe permet de creer une instance de Cplex a partir d un ensemble de donnees representant un probleme d optimisation
   */
class PLNE
{
private:

	IloEnv env; /*! variable d'environnement */
	IloModel model; /*! variable representant le modele a resoudre (variables, contraintes) */
	IloCplex cplex; /*! variable Cplex */

	IloInt n; /*! nombre total d'operations*/
	IloInt m; /*! nombre de voies*/
	IloInt D; /*! Horizon de planification (en heures)*/
	IloInt nInfra; /*! nombre de types d'infrastructures*/
	IloInt nSite; /*!  nombre sites*/
	IloInt nSlot; /*! Nombre de creneaux horaires de travail des sites sur l horizon*/
	IloInt nTrain; /*! nombre rames*/
	IloInt nAgent; /*! nombre agents*/
	IloInt nSkill; /*! nombre competences*/
	IloNum alpha; /*! taux d'avance maximum par rapport a la butee*/

	// -------------------------- definition des données vectorielles --------------------------------------//

	/*! Durees completes des operations i */
	IloIntArray p;

	/*! Durees diagnostiques des operations i */
	IloIntArray pDelta;

	/*! Possibilite de rejeter ou non les operations i (booleen)*/
	IloIntArray r;

	/*! Dates maximum de debut souhaite des operations i (dates de rentree souhaitee des rames) */
	IloIntArray d;

	/*! Poids unitaire de retard des operations i*/
	IloNumArray w;

	/*! Poids associe au rejets des operations i */
	IloNumArray u;

	/*! Besoin de l’operation i en infrastructure k (booleen)*/
	IloArray<IloBoolArray> NI_ik;

	/*! Equipement de la voie j en infrastructure k (booleen)*/
	IloArray<IloBoolArray> IN_jk;

	/*! Nombre maximum de rentrees de rames sur le site l pendant le creneau h*/
	IloArray<IloIntArray> rMax_lh;

	/*! Nombre maximum autorise de rames en maintenance sur le reseau aux dates t*/
	IloIntArray rTot;

	//Durée de voyage pour aller de la gare g1 à la gare g2
	// TODO IloNumArray v(env, D);

	//Nombre d'opérations préventives par rame f
	IloIntArray nPrev; //construction d'un tableau de nTrain cases

	//Nombre d'opérations correctives par rame f
	IloIntArray nCorr;

	/*! Matrice de compatibilité des opérations i et i2 (booleen)*/
	IloArray<IloBoolArray> CO_ii;

	/*! Nombre d’agents ayant la competence s requise pour l’operation i*/
	IloArray<IloIntArray> NS_is;

	/*! L’agent a dispose de la competence s sur le site l (booleen)*/
	IloArray<IloArray<IloBoolArray> > SKL_asl; 

	// -------------------------- definition des ensembles --------------------------------------//

	/*! {Dates t appartenant au creneau horaire h}*/
	IloArray<IloIntArray> H;

	/*! {Voies j appartenant au site l} */
	IloArray<IloIntArray> L;

	/*! {Operations preventives de la rame f}*/
	IloArray<IloIntArray> Oprev;
	
	/*! {Operations correctives de la rame f}*/
	IloArray<IloIntArray> Ocorr;

	/*! {Intervalles[t−;t+]q de disponibilite de la rame f} */
	IloArray<IloArray<IloIntArray> > Ttrain;

	/*! {Intervalles[t−;t+]q de disponibilite de la voie j}*/
	IloArray<IloArray<IloIntArray> > Ttrack; 

	/*! {Couples (j;[t−;t]q) de disponibilite simultanee des rames f et des voies j}*/
	IloArray<IloArray<IloArray<IloIntArray> > > Tfj; 
	
	/*! {Intervalles [t−;t+]q de disponibilite de l’agent a}*/
	IloArray<IloArray<IloIntArray> > Tagent;

	// -------------------------- Variables --------------------------------------//

	/*! Variable X(f)ijt */
	IloArray< IloArray< IloArray<IloBoolVarArray> > > X;

	/*! Variable Y(f)i */
	IloArray<IloBoolVarArray> Y;

	/*! Variable Za(f)it */
	IloArray< IloArray< IloArray<IloBoolVarArray> > > Z;

	/*! Variable Eflt */
	IloArray< IloArray<IloBoolVarArray> > E;

	/*! Variable Efl start */
	IloArray<IloBoolVarArray> Estart;

	/*! Variable S(f)i */
	IloArray<IloIntVarArray> S;

	/*! Variable C(f)i */
	IloArray<IloIntVarArray> C;

	/*! Variable E(f)i prev */
	IloArray<IloIntVarArray> Eprev;

	/*! Variable T(f)i corr */
	IloArray<IloIntVarArray> Tcorr;

	//vector<int> operationsPrev; 
	//vector<int> operationsCorr; 

public:

	/*!
	*  \brief Constructeur
	*
	*  Constructeur de la classe PLNE. La fonction prepare l ensemble des donnees Cplex, les variables, les contraintes, en vue de la resolution
	*
	*  \param input : donnees d entree
	*/
	PLNE(CInput input);

	void addContrainte1();

	void addContrainte2();

	void addContrainte3();
	
	void addContrainte4();

	void addContrainte5();

	void addContrainte6();

	void addAllContraintes();


	/*!
	 *  \brief fonction affichage
	 *
	 *  Methode qui permet d'afficher les donnees d une instance CInput
	 *
	 */
	void printInfo();

	/*!
	*  \brief fonction interface
	*
	*  permet d obtenir l indice d une operation dans l'ensemble Ocorr à partir de son numero de rame et sa position dans la liste des operations de cette rame
	*
	*  \param f : numero de la rame
	*  \param indice : position relative à f de l'operation dont un souhaite connaitre l'indice
	*  \return la valeur de l'operation dans l'ensemble des operations correctives
	*/
	int opY(int f, int indice); 

	/*!
*  \brief fonction interface
*
*  permet d obtenir l'indice d'une operation dans l'ensemble Oprev U Ocorr à partir de son numero de rame et sa position dans la liste des operations de cette rame
*
*  \param f : numero de la rame
*  \param indice : position relative à f de l'operation dont un souhaite connaitre l'indice
*  \return la valeur de l'operation dans l'ensemble des operations correctives ou préventives selon le type de l'operation
*/
	int opX(int f, int indice);


	int getIndiceGeneralFromOperationCorrective(int f, int i);

	int getIndiceGeneralFromOperationPreventive(int fParam, int iParam);

	int getIndiceGeneralFromOperation(int fParam, int iParam);

	int getIndiceTempsFromValeur(int fParam, int jParam, int creneauParam, int tParam);

	


};

