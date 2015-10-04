#include "CalculateEnergy.h"


CalculateEnergy::CalculateEnergy(void) : Task()
{
}

CalculateEnergy::CalculateEnergy(int begin, int end, cell** cells) : Task(){
	this->begin = begin;
	this->end = end;
	this->cells = cells;
}

CalculateEnergy::~CalculateEnergy(void)
{
}

void CalculateEnergy::start(){
	th = boost::thread(&CalculateEnergy::execute,this,begin,end,cells);
}

void CalculateEnergy::execute(int begin, int end, cell** cells){
	end = (end>HEIGHT)? HEIGHT : end;
	cout<<"calculate energy..."<<endl;
	for(int i=begin;i<end;i++){
		for(int j=0;j<WIDTH;j++){
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