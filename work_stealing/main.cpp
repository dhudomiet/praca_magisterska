#include <iostream>
#include <vector>
#include "constans.h"
#include <boost\thread.hpp>
#include "Recrystalization.h"


using namespace std;

int main(){
	//MonteCarlo mc;
	//mc.monte_carlo_algorithm();
	Recrystalization rec;
	rec.recrystalization_algorithm();
	system("pause");
	return 0;



}

