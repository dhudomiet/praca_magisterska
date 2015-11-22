#include "ExecuteGrainGrow.h"


ExecuteGrainGrow::ExecuteGrainGrow(void)
{
}

ExecuteGrainGrow::ExecuteGrainGrow(int params[4], int** space, int** old_space){
	for(int i=0;i<4;i++){
		this->params[i] = params[i];
	}
	this->space = space;
	this->old_space = old_space;
}


ExecuteGrainGrow::~ExecuteGrainGrow(void)
{
	
}

void ExecuteGrainGrow::start(){

}
void ExecuteGrainGrow::execute(){
	int end1 = params[0]+params[1];
	int end2 = params[2]+params[3];
	for (int i = params[0]; i < end1; i++) {
		for (int j = params[2]; j < end2; j++) {
			if (old_space[i][j] == 0) {
				int tab[2];
				if (is_neighbor(i, j, tab, old_space)) {
					space[i][j] = old_space[tab[0]][tab[1]];
				}
			}
		}
	}
}
void ExecuteGrainGrow::toString(){
	cout<<"execute task executeGrainGrow..."<<endl;
}

bool ExecuteGrainGrow::is_neighbor(int idx_i, int idx_j, int *tab, int **space_of_cells){
	if (idx_i == 0 && idx_j == 0) {
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == 0 && j == 0)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_i == 0 && idx_j == WIDTH - 1) {
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_i == HEIGHT - 1 && idx_j == 0) {
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_i == HEIGHT - 1 && idx_j == WIDTH - 1) {
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == 0) {
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == WIDTH - 1) {
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == 0) {
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == HEIGHT - 1) {
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else {
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	}

}
