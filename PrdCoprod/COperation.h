/*!
 * \file COperation.h
 * \brief manipulation d'une operation de maintenance
 * \author Yohan Nouet
 * \version 1
 */
#pragma once
#include <iostream>
#include <string>
using namespace std;

 /*! \class COperation
	* \brief Classe Operation de maintenance
	*
	*  La classe permet de creer une instance de chaque operation de maintenance (quelle soit preventive ou corrective) constituee des differents attributs permettant son identification.
	* L'objet est cree a partir des donnees récuperees dans les fichiers csv.
	*/
class COperation
{
private:
	int idCplex;					/*!< identifiant CPlex*/
	int idReference;				/*!< champ fichier csv : Id Op. Ref*/
	string refOperation;			/*!< champ fichier csv : Opération Ref*/
	string descOperation;			/*!< champ fichier csv : Description Op. Ref*/
	string versionPMS;				/*!< champ fichier csv : Version PMS Op.Ref */
	bool versionPMSEnCours;			/*!< champ fichier csv : Version PMS en cours*/
	string typeOperationPartService;/*!< champ fichier csv : Type d'Operation Part/Service */
	string cycle;					/*!< champ fichier csv : Cycle */		// peut être transformer en enumeration MODULAIRE REVISION CORRECTIF...
	string stfOpePart;				/*!< champ fichier csv : STF / Ope. Part.*/
	string statutOpeRef;			/*!< champ fichier csv : Statut Op. Ref*/
	string lcnRacine;				/*!< champ fichier csv : LCN Racine Op. Ref*/
	string lcnArticle;				/*!< champ fichier csv : LCN Article Op. Ref */
	string refDocMaintenance;		/*!< champ fichier csv : Reference document Maintenance*/
	int rang;						/*!< champ fichier csv : Rang */
	string dateDebutApplicabilite;	/*!< champ fichier csv : Date debut applicabilité Op. Ref */		//TODO changer pour un type date
	string dateFinApplicabilite;	/*!< champ fichier csv : Date fin applicabilité Op. Ref */		//TODO changer pour un type date
	string sef;						/*!< champ fichier csv : SEF */
	string cadence;					/*!< champ fichier csv : Cadence Op. Ref */
	string typeOperation;			/*!< champ fichier csv : Type Op. Ref */
	string libelleTypeOperation;	/*!< champ fichier csv : Libelle Type Op. Ref */
	int nbReferentielsApplicables;	/*!< champ fichier csv : Nb Referentiels Applicables */
	string declinaisonMR;			/*!< champ fichier csv : Declinaison MR */


public:

	/*!
	*  \brief Constructeur
	*
	*  Constructeur par defaut de la classe COperation
	*/
	COperation();


	/*!
	*  \brief Destructeur
	*
	*  Destructeur de la classe CChantier
	*/
	~COperation();

	//////////// GETTERS AND SETTERS ///////////////////

	int getIdCplex();
	void setIdCplex(int idParam);

	int getIdReference();
	void setIdReference(int idParam);

	string getRefOperation();
	void setRefOperation(string str);

	string getDescOperation();
	void setDescOperation(string str);

	string getVersionPMS();
	void setVersionPMS(string str);

	bool getVersionPMSEnCours();
	void setVersionPMSEnCours(bool param);

	string getTypeOperationPartService();
	void setTypeOperationPartService(string str);

	string getCycle();
	void setCycle(string str);

	string getStfOpePart();
	void setStfOpePart(string str);

	string getStatutOpeRef();
	void setStatutOpeRef(string str);

	string getLcnRacine();
	void setLcnRacine(string str);

	string getLcnArticle();
	void setLcnArticle(string str);

	string getRefDocMaintenance();
	void setRefDocMaintenance(string str);

	int getRang();
	void setRang(int idParam);

	string getDateDebutApplicabilite();
	void setDateDebutApplicabilite(string str);

	string getDateFinApplicabilite();
	void setDateFinApplicabilite(string str);

	string getSEF();
	void setSEF(string str);

	string getCadence();
	void setCadence(string str);

	string getTypeOperation();
	void setTypeOperation(string str);

	string getLibelleTypeOperation();
	void setLibelleTypeOperation(string str);

	int getNbReferentielsApplicables();
	void setNbReferentielsApplicables(int i);

	string getDeclinaisonMR();
	void setDeclinaisonMR(string str);


};

/*!
*  \brief Surcharge <<
*
*  Methode qui permet de surcharger l'utilisation de l'operateur << pour afficher directement le contenu de l'objet.
*
*	Ex : std::cout << monOperation;
*
*/
ostream &operator<<(std::ostream &out, COperation &obj);