#pragma once
#include <iostream>
#include <ilcplex/ilocplex.h>
#include <vector>
#include "COperation.h"

class PLNE2
{
public:
	PLNE2();
	~PLNE2();
	void print();
	int opY(int f, int indiceRelatifF);
};

