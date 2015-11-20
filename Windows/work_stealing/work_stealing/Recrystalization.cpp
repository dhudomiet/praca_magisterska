/*
 * Recrystalization.cpp
 *
 *  Created on: Aug 23, 2015
 *      Author: damian
 */

#include "Recrystalization.h"

Recrystalization::Recrystalization() {
	initializeSpace();
}

void Recrystalization::recrystalization_algorithm() {
	concurrent_vector<cell> noRecrystalizationCells;
	clock_t start, stop;
	start = clock();
	randomRecGrains();
	fill_no_recrystalization_list(&noRecrystalizationCells);
	for (int i = 0; i < 1000; i++) {
		srand(time(NULL));
		int size = noRecrystalizationCells.size();
		parallel_for(0,size,[&] (int j) {
			cell grain = noRecrystalizationCells.at(j);
			int era = j - 1;
			if(era<0){
				era = 0;
			}
			int tab[2];
			int *p = tab;
			cal_energy(grain.idx_i, grain.idx_j, p, &cells);
			if (p[0] < 0) {
				int energy = 0;
				energy = p[1] + H;
				int energyRec = cells.at(grain.idx_i)[grain.idx_j].energy+ energy;
				energy = cells.at(grain.idx_i)[grain.idx_j].energy;
				if (energyRec > energy) {
					cells.at(grain.idx_i)[grain.idx_j].energy=0;
					cells.at(grain.idx_i)[grain.idx_j].id=p[0];
					recrystalizationList.push_back(cells.at(grain.idx_i)[grain.idx_j]);
				}

			}
		});
		noRecrystalizationCells.clear();
		fill_no_recrystalization_list(&noRecrystalizationCells);
		if (noRecrystalizationCells.size() == 0) {
			break;
		}
	}
	stop = clock();
	float t = (float)stop - (float)start;
	loggTime("time of execution recrystalization: ",t);
	draw_data();
}

void Recrystalization::draw_data() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << cells[i][j].id<< " ";
		}
		std::cout << std::endl;
	}
}

void Recrystalization::initializeSpace() {
	parallel_for(0,HEIGHT,[&](int i){
		cell* tab = new cell[WIDTH];
		cells.push_back(tab);
		
	});
	mc.monte_carlo_algorithm();
	mc.set_cells(&cells);
	initializeEnergy();

}

void Recrystalization::initializeEnergy() {
	parallel_for(0,HEIGHT,[&] (int i) {
		parallel_for(0,WIDTH,[&] (int j) {
			if (mc.is_on_the_board(i, j, &cells)) {
				cells.at(i)[j].energy = ENERGY_ON_THE_BOARD;
			} else {
				cells.at(i)[j].energy = ENERGY_ON_GRAIN;
			}
		});
	});
}

void Recrystalization::cal_energy(int idx_i, int idx_j, int * point, concurrent_vector<cell*> *space_of_cells) {
	
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
			tab[k] = space_of_cells->at(i)[j].id;
			k++;
			j++;
		}
		i++;
		j=m;
	}
	int energy = 0;
		int id = -1;
		std::vector<int *> data;
		for (int i = 0; i < k; i++) {
			id = tab[i];
			if (id < 0) {
				for (int j = 0; j < k; j++) {
					if (tab[j] == id) {
						energy++;

					}
				}
				if (energy != 0) {
					int count = 0;
					for (unsigned int i = 0; i < data.size(); i++) {
						if (id == data.at(i)[0]) {
							count = -1;
							break;
						}
					}
					if (count != -1) {
						int * d = new int[2];
						d[0] = id;
						d[1] = energy;
						energy = 0;
						data.push_back(d);
					}
				}

			}
		}
		if (data.size() > 0) {
			int * w = data.at(0);
			for (unsigned int i = 0; i < data.size(); i++) {
				for (unsigned int j = 0; j < data.size(); j++) {
					if (w[1] < data.at(j)[1]) {
						w = data.at(j);
					}
				}
				break;
			}
			point[0] = w[0];
			point[1] = w[1];
			return;
		} else {
			point[0] = 0;
			point[1] = 0;
			return;
		}

}

void Recrystalization::fill_no_recrystalization_list(concurrent_vector<cell>* list) {
	parallel_for(0,HEIGHT,[&](int i) {
		parallel_for(0,WIDTH,[&](int j) {
			if (cells.at(i)[j].energy > 0) {
				list->push_back(cells.at(i)[j]);
			}
		});
	});
}

void Recrystalization::randomRecGrains() {
	srand(time(NULL));
	for (int i = 1; i <= RECRYSTALIZATION_GRAINS; i++) {
		int x = rand() % HEIGHT;
		int y = rand() % WIDTH;
		if (mc.is_on_the_board(x, y, &cells)) {
			cells.at(x)[y].id = -i;
			cells.at(x)[y].energy = 0;
			recrystalizationList.push_back(cells.at(x)[y]);
		} else {
			i--;
		}
	}
}
