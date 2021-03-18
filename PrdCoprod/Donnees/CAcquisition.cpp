/*!
 * \file CAcquisition.cpp
 * \brief Aquisition des differentes sources de donnees
 * \author Yohan Nouet
 * \version 1
 */

#include "CAcquisition.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <xlnt/xlnt.hpp>
#include "../rapidcsv.h"

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
	// 2e colonne = libelle SR
	vector<string> col2 = doc.GetColumn<string>(1);
	// 3e colonne = SR Long
	vector<string> col3 = doc.GetColumn<string>(2);

	cout << "Lecture de  " << col1.size() << " lignes a partir du fichier : "<< path  << endl;
	cout << "Acquisition : ";

	//creation des objets Chantier
	for (int i = 0; i < col1.size(); i++)
	{
		string SR = col1[i];
		string libelleSR = col2[i];
		string SRLong = col3[i];

		CChantier chantier(SR, libelleSR);
		
		listeChantiers.push_back(chantier);
		/*myfile << SR <<" | " << libelleSR << " | " << SRLong << " | " << endl;*/
	}

	/*myfile.close();*/
	cout << "OK" << endl;
	return listeChantiers;
}

vector<COperation> CAcquisition::operations(string path)
{
	rapidcsv::Document doc(path, rapidcsv::LabelParams(0, -1), rapidcsv::SeparatorParams(';'));
	vector<COperation> listeOperations;

	// NOMS DES COLONNES
	vector<string> nomsColonnes = doc.GetColumnNames(); // not used

	// 1ère colonne = Id Op. Ref
	vector<int> col0 = doc.GetColumn<int>(0);
	// 2e colonne = Operation Ref
	vector<string> col1 = doc.GetColumn<string>(1);
	// 3e colonne = Description Op. Ref
	vector<string> col2 = doc.GetColumn<string>(2);
	// 4e colonne = Version PMS Op.Ref
	vector<string> col3 = doc.GetColumn<string>(3);
	// 5e colonne = Version PMS en cours
	vector<string> col4 = doc.GetColumn<string>(4); 
	// 6e colonne = Type d'Operation Part/Service
	vector<string> col5 = doc.GetColumn<string>(5); 
	// 7e colonne = Cycle
	vector<string> col6 = doc.GetColumn<string>(6);
	// 8e colonne = STF / Ope. Part.
	vector<string> col7 = doc.GetColumn<string>(7);
	// 9e colonne = Statut Op. Ref
	vector<string> col8 = doc.GetColumn<string>(8);
	// 10e colonne = LCN Racine Op. Ref
	vector<string> col9 = doc.GetColumn<string>(9);
	// 11e colonne = LCN Article Op. Ref
	vector<string> col10 = doc.GetColumn<string>(10);
	// 12e colonne = Reference document Maintenance
	vector<string> col11 = doc.GetColumn<string>(11);
	// 13e colonne = Rang
	vector<int> col12 = doc.GetColumn<int>(12);
	// 14e colonne = Date debut applicabilite Op. Ref
	vector<string> col13 = doc.GetColumn<string>(13);
	// 15e colonne =  Date fin applicabilite Op. Ref
	vector<string> col14 = doc.GetColumn<string>(14);
	// 16e colonne = SEF
	vector<string> col15 = doc.GetColumn<string>(15);
	// 17e colonne = Cadence Op. Ref
	vector<string> col16 = doc.GetColumn<string>(16);
	// 18e colonne =  Type Op. Ref
	vector<string> col17 = doc.GetColumn<string>(17);
	// 19e colonne = Libelle Type Op. Ref
	vector<string> col18 = doc.GetColumn<string>(18);
	// 20e colonne = Nb Referentiels Applicables
	vector<int> col19 = doc.GetColumn<int>(19);
	// 21e colonne = Declinaison MR
	vector<string> col20 = doc.GetColumn<string>(20);

	cout << "Lecture de  " << col0.size() << " lignes a partir du fichier : " << path << endl;
	cout << "Acquisition : ";
	//creation des objets COperation
	for (int i = 0; i < col1.size(); i++)
	{
		COperation operation;

		operation.setIdReference(col0[i]);
		operation.setRefOperation(col1[i]);
		operation.setDescOperation(col2[i]);
		operation.setVersionPMS(col3[i]);

		bool versionPMSEnCours = false;
		if (col4[i].compare("N") != 0) { //"N" => false, "O" => true
			versionPMSEnCours = true;
		}
		operation.setVersionPMSEnCours(versionPMSEnCours);
		operation.setTypeOperationPartService(col5[i]);
		operation.setCycle(col6[i]);
		operation.setStfOpePart(col7[i]);
		operation.setStatutOpeRef(col8[i]);
		operation.setLcnRacine(col9[i]);
		operation.setLcnArticle(col10[i]);
		operation.setRefDocMaintenance(col11[i]);
		operation.setRang(col12[i]);
		operation.setDateDebutApplicabilite(col13[i]);
		operation.setDateFinApplicabilite(col14[i]);
		operation.setSEF(col15[i]);
		operation.setCadence(col16[i]);
		operation.setTypeOperation(col17[i]);
		operation.setLibelleTypeOperation(col18[i]);
		operation.setNbReferentielsApplicables(col19[i]);
		operation.setDeclinaisonMR(col20[i]);
		
		//cout << operation << endl;
		listeOperations.push_back(operation);
	}

	cout << "OK" << endl;

	return listeOperations;
}
