#include "ExecuteList.h"


ExecuteList::ExecuteList(void) : Task()
{
}

ExecuteList::ExecuteList(int begin,int end,std::vector<cell*> *vect, cell** cells, cell** oldstate) : Task(){
	this->begin = begin;
	this->end = end;
	this->vect = vect;
	this->cells = cells;
	this->oldstate = oldstate;
}

ExecuteList::~ExecuteList(void)
{
	
}

void ExecuteList::start(){

}

void ExecuteList::execute(){
	//end = (end>vect->size())? vect->size() : end;
	//cout<<begin<<"  "<<end<<endl;
	for(int i=begin;i<end;i++){
		cell data = *vect->at(i);
		int tab[2];
		int *p = tab;
		cal_energy(data.idx_i, data.idx_j, p, oldstate);
		if (p[0] != -1) {
			int delta = p[1] - data.energy;
			if (delta <= 0) {
				cells[data.idx_i][data.idx_j].id=p[0];
				cells[data.idx_i][data.idx_j].energy=p[1];
			}
		}
	}
}

void ExecuteList::cal_energy(int idx_i, int idx_j,int * point, cell** space_of_cells) {
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
	int id = -1;
	for (int i = 0; i < k; i++) {
		id = tab[i];
		if (id != space_of_cells[idx_i][idx_j].id) {
			for (int j = 0; j < k; j++) {
				if (tab[j] != id) {
					energy++;
				}
			}
			point[0] = id;
			point[1] = energy;
			delete[] tab;
			return;
		}
	}
	point[0] = -1;
	point[1] = energy;
	delete[] tab;
	return;
}

void ExecuteList::toString(){
	std::cout<<"execute task ExecuteList..."<<std::endl;
}
