/*!
 * \file Cinput.h
 * \brief Elements permettant de fournir les donnees d'entrees a un modele de résolution
 * \author Yohan Nouet
 * \version 1
 */

#pragma once
#include <iostream>
#include <vector>

using namespace std;

/*! \class CInput
   * \brief Classe Input
   *
   *  La classe permet de creer une instance regroupant les donnees en vue de la resolution par le solveur.
   */
class CInput
{
private:
	int n; /*! nombre total d'operations*/
	int m; /*! nombre de voies*/
	int D; /*! Horizon de planification (en heures)*/
	int nInfra; /*! nombre de types d'infrastructures*/
	int nSite; /*!  nombre sites*/
	int nSlot; /*! Nombre de creneaux horaires de travail des sites sur l horizon*/
	int nTrain; /*! nombre rames*/
	int nAgent; /*! nombre agents*/
	int nSkill; /*! nombre competences*/
	double alpha; /*! taux d'avance maximum par rapport a la butee*/

	vector<double> p; /*! Durees completes des operations i */
	vector<double> pDelta; /*! Durees diagnostiques des operations i */
	vector<int> r; /*! Possibilite de rejeter ou non les operations i (booleen)*/
	vector<int> d; /*! Dates maximum de debut souhaite des operations i (dates de rentree souhaitee des rames) */
	vector<double> w; /*! Poids unitaire de retard des operations i*/
	vector<double> u; /*! Poids associe au rejets des operations i */

	vector <vector<int> > NI_ik; /*! Besoin de l’operation i en infrastructure k (booleen)*/
	vector <vector<int> > IN_jk; /*! Equipement de la voie j en infrastructure k (booleen)*/
	vector <vector<int> > rMax_lh; /*! Nombre maximum de rentrees de rames sur le site l pendant le creneau h*/
	vector <int> rTot; /*! Nombre maximum autorise de rames en maintenance sur le reseau aux dates t*/
	vector <vector<int> > CO_ii; /*! Matrice de compatibilité des opérations i et i2 (booleen)*/
	vector <vector<int> > NS_is; /*! Nombre d’agents ayant la competence s requise pour l’operation i*/
	vector <vector <vector<int> > > SKL_asl; /*! L’agent a dispose de la competence s sur le site l (booleen)*/

	vector <vector<int> > H; /*! {Dates t appartenant au creneau horaire h}*/
	vector <vector<int> > L; /*! {Voies j appartenant au site l} */

	vector <vector<int> > Oprev; /*! {Operations preventives de la rame f}*/
	vector <vector<int> > Ocorr; /*! {Operations correctives de la rame f}*/

	vector <vector <vector<int> > > Ttrain; /*! {Intervalles[t−;t+]q de disponibilite de la rame f} */
	vector <vector <vector<int> > > Ttrack; /*! {Intervalles[t−;t+]q de disponibilite de la voie j}*/
	vector < vector <vector <vector<int> > > > Tfj; /*! {Couples (j;[t−;t]q) de disponibilite simultanee des rames f et des voies j}*/
	vector <vector <vector<int> > > Tagent; /*! {Intervalles [t−;t+]q de disponibilite de l’agent a}*/

public:
	
	/*!
	*  \brief Constructeur
	*
	*  Constructeur de la classe CInput
	*
	*  Tous les parametres sont requis et representent les differentes donnees necessaire a la resolution du modele
	*/
	CInput(int n, int m, int D, int nInfra, int nSite, int nSlot, int nTrain, int nAgent, int nSkill, double alpha,
		std::vector<double> p, std::vector<double> pDelta, std::vector<int> r, std::vector<int> d, std::vector<double> w, std::vector<double> u,
		vector <vector<int> > NI_ik, vector <vector<int> > IN_jk, vector <vector<int> > rMax_lh, vector<int> rTot, vector <vector<int> > CO_ii,
		vector <vector<int> >NS_is, vector <vector <vector<int> > > SKL_asl, vector <vector<int> > H, vector <vector<int> > L, vector <vector<int> > Oprev,
		vector <vector<int> > Ocorr, vector <vector <vector<int> > > Ttrain, vector <vector <vector<int> > > Ttrack, vector < vector <vector <vector<int> > > > Tfj,
		vector <vector <vector<int> > > Tagent);

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe CInput
	 */
	~CInput();

	/*!
	 *  \brief fonction affichage
	 *
	 *  Methode qui permet d'afficher les donnees d une instance CInput
	 *  
	 */
	void print();

	// GETTERS and SETTERS

	int getN();
	int getM();
	int getD();
	int getNInfra();
	int getNSite();
	int getNSlot();
	int getNTrain();
	int getNAgent();
	int getNSkill();
	double getAlpha();
	vector<double> getP();
	vector<double> getPDelta();
	vector<int> getR();
	vector<int> getDateDeRentree();
	vector<double> getW();
	vector<double> getU();
	vector <vector<int> > getNI_ik();
	vector <vector<int> > getIN_jk();
	vector <vector<int> > getRMax_lh();
	vector<int> getRTot();
	vector <vector<int> > getCO_ii();
	vector <vector<int> >getNS_is();
	vector <vector <vector<int> > > getSKL_asl();
	vector <vector<int> > getH();
	vector <vector<int> > getL();
	vector <vector<int> > getOprev();
	vector <vector<int> > getOcorr();
	vector <vector <vector<int> > > getTtrain();
	vector <vector <vector<int> > > getTtrack();
	vector < vector <vector <vector<int> > > > getTfj();
	vector <vector <vector<int> > > getTagent();

	void setN(int i);
	void setM(int i);
	void setD(int i);
	void setNInfra(int i);
	void setNSite(int i);
	void setNSlot(int i);
	void setNTrain(int i);
	void setNAgent(int i);
	void setNSkill(int i);
	void setAlpha(double i);
};


