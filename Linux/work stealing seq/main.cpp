#include "MonteCarlo.h"
#include "Recrystalization.h"
#include "GrainGrow.h"
#include <stdio.h>
#include <iostream>

#define DATA_SIZE 10
using namespace std;

int main(){
	//Recrystalization rec;
	//rec.recrystalization_algorithm();
	GrainGrow g;
	g.grain_grow_algorithm();
	system("pause");
	return 0;

}

