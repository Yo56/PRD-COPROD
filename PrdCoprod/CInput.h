#pragma once
#include <iostream>
#include <vector>

using namespace std;

class CInput
{
private:
	int n, m, D, nInfra, nSite, nSlot, nTrain, nAgent, nSkill;
	double alpha;

	vector<double> p;
	vector<double> pDelta;
	vector<int> r;
	vector<int> d;
	vector<double> w;
	vector<double> u;

public:
	CInput();
	CInput(int n, int m, int D, int nInfra, int nSite, int nSlot, int nTrain, int nAgent, int nSkill, double alpha,
		std::vector<double> p, std::vector<double> pDelta, std::vector<int> r, std::vector<int> d, std::vector<double> w, std::vector<double> u);

	~CInput();
	void print();

	// GETTERS and SETTERS

	int getN();
	int getM();
	int getD();
	int getNInfra();
	int getNSite();
	int getNSlot();
	int getNTrain();
	int getNAgent();
	int getNSkill();
	double getAlpha();
	vector<double> getP();
	vector<double> getPDelta();
	vector<int> getR();
	vector<int> getDateDeRentree();
	vector<double> getW();
	vector<double> getU();

	void setN(int i);
	void setM(int i);
	void setD(int i);
	void setNInfra(int i);
	void setNSite(int i);
	void setNSlot(int i);
	void setNTrain(int i);
	void setNAgent(int i);
	void setNSkill(int i);
	void setAlpha(double i);
};


