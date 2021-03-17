/*!
 * \file Cinput.cpp
 * \brief Elements permettant de fournir les donnees d'entrees a un modele de resolution
 * \author Yohan Nouet
 * \version 1
 */

#include "CInput.h"



CInput::CInput(int n, int m, int D, int nInfra, int nSite, int nSlot, int nTrain, int nAgent, int nSkill, double alpha,
	vector<double> pParam, vector<double> pDeltaParam, vector<int> rParam, vector<int> dParam, vector<double> wParam, vector<double> uParam,
	vector <vector<int> > NI_ikParam, vector <vector<int> > IN_jkParam, vector <vector<int> > rMax_lhParam, vector<int> rTotParam,
	vector <vector<int> > CO_iiParam, vector <vector<int> >NS_isParam, vector <vector <vector<int> > > SKL_aslParam, vector <vector<int> > HParam, vector <vector<int> > LParam,
	vector <vector<int> > OprevParam, vector <vector<int> > OcorrParam, vector <vector <vector<int> > > TtrainParam,
	vector <vector <vector<int> > > TtrackParam, vector < vector <vector <vector<int> > > > TfjParam, vector <vector <vector<int> > > TagentParam)
{
	this->n = n; 
	this->m = m;
	this->D = D;
	this->nInfra = nInfra;
	this->nSite = nSite;
	this->nSlot = nSlot;
	this->nTrain = nTrain;
	this->nAgent = nAgent;
	this->nSkill = nSkill;
	this->alpha = alpha;

	this->p = pParam;
	this->pDelta = pDeltaParam;
	this->r = rParam;
	this->d = dParam;
	this->w = wParam;
	this->u = uParam;
	this->NI_ik = NI_ikParam;
	this->IN_jk = IN_jkParam;
	this->rMax_lh = rMax_lhParam;
	this->rTot = rTotParam;
	this->CO_ii = CO_iiParam;
	this->NS_is = NS_isParam;
	this->SKL_asl = SKL_aslParam;

	this->H = HParam;
	this->L = LParam;
	this->Oprev = OprevParam;
	this->Ocorr = OcorrParam;
	this->Ttrain = TtrainParam;
	this->Ttrack = TtrackParam;
	this->Tfj = TfjParam;
	this->Tagent = TagentParam;
}


CInput::~CInput()
{
}

void CInput::print() {
	cout << "== Input ==" << endl;
	cout << "n : " << n << endl;
	cout << "m : " << m << endl;
	cout << "D : " << D << endl;
	cout << "nInfra : " << nInfra << endl;
	cout << "nSite : " << nSite << endl;
	cout << "nSlot : " << nSlot << endl;
	cout << "nTrain : " << nTrain << endl;
	cout << "nAgent : " << nAgent << endl;
	cout << "nSkill : " << nSkill << endl;
	cout << "alpha : " << alpha << endl;

	/*cout <<endl << "p : ";
	for (auto val = p.begin(); val != p.end(); ++val) {
	cout << *val << endl;
	}
	cout << "pDelta : ";
	for (auto val = pDelta.begin(); val != pDelta.end(); ++val) {
		cout << *val << endl;
	}
	cout << "r : ";
	for (auto val = r.begin(); val != r.end(); ++val) {
		cout << *val << endl;
	}
	cout << "d : ";
	for (auto val = d.begin(); val != d.end(); ++val) {
		cout << *val << endl;
	}
	cout << "w : ";
	for (auto val = w.begin(); val != w.end(); ++val) {
		cout << *val << endl;
	}
	cout << "u : ";
	for (auto val = u.begin(); val != u.end(); ++val) {
		cout << *val << endl;
	}*/
	
}

////////////////// getters and setters

int CInput::getN()
{
	return n;
}

int CInput::getM()
{
	return m;
}

int CInput::getD()
{
	return D;
}

int CInput::getNInfra()
{
	return nInfra;
}

int CInput::getNSite()
{
	return nSite;
}

int CInput::getNSlot()
{
	return nSlot;
}

int CInput::getNTrain()
{
	return nTrain;
}

int CInput::getNAgent()
{
	return nAgent;
}

int CInput::getNSkill()
{
	return nSkill;
}

double CInput::getAlpha()
{
	return alpha;
}

vector<double> CInput::getP()
{
	return p;
}

vector<double> CInput::getPDelta()
{
	return pDelta;
}

vector<int> CInput::getR()
{
	return r;
}

vector<int> CInput::getDateDeRentree()
{
	return d;
}

vector<double> CInput::getW()
{
	return w;
}

vector<double> CInput::getU()
{
	return u;
}

vector<vector<int>> CInput::getNI_ik()
{
	return NI_ik;
}

vector<vector<int>> CInput::getIN_jk()
{
	return IN_jk;
}

vector<vector<int>> CInput::getRMax_lh()
{
	return rMax_lh;
}

vector<int> CInput::getRTot()
{
	return rTot;
}

vector<vector<int>> CInput::getCO_ii()
{
	return CO_ii;
}

vector<vector<int>> CInput::getNS_is()
{
	return NS_is;
}

vector<vector<vector<int>>> CInput::getSKL_asl()
{
	return SKL_asl;
}

vector<vector<int>> CInput::getH()
{
	return H;
}

vector<vector<int>> CInput::getL()
{
	return L;
}

vector<vector<int>> CInput::getOprev()
{
	return Oprev;
}

vector<vector<int>> CInput::getOcorr()
{
	return Ocorr;
}

vector<vector<vector<int>>> CInput::getTtrain()
{
	return Ttrain;
}

vector<vector<vector<int>>> CInput::getTtrack()
{
	return Ttrack;
}

vector<vector<vector<vector<int>>>> CInput::getTfj()
{
	return Tfj;
}

vector<vector<vector<int>>> CInput::getTagent()
{
	return Tagent;
}


void CInput::setN(int i)
{
	n = i;
}

void CInput::setM(int i)
{
	m = i;
}

void CInput::setD(int i)
{
	D = i;
}

void CInput::setNInfra(int i)
{
	nInfra = i;
}

void CInput::setNSite(int i)
{
	nSite = i;
}

void CInput::setNSlot(int i)
{
	nSlot = i;
}

void CInput::setNTrain(int i)
{
	nTrain = i;
}

void CInput::setNAgent(int i)
{
	nAgent = i;
}

void CInput::setNSkill(int i)
{
	nSkill = i;
}

void CInput::setAlpha(double i)
{
	alpha = i;
}

