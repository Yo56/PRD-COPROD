/*!
 * \file CAcquisition.h
 * \brief 
 * \author Yohan Nouet
 * \version 1
 */

#pragma once
#include <vector>
#include "CChantier.h"
using namespace std;

/*! \class CAcquisition
   * \brief Classe Aqcuisition 
   *
   *  La classe permet de recuperer les donnees a partir des differents fichiers de donnees *.csv
   * Une methode statique est definie pour format de donnee
   */
class CAcquisition
{
public:

	/*!
	 *  \brief Parseur Chantiers (sites de maintenance)
	 *
	 *  Methode statique qui permet de construire la liste des chantiers a partir du fichiers csv
	 *
	 *  \param path : chemin d'acces au fichier
	 *	\return la liste des objets chantiers
	 */
	static vector<CChantier> chantiers(string path);

};

