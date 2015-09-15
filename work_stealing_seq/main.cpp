#include "MonteCarlo.h"
#include "Recrystalization.h"
#include <stdio.h>
#include <iostream>

#define DATA_SIZE 10
using namespace std;

int main(){
	//MonteCarlo mc;
	//mc.monte_carlo_algorithm();
	Recrystalization rec;
	rec.recrystalization_algorithm();
	system("pause");
	return 0;

}

