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

	vector <vector<int> > NI_ik;
	vector <vector<int> > IN_jk;
	vector <vector<int> > rMax_lh;
	vector <int> rTot;
	vector <vector<int> > CO_ii;
	vector <vector<int> > NS_is;
	vector <vector <vector<int> > > SKL_asl;

	vector <vector<int> > H;
	vector <vector<int> > L;

public:
	CInput();
	CInput(int n, int m, int D, int nInfra, int nSite, int nSlot, int nTrain, int nAgent, int nSkill, double alpha,
		std::vector<double> p, std::vector<double> pDelta, std::vector<int> r, std::vector<int> d, std::vector<double> w, std::vector<double> u,
		vector <vector<int> > NI_ik, vector <vector<int> > IN_jk, vector <vector<int> > rMax_lh, vector<int> rTot, vector <vector<int> > CO_ii,
		vector <vector<int> >NS_is, vector <vector <vector<int> > > SKL_asl, vector <vector<int> > H, vector <vector<int> > L);

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
	vector <vector<int> > getNI_ik();
	vector <vector<int> > getIN_jk();
	vector <vector<int> > getRMax_lh();
	vector<int> getRTot();
	vector <vector<int> > getCO_ii();
	vector <vector<int> >getNS_is();
	vector <vector <vector<int> > > getSKL_asl();
	vector <vector<int> > getH();
	vector <vector<int> > getL();

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


