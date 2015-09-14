#include "MonteCarlo.h"
//#include "Recrystalization.h"
#include <stdio.h>
#include <iostream>
#include <concurrent_vector.h>
#include <vector>


#define DATA_SIZE 10
using namespace std;

int main(){
	MonteCarlo mc;
	mc.monte_carlo_algorithm();
	//std::cout<<std::endl;
	//std::cout<<std::endl;
	//mc.copy_spaces(mc.oldstate,mc.cells);
	/*for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			std::cout<<mc.oldstate[i][j].id<<" ";
		}
		std::cout<<std::endl;
	}*/
	system("pause");
	return 0;



}

