/*!
 * \file CJeuDonnees.h
 * \brief Elements permettant d instancier des jeux de donnees pour resoudre des instances avec le solveur
 * \author Yohan Nouet
 * \version 1
 */

#pragma once
#include "CInput.h"

 /*! \class CJeuDonnees
	* \brief Classe JeuDonnees 
	*
	*  La classe permet de creer des jeux de donnes a l aide de methodes statiques retournant une instance CInput
	*/
class CJeuDonnees
{
public:

	/*!
	 *  \brief Generation du jeu de donnee v1
	 *
	 *  Methode statique qui permet d'obtenir un jeu de donnee predefini (vesrsion simple).
	 *
	 *  \return le jeu de donnees
	 */
	static CInput version1();
};

