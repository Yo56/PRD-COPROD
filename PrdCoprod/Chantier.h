#pragma once
#include <iostream>
#include <string>
using namespace std;

class Chantier
{
private:
	int id;
	string abreviation;
	string nom;
	
public:
	Chantier();
	Chantier(int idParam, string abreviationParam, string nomParam);
	Chantier(string abreviationParam, string nomParam);
	~Chantier();

	int getId();
	void setId(int idParam);
	string getAbreviation();
	void setAbreviation(string abreviationParam);
	string getNom();
	void setNom(string nomParam);
};

ostream &operator<<(std::ostream &out, Chantier &obj);

