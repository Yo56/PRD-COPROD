#include "COperation.h"



COperation::COperation()
{
}


COperation::~COperation()
{
}

int COperation::getIdCplex()
{
	return idCplex;
}

void COperation::setIdCplex(int idParam)
{
	idCplex = idParam;
}

int COperation::getIdReference()
{
	return idReference;
}

void COperation::setIdReference(int idParam)
{
	idReference = idParam;
}

string COperation::getRefOperation()
{
	return refOperation;
}

void COperation::setRefOperation(string str)
{
	refOperation = str;
}

string COperation::getDescOperation()
{
	return descOperation;
}

void COperation::setDescOperation(string str)
{
	descOperation = str;
}

string COperation::getVersionPMS()
{
	return versionPMS;
}

void COperation::setVersionPMS(string str)
{
	versionPMS = str;
}

bool COperation::getVersionPMSEnCours()
{
	return versionPMSEnCours;
}

void COperation::setVersionPMSEnCours(bool param)
{
	versionPMSEnCours = param;
}

string COperation::getTypeOperationPartService()
{
	return typeOperationPartService;
}

void COperation::setTypeOperationPartService(string str)
{
	typeOperationPartService = str;
}

string COperation::getCycle()
{
	return cycle;
}

void COperation::setCycle(string str)
{
	cycle = str;
}

string COperation::getStfOpePart()
{
	return stfOpePart;
}

void COperation::setStfOpePart(string str)
{
	stfOpePart = str;
}

string COperation::getStatutOpeRef()
{
	return statutOpeRef;
}

void COperation::setStatutOpeRef(string str)
{
	statutOpeRef = str;
}

string COperation::getLcnRacine()
{
	return lcnRacine;
}

void COperation::setLcnRacine(string str)
{
	lcnRacine = str;
}

string COperation::getLcnArticle()
{
	return lcnArticle;
}

void COperation::setLcnArticle(string str)
{
	lcnArticle = str;
}

string COperation::getRefDocMaintenance()
{
	return refDocMaintenance;
}

void COperation::setRefDocMaintenance(string str)
{
	refDocMaintenance = str;
}

int COperation::getRang()
{
	return rang;
}

void COperation::setRang(int idParam)
{
	rang = idParam;
}

string COperation::getDateDebutApplicabilite()
{
	return dateDebutApplicabilite;
}

void COperation::setDateDebutApplicabilite(string str)
{
	dateDebutApplicabilite = str;
}

string COperation::getDateFinApplicabilite()
{
	return dateFinApplicabilite;
}

void COperation::setDateFinApplicabilite(string str)
{
	dateFinApplicabilite = str;
}

string COperation::getSEF()
{
	return sef;
}

void COperation::setSEF(string str)
{
	sef = str;
}

string COperation::getCadence()
{
	return cadence;
}

void COperation::setCadence(string str)
{
	cadence = str;
}

string COperation::getTypeOperation()
{
	return typeOperation;
}

void COperation::setTypeOperation(string str)
{
	typeOperation = str;
}

string COperation::getLibelleTypeOperation()
{
	return libelleTypeOperation;
}

void COperation::setLibelleTypeOperation(string str)
{
	libelleTypeOperation = str;
}

int COperation::getNbReferentielsApplicables()
{
	return nbReferentielsApplicables;
}

void COperation::setNbReferentielsApplicables(int i)
{
	nbReferentielsApplicables = i;
}

string COperation::getDeclinaisonMR()
{
	return declinaisonMR;
}

void COperation::setDeclinaisonMR(string str)
{
	declinaisonMR = str;
}


ostream & operator<<(std::ostream & out, COperation & obj)
{
	out << " === Operation === \n" << obj.getIdCplex() << endl << obj.getIdReference() << endl << obj.getRefOperation() << endl << obj.getDescOperation() << endl << obj.getVersionPMS() << endl
		<< obj.getVersionPMSEnCours() << endl << obj.getTypeOperationPartService() << endl << obj.getCycle() << endl << obj.getStfOpePart() << endl << obj.getStatutOpeRef() << endl
		<< obj.getLcnRacine() << endl << obj.getLcnArticle() << endl << obj.getRefDocMaintenance() << endl << obj.getRang() << endl << obj.getDateDebutApplicabilite() << endl
		<< obj.getDateFinApplicabilite() << endl << obj.getSEF() << endl << obj.getCadence() << endl << obj.getTypeOperation() << endl << obj.getLibelleTypeOperation() << endl
		<< obj.getNbReferentielsApplicables() << endl << obj.getDeclinaisonMR() << endl;

	return out;
}
