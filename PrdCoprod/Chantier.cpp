#include "Chantier.h"


//Constructeur par défaut
Chantier::Chantier()
{
}

Chantier::Chantier(int idParam, string abreviationParam, string nomParam)
{
	id = idParam;
	abreviation = abreviationParam;
	nom = nomParam;
}

Chantier::Chantier( string abreviationParam, string nomParam)
{
	id = -1; //doit être modifié par la suite
	abreviation = abreviationParam;
	nom = nomParam;
}


Chantier::~Chantier()
{
}

////////// GETTERS & SETTERS  /////////////

int Chantier::getId()
{
	return id;
}

void Chantier::setId(int idParam)
{
	id = idParam;
}

string Chantier::getAbreviation()
{
	return abreviation;
}

void Chantier::setAbreviation(string abreviationParam)
{
	abreviation = abreviationParam;
}

string Chantier::getNom()
{
	return nom;
}

void Chantier::setNom(string nomParam)
{
	nom = nomParam;
}

ostream & operator<<(std::ostream & out, Chantier & obj)
{
	out << "Chantier : " << obj.getId() << " - " << obj.getAbreviation() << " - " << obj.getNom();
	return out;
}
