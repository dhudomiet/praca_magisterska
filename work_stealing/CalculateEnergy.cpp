#include "CalculateEnergy.h"


CalculateEnergy::CalculateEnergy(void) : Task()
{

}

CalculateEnergy::CalculateEnergy(int params[4], cell** cells) : Task(){
	for(int i=0;i<4;i++){
		this->params[i] = params[i];
	}
	this->cells = cells;
}

CalculateEnergy::~CalculateEnergy(void)
{
	th->detach();
}

void CalculateEnergy::start(){
	th = new boost::thread(&CalculateEnergy::execute,this);
}

void CalculateEnergy::execute(){
	int end1 = params[0]+params[1];
	int end2 = params[2]+params[3];
	for(int i=params[0];i<end1;i++){
		for(int j=params[2];j<end2;j++){
			cells[i][j].energy = cal_energy(i,j,cells[i][j].id,cells);
		}
	}
}

int CalculateEnergy::cal_energy(int idx_i, int idx_j,int id, cell** space_of_cells) {
	srand(time(NULL));
	int *tab;
	int k=0,i=0,j=0,endI=0,endJ=0;
	if (idx_i == 0 && idx_j == 0) {
		tab = new int[3];
		i = idx_i;
		endI = idx_i+2;
		j = idx_j;
		endJ = idx_j+2;
	} else if (idx_i == 0 && idx_j == WIDTH - 1) {
		tab = new int[3];
		i = idx_i;
		endI = idx_i+2;
		j = idx_j-1;
		endJ = idx_j+1;
	} else if (idx_i == HEIGHT - 1 && idx_j == 0) {
		tab = new int[3];
		i = idx_i-1;
		endI = idx_i+1;
		j = idx_j;
		endJ = idx_j+2;
	} else if (idx_i == HEIGHT - 1 && idx_j == WIDTH - 1) {
		tab = new int[3];
		i = idx_i-1;
		endI = idx_i+1;
		j = idx_j-1;
		endJ = idx_j+1;
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == 0) {
		tab = new int[5];
		i = idx_i-1;
		endI = idx_i+2;
		j = idx_j;
		endJ = idx_j+2;
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == WIDTH - 1) {
		tab = new int[5];
		i = idx_i-1;
		endI = idx_i+2;
		j = idx_j-1;
		endJ = idx_j+1;
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == 0) {
		tab = new int[5];
		i = idx_i;
		endI = idx_i+2;
		j = idx_j-1;
		endJ = idx_j+2;
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == HEIGHT - 1) {
		tab = new int[5];
		i = idx_i-1;
		endI = idx_i+1;
		j = idx_j-1;
		endJ = idx_j+2;
	} else {
		tab = new int[8];
		i = idx_i-1;
		endI = idx_i+2;
		j = idx_j-1;
		endJ = idx_j+2;
	}
	int m = j;
	while(i < endI) {
		while(j < endJ) {
			if (i == idx_i && j == idx_j){
				j++;
				continue;
			}
			tab[k] = space_of_cells[i][j].id;
			k++;
			j++;
		}
		i++;
		j=m;
	}
	int energy = 0;
	for (i = 0; i < k; i++) {
		if (tab[i] != id) {
			energy++;
		}

	}
	delete[] tab;
	return energy;
}

void CalculateEnergy::toString(){
	cout<<"execute task CalculateEnergy..."<<endl;
}