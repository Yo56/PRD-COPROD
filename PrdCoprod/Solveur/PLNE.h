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
	/*! variable d'environnement */
	IloEnv env; 

	/*! variable representant le modele a resoudre (variables, contraintes) */
	IloModel model; 

	/*! variable Cplex */
	IloCplex cplex;

	/*! nombre total d'operations*/
	IloInt n; 

	/*! nombre de voies*/
	IloInt m;

	/*! Horizon de planification (en heures)*/
	IloInt D; 

	/*! nombre de types d'infrastructures*/
	IloInt nInfra;

	/*!  nombre de sites*/
	IloInt nSite; 

	/*! Nombre de creneaux horaires de travail des sites sur l horizon*/
	IloInt nSlot; 

	/*! nombre rames*/
	IloInt nTrain;

	/*! nombre agents*/
	IloInt nAgent;

	/*! nombre competences*/
	IloInt nSkill;

	/*! taux d'avance maximum par rapport a la butee*/
	IloNum alpha; 

	// -------------------------- definition des donnees vectorielles --------------------------------------//

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

	//Duree de voyage pour aller de la gare g1 a la gare g2
	// TODO IloNumArray v(env, D);

	//Nombre d'operations preventives par rame f
	IloIntArray nPrev; //construction d'un tableau de nTrain cases

	//Nombre d'operations correctives par rame f
	IloIntArray nCorr;

	/*! Matrice de compatibilite des operations i et i2 (booleen)*/
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
	*  \param input : donnees d'entree
	*/
	PLNE(CInput input);

	/*!
	 *  \brief Ajout contrainte 1
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte 1 pour gerer l'objectif sur les rejets (epsilon contrainte)
	 *
	 */
	void addContrainte1();

	/*!
	 *  \brief Ajout contrainte 2
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte 2 de calcul de la quantite de retard de chaque operation
	 *
	 */
	void addContrainte2();

	/*!
	 *  \brief Ajout contrainte 3
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte 3 de calcul de la quantite d'avance de chaque operation
	 *
	 */
	void addContrainte3();
	
	/*!
	 *  \brief Ajout contrainte 4
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte de calcul de la date de fin d'operation
	 *
	 */
	void addContrainte4();

	/*!
	 *  \brief Ajout contrainte 5
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte de calcul de la date de debut de chaque operation
	 *
	 */
	void addContrainte5();

	/*!
	 *  \brief Ajout contrainte 6
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte de planification de l'operation si il n'y a pas de diagnostic
	 *
	 */
	void addContrainte6();

	/*!
	 *  \brief Ajout contrainte 7
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte de planifiction de l'operation en cas de diagnostic
	 *
	 */
	void addContrainte7();

	/*!
	 *  \brief Ajout contrainte 8
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte de respect du besoin en infrastructure des opeartions
	 *
	 */
	void addContrainte8();

	/*!
	 *  \brief Ajout contrainte 9
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte de non chevauchement des operations sur les voies (diagnostic)
	 *
	 */
	void addContrainte9();

	/*!
	 *  \brief Ajout contrainte 10
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte complementaire a la contrainte 9 dans le cas ou l'on ne serait pas en diagnostic
	 *
	 */
	void addContrainte10();

	/*!
	 *  \brief Ajout contrainte 11
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte qui restreint le nombre de rames en immobilisation a chaque instant
	 *
	 */
	void addContrainte11();

	/*!
	 *  \brief Ajout contrainte 12
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte qui permet de declarer une rame en maintenance uniquement si au moins une operation est realisee
	 *
	 */
	void addContrainte12();

	/*!
	 *  \brief Ajout contrainte 14
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte du respect du besoin en competences des operations
	 *
	 */
	void addContrainte14();

	/*!
	 *  \brief Ajout contrainte 15
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte assurant que chaque agent fait au plus 1 operation a chaque instant
	 *
	 */
	void addContrainte15();

	/*!
	 *  \brief Ajout contrainte 16
	 *
	 *  Methode qui permet d'ajouter au modele la contrainte de respect des disponibilites des agents
	 *
	 */
	void addContrainte16();

	/*!
	 *  \brief Ajout de toutes les contraintes
	 *
	 *  Methode qui permet d'ajouter l'ensemble des contraintes au modele au appelant les methodes respectives
	 *
	 */
	void addAllContraintes();

	/*!
	 *  \brief Ajout de l'objectif a optimiser 
	 *
	 *  Methode qui permet d'ajouter l'objectif du modele : minimiser la somme ponderee des retards des operations correctives et l'avance ponderee des operations preventives
	 *
	 */
	void addObjectif();


	/*!
	 *  \brief fonction affichage
	 *
	 *  Methode qui permet d'afficher les donnees d une instance CInput
	 *
	 */
	void printInfo();

	/*!
	 *  \brief fonction d'export
	 *
	 *  Methode qui permet d'exporter le modele au format *.lp
	 *
	 *  \param nom : nom du fichier a exporter sans extension
	 */
	void exportationModele(string nom);

	/*!
	 *  \brief fonction de resolution du modele
	 *
	 *  Methode qui permet de lancer la resolution du modele
	 *
	 */
	void solve();

	/*!
	*  \brief fonction interface
	*
	*  permet d obtenir l indice d une operation dans l'ensemble Ocorr a partir de son numero de rame et sa position dans la liste des operations de cette rame
	*
	*  \param f : numero de la rame
	*  \param indice : position relative a f de l'operation dont un souhaite connaitre l'indice
	*  \return la valeur de l'operation dans l'ensemble des operations correctives
	*/
	int opY(int f, int indice); 

/*!
*  \brief fonction interface
*
*  permet d obtenir l'indice d'une operation dans l'ensemble Oprev U Ocorr a partir de son numero de rame et sa position dans la liste des operations de cette rame
*
*  \param f : numero de la rame
*  \param indice : position relative a f de l'operation dont un souhaite connaitre l'indice
*  \return la valeur de l'operation dans l'ensemble des operations correctives ou preventives selon le type de l'operation
*/
	int opX(int f, int indice);

	/*!
	*  \brief fonction interface
	*
	*  permet d'obtenir l'indice general, dans [0;n[, d'une operation corrective a partir de sa position dans la liste des operations correctives d'une rame f : Ocorr(f).
	*
	*  \param f : numero de la rame associee a l'operation
	*  \param i : indice de l'operation dans Ocorr(f)
	*  \return l'indice general de l'operation permettant d'iterer sur les listes dont les operations sont definies sur n.
	*/
	int getIndiceGeneralFromOperationCorrective(int f, int i);

	/*!
	*  \brief fonction interface
	*
	*  permet d'obtenir l'indice general, dans [0;n[, d'une operation preventive a partir de sa position dans la liste des operations preventives d'une rame f : Oprev(f).
	*
	*  \param f : numero de la rame associee a l'operation
	*  \param i : indice de l'operation dans Oprev(f)
	*  \return l'indice general de l'operation permettant d'iterer sur les listes dont les operations sont definies sur n.
	*/
	int getIndiceGeneralFromOperationPreventive(int fParam, int iParam);

	/*!
	*  \brief fonction interface
	*
	*  permet d'obtenir l'indice general, dans [0;n[, d'une operation quelconque a partir de sa position dans la liste des operations d'une rame f : Oprev(f) U Ocorr(f).
	*
	*  \param f : numero de la rame associee a l'operation
	*  \param i : indice de l'operation dans Oprev(f) U Ocorr(f)
	*  \return l'indice general de l'operation permettant d'iterer sur les listes dont les operations sont definies sur n.
	*/
	int getIndiceGeneralFromOperation(int fParam, int iParam);


	//int getIndiceTempsFromValeur(int fParam, int jParam, int creneauParam, int tParam);


	//int getIndiceTempsGeneralFromValeur(int fParam, int jParam, int tParam);


	/*!
	*  \brief fonction interface
	*
	*  permet d obtenir l'indice j d'une voie dans Xijt a partir de sa position dans l'ensemble L
	*
	*  \param lParam : numero du site
	*  \param jParam : numero de la voie du site lParam dont on souhaite connaitre l'indice
	*  \return l'indice de la voie jParam dans Xijt
	*/
	int getIndiceVoieGeneralFromIndiceDansL(int lParam, int jParam);

	/*!
	*  \brief fonction interface
	*
	*  permet d obtenir la disponibilite d'un agent a une heure t donnee
	*
	*  \param agent : numero de l'agent
	*  \param t : heure 
	*  \return true si l'agent est disponible a l'heure t, false sinon 
	*/
	bool agentDisponibleAUnInstant(int agent, int t);
};

