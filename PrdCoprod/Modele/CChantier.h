/*!
 * \file CChantier.h
 * \brief Elements representant un chantier (atelier de maintenance)
 * \author Yohan Nouet
 * \version 1
 */

#pragma once
#include <iostream>
#include <string>
using namespace std;

/*! \class CChantier
   * \brief Classe Chantier (Atelier de maintenance)
   *
   *  La classe permet de creer une instance de chaque site de maintenance constituee des differents attributs permettant son identification.
   * L'objet est cree a partir des donnees recuperees dans les fichiers csv.
   */
class CChantier
{
private:
	int id; /*!< identifiant CPlex*/
	string abreviation; /*!< Abreviation SNCF du nom du site */
	string nom; /*!< Nom du site complet*/
	
public:
	/*!
	*  \brief Constructeur
	*
	*  Constructeur par defaut de la classe CChantier
	*/
	CChantier();

	/*!
	*  \brief Constructeur
	*
	*  Constructeur de la classe CChantier
	*
	*  \param idParam : identifiant representant l'objet dans le modele CPlex
	*  \param abreviationParam : abreviation SNCF du nom du site
	*  \param nomParam : nom complet du site
	*/
	CChantier(int idParam, string abreviationParam, string nomParam);

	/*!
	*  \brief Constructeur
	*
	*  Constructeur de la classe CChantier
	*
	*  \param abreviationParam : abreviation SNCF du nom du site
	*  \param nomParam : nom complet du site
	*/
	CChantier(string abreviationParam, string nomParam);

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe CChantier
	 */
	~CChantier();


	////////////////// GETTERS - SETTERS /////////////////////////

	/*!
	 *  \brief GET identifiant
	 *
	 *  Methode qui permet d'obtenir l'identifiant utilise dans la modelisation CPlex
	 *
	 *  \return l'identifiant (entier)
	 */
	int getId();

	/*!
	 *  \brief SET id
	 *
	 *  Methode qui permet de definir l'identifiant utilise dans la modelisation CPlex
	 *
	 *  \param idParam : l'identifiant a ajouter
	 */
	void setId(int idParam);

	/*!
	 *  \brief GET abreviation
	 *
	 *  Methode qui permet d'obtenir l'abreviation SNCF du nom du site
	 *
	 *  \return l'abreviation (chaine de caracteres)
	 */
	string getAbreviation();

	/*!
	 *  \brief SET abreviation
	 *
	 *  Methode qui permet de definir l'abreviation SNCF du nom du site
	 *
	 *  \param abreviationParam : abreviation
	 */
	void setAbreviation(string abreviationParam);

	/*!
	 *  \brief GET nom
	 *
	 *  Methode qui permet d'obtenir le nom du site complet
	 *
	 *  \return le nom (chaine de caracteres)
	 */
	string getNom();

	/*!
 *  \brief SET nom
 *
 *  Methode qui permet de definir le nom detaille du site de maintenance
 *
 *  \param nomParam : nom complet du site
 */
	void setNom(string nomParam);
};

/*!
 *  \brief Surcharge <<
 *
 *  Methode qui permet de surcharger l'utilisation de l'operateur << pour afficher directement le contenu de l'objet.
 *
 *	Ex : std::cout << monChantier;
 *
 */
ostream &operator<<(std::ostream &out, CChantier &obj);

