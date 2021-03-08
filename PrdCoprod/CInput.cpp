#include "CInput.h"



CInput::CInput()
{
}

CInput::CInput(int n, int m, int D, int nInfra, int nSite, int nSlot, int nTrain, int nAgent, int nSkill, double alpha, std::vector<double> pParam, std::vector<double> pDeltaParam, std::vector<int> rParam, std::vector<int> dParam, std::vector<double> wParam, std::vector<double> uParam)
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
}


CInput::~CInput()
{
}

void CInput::print() {
	for (auto val = p.begin(); val != p.end(); ++val) {
	cout << *val << endl;
	}
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

