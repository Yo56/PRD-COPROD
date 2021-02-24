#include "CChantier.h"


//Constructeur par défaut
CChantier::CChantier()
{
}

CChantier::CChantier(int idParam, string abreviationParam, string nomParam)
{
	id = idParam;
	abreviation = abreviationParam;
	nom = nomParam;
}

CChantier::CChantier( string abreviationParam, string nomParam)
{
	id = -1; //doit être modifié par la suite
	abreviation = abreviationParam;
	nom = nomParam;
}


CChantier::~CChantier()
{
}

////////// GETTERS & SETTERS  /////////////

int CChantier::getId()
{
	return id;
}

void CChantier::setId(int idParam)
{
	id = idParam;
}

string CChantier::getAbreviation()
{
	return abreviation;
}

void CChantier::setAbreviation(string abreviationParam)
{
	abreviation = abreviationParam;
}

string CChantier::getNom()
{
	return nom;
}

void CChantier::setNom(string nomParam)
{
	nom = nomParam;
}

ostream & operator<<(std::ostream & out, CChantier & obj)
{
	out << "Chantier : " << obj.getId() << " - " << obj.getAbreviation() << " - " << obj.getNom();
	return out;
}
