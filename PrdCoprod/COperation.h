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
	int idCplex;
	int idReference;
	string refOperation;
	string descOperation;
	string versionPMS;
	bool versionPMSEnCours;
	string typeOperation;
	string cycle; // peut être transformer en enumeration MODULAIRE REVISION CORRECTIF...
	string STFOpePart;
	string statutOpeRef;
	string LCNRacine;
	string LCNArticle;
	string refDocMaintenance;
	int rang;
	string





public:
	COperation();
	~COperation();
};

