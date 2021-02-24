#include "CAcquisition.h"
#include <vector>
#include "CChantier.h"
#include <iostream>
#include <fstream>
#include <xlnt/xlnt.hpp>
#include "rapidcsv.h"

using namespace std;


vector<CChantier> CAcquisition::chantiers(string path)
{
	rapidcsv::Document doc(path, rapidcsv::LabelParams(0, -1), rapidcsv::SeparatorParams(';'));
	vector<CChantier> listeChantiers;
	
	// NOMS DES COLONNES
	vector<string> nomsColonnes = doc.GetColumnNames(); // not used
	
	//ofstream myfile;
	//myfile.open("example.txt");
	//myfile << "=== COLONNES (" << nomsColonnes.size() <<") ===" << endl;

	// 1ère colonne = SR
	vector<string> col1 = doc.GetColumn<string>(0);
	// 2e colonne = libellé SR
	vector<string> col2 = doc.GetColumn<string>(1);
	// 3e colonne = SR Long
	vector<string> col3 = doc.GetColumn<string>(2);

	cout << "Lecture de  " << col1.size() << " lignes a partir du fichier : "<< path  << endl;

	//création des objets Chantier
	for (int i = 0; i < col1.size(); i++)
	{
		string SR = col1[i];
		string libelleSR = col2[i];
		string SRLong = col3[i];

		CChantier chantier(SR, libelleSR);
		cout << chantier << endl;
		listeChantiers.push_back(chantier);
		/*myfile << SR <<" | " << libelleSR << " | " << SRLong << " | " << endl;*/
	}

	/*myfile.close();*/

	return listeChantiers;
}
