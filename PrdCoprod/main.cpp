#include <iostream>
#include <ilcplex/ilocplex.h>

#include "Tuto.h"
#include "PLNE.h"

//ILOSTBEGIN

using namespace std;

int main()
{
	Tuto::basic();
	PLNE::run();

	return 0;
}



