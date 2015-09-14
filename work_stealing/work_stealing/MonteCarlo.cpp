/*
* MonteCarlo.cpp
*
*  Created on: Aug 15, 2015
*      Author: damian
*/

#include "MonteCarlo.h"

MonteCarlo::MonteCarlo() {
	initialize_ids();

}

void MonteCarlo::initialize_ids() {
	srand(time(NULL));
	logg("initialize Ids");
	clock_t start, stop;
	start = clock();
	for(int i=0;i<WIDTH;i++){
		cell* tab = new cell[WIDTH];
		parallel_for(0,HEIGHT,[&](int j) {
			tab[j].id=rand() % NUMBER_OF_IDS+1;
			tab[j].idx_i=i;
			tab[j].idx_j=j;
			tab[j].flag=true;

		});	
		cells.push_back(tab);
		oldstate.push_back(tab);
	}


	stop = clock();
	float t = (float)stop - (float)start;
	std::cout<<"time: "<<t<<std::endl;
	draw_space();
	std::cout<<std::endl;
	std::cout<<std::endl;
	/*for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			std::cout<<i<<" "<<j<<" "<<cells.at(i)[j].idx_i<<" "<<cells.at(i)[j].idx_j<<std::endl;
		}
	}*/

}

void MonteCarlo::calculate_energy() {
	clock_t start, stop;
	start = clock();
	concurrency::parallel_for(0,HEIGHT,[&](int i) {
		concurrency::parallel_for(0,HEIGHT,[&](int j) {
			cells.at(i)[j].energy=cal_energy(i, j, cells.at(i)[j].id, cells);
		});
	});
	stop = clock();
	//loggTime("time of execution function calculate_energy: ",(float)stop-(float)start);
}

void MonteCarlo::cal_energy(int idx_i, int idx_j,int * point, concurrent_vector<cell*> space_of_cells) {
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
	for (i ; i < endI; i++) {
		for (j ; j < endJ; j++) {
			if (i == idx_i && j == idx_j)
				continue;
			tab[k] = space_of_cells.at(i)[j].id;
			k++;
		}
	}
	int energy = 0;
	int id = -1;
	for (int i = 0; i < 8; i++) {
		id = tab[i];
		if (id != space_of_cells.at(idx_i)[idx_j].id) {
			for (int i = 0; i < k; i++) {
				if (tab[i] != id) {
					energy++;
				}
			}
			point[0] = id;
			point[1] = energy;
			return;
		}
	}
	point[0] = -1;
	point[1] = energy;
	delete[] tab;


}

int MonteCarlo::cal_energy(int idx_i, int idx_j,int id, concurrent_vector<cell*> space_of_cells) {
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
	for (int i ; i < endI ; i++) {
		for (j ; j < endJ; j++) {
			if (i == idx_i && j == idx_j)
				continue;
			tab[k] = space_of_cells.at(i)[j].id;
			k++;
		}
	}
	int energy = 0;
	for (int i = 0; i < 8; i++) {
		if (tab[i] != id) {
			energy++;
		}
	}
	return energy;


}

void MonteCarlo::monte_carlo_algorithm() {
	logg("start monteCarlo algorithm...");
	clock_t start,stop;
	start=clock();
	calculate_energy();
	std::vector<cell> listCells;
	copy_spaces(oldstate, cells);
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		fill_list(&listCells, cells);
		int size = listCells.size();
		while (size>0) {
			int number = rand() % size;
			cell data = listCells.at(number);
			int er = number -1;
			if(er < 0){
				er = 0;
			}
			listCells.erase(listCells.begin()+er);
			int tab[2];
			int *p = tab;
			cal_energy(data.idx_i, data.idx_j, p, oldstate);
			if (p[0] == -1) {
				continue;
			}
			int delta = p[1] - data.energy;
			if (delta <= 0) {
				cells.at(data.idx_i)[data.idx_j].id=p[0];
				cells.at(data.idx_i)[data.idx_j].energy=p[1];
			}
			size = listCells.size();
		}
		copy_spaces(oldstate, cells);
	}
	stop=clock();
	float time = (float)stop - (float)start;
	loggTime("time execution monteCarlo algorithm: ",time);
	draw_space();

}

void MonteCarlo::fill_list(std::vector<cell> *vect, concurrent_vector<cell*> space) {
	concurrency::concurrent_vector<cell> vct;
	concurrency::parallel_for(0,HEIGHT,[&](int i) {
		concurrency::parallel_for(0,HEIGHT,[&](int j) {
			if (is_on_the_board(i, j, space)) {
				vct.push_back(space.at(i)[j]);
			}
		});
	});
	for(unsigned int i=0;i<vct.size();i++){
		vect->push_back(vct.at(i));
	}
}

bool MonteCarlo::is_on_the_board(int idx_i, int idx_j, concurrent_vector<cell*> space_of_cells) {
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

	for (int i ; i < endI ; i++) {
		for (j ; j < endJ; j++) {
			if (i == idx_i && j == idx_j)
				continue;
			if (space_of_cells.at(i)[j].id != space_of_cells.at(idx_i)[idx_j].id) {
				return true;
			}
		}
	}
	return false;


}



void MonteCarlo::draw_energy() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << cells.at(i)[j].energy << " ";
		}
		std::cout << std::endl;
	}
}

void MonteCarlo::copy_spaces(concurrent_vector<cell*> space, concurrent_vector<cell*> source_space) {
	clock_t start, stop;
	for(int i = 0;i< HEIGHT;i++){
		parallel_for(0,WIDTH, [&](int j){
			source_space.at(i)[j].id = source_space.at(i)[j].id; 
			source_space.at(i)[j].idx_i = source_space.at(i)[j].idx_i;
			source_space.at(i)[j].idx_j = source_space.at(i)[j].idx_j;
			source_space.at(i)[j].flag = source_space.at(i)[j].flag;
			source_space.at(i)[j].energy = source_space.at(i)[j].energy;
		});
	}

	stop = clock();
	float diff = (float)stop - (float)start;
	//loggTime("time of execution copySpace function: ",diff);
}

MonteCarlo::MonteCarlo(concurrent_vector<cell*> cells) {
	concurrency::parallel_for(0,HEIGHT,[&](int i){
		concurrency::parallel_for(0,WIDTH,[&](int j){
			this->cells.at(i)[j] = cells.at(i)[j];
		});
	});
}

void MonteCarlo::set_cells(concurrent_vector<cell*> cells) {
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			cells.at(i)[j] = this->cells.at(i)[j];
		}
	}

}

void MonteCarlo::draw_space() {
	for (int i = 0; i < HEIGHT; i++) {
		for(int j=0;j<WIDTH;j++){
			std::cout<<cells.at(i)[j].id<<" ";
		}
		std::cout<<std::endl;


	}
}


