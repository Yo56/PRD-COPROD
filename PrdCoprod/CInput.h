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

public:
	CInput();
	CInput(int n, int m, int D, int nInfra, int nSite, int nSlot, int nTrain, int nAgent, int nSkill, double alpha, std::vector<double> p);
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
	/*double[] getP();*/

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


