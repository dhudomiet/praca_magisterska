#include <iostream>
#include <vector>
#include "constans.h"
#include <boost/thread.hpp>
#include "MonteCarlo.h"
#include "Recrystalization.h"
#include "GrainGrow.h"
#include <functional>
using namespace std;

int main(int argc, char* argv[]){
	int cores=atoi(argv[1]);
	cout<<"set cores: "<<cores<<endl;
	Grain_grow g(cores);
	g.grainGrowAlgorithm();
	//Recrystalization r;
	//r.recrystalization_algorithm();
	return 0;


}

