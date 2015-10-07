#include "InitializeEnergy.h"


InitializeEnergy::InitializeEnergy(void) : Task()
{
}


InitializeEnergy::~InitializeEnergy(void)
{
}

InitializeEnergy::InitializeEnergy(int begin, int end, cell** cells) : Task(){
	this->begin = begin;
	this->end = end;
	this->cells = cells;
}
	
void InitializeEnergy::start(){
	th = boost::thread(&InitializeEnergy::execute,this);
}

void InitializeEnergy::execute(){
	for(int i=begin;i<end;i++) {
		for(int j=0;j<WIDTH;j++) {
			if (is_on_the_board(i, j, cells)) {
				cells[i][j].energy = ENERGY_ON_THE_BOARD;
			} else {
				cells[i][j].energy = ENERGY_ON_GRAIN;
			}
		}
	}
}

bool InitializeEnergy::is_on_the_board(int idx_i, int idx_j, cell** space_of_cells) {
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
			if (space_of_cells[i][j].id != space_of_cells[idx_i][idx_j].id) {
				return true;
			}
			tab[k] = space_of_cells[i][j].id;
			k++;
			j++;
		}
		i++;
		j=m;
	}
	return false;
}
