/*
* MonteCarlo.cpp
*
*  Created on: Aug 15, 2015
*      Author: damian
*/

#include "MonteCarlo.h"

MonteCarlo::MonteCarlo() {
	initialize_ids();
	calculate_energy();
	//initialize_ids();
}

void MonteCarlo::initialize_ids() {
	logg("initialize Ids");
	clock_t start, stop;
	int sum = 0;
	int step = HEIGHT/CORES;
	boost::thread_group group;
	cells = new cell*[HEIGHT];
	for(int i=0;i<CORES;i++){
		WorkStealing* ws = new WorkStealing();
	}
	while(sum<HEIGHT){
		InitializeIds* init = new InitializeIds(sum,sum+step,cells);
		WorkStealing::getCore(0)->addTask(init);
		sum+=step;
	}
	start = clock();
	for(int i= CORES-1;i>=0;i--){
		group.add_thread(WorkStealing::getCore(i)->start());
	}
	group.join_all();
	stop = clock();
	float t = (float)stop - (float)start;
	WorkStealing::clear();
	draw_space();
}

void MonteCarlo::calculate_energy() {
	clock_t start, stop;
	int sum = 0;
	int step = HEIGHT/CORES;
	boost::thread_group group;
	cout<<"calculate energy"<<endl;
	for(unsigned i = 0;i<CORES;i++){
		WorkStealing* wo = new WorkStealing();
	}
	while(sum<HEIGHT){
		CalculateEnergy* init = new CalculateEnergy(sum,sum+step,cells);
		WorkStealing::getCore(0)->addTask(init);

		sum+=step;
	}
	start = clock();
	for(int i=CORES-1;i>=0;i--){
		group.add_thread(WorkStealing::getCore(i)->start());
	}
	group.join_all();
	stop = clock();
	WorkStealing::clear();
	float t = (float)stop - (float)start;
	//loggTime("time of execution function calculate_energy: ",(float)stop-(float)start);
	draw_energy();
}
/*
void MonteCarlo::cal_energy(int idx_i, int idx_j,int * point, concurrent_vector<cell*> *space_of_cells) {
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
	for (int i = 0; i < k; i++) {
		id = tab[i];
		if (id != space_of_cells->at(idx_i)[idx_j].id) {
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
	return;
}

void MonteCarlo::monte_carlo_algorithm() {
	logg("start monteCarlo algorithm...");
	clock_t start,stop;
	start=clock();
	calculate_energy();
	concurrent_vector<cell> listCells;
	copy_spaces(oldstate, cells);
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		fill_list(&listCells, cells);
		int size = listCells.size();
		parallel_for(0,size,[&](int j) {
			cell data = listCells.at(j);
			int tab[2];
			int *p = tab;
			cal_energy(data.idx_i, data.idx_j, p, &oldstate);
			if (p[0] != -1) {
				int delta = p[1] - data.energy;
				if (delta <= 0) {
					cells.at(data.idx_i)[data.idx_j].id=p[0];
					cells.at(data.idx_i)[data.idx_j].energy=p[1];
				}

			}
		});
		listCells.clear();
		copy_spaces(oldstate, cells);
	}
	stop=clock();
	float time = (float)stop - (float)start;
	loggTime("time execution montecarlo algorithm: ",time);
	draw_space();

}

void MonteCarlo::fill_list(concurrent_vector<cell> *vect, concurrent_vector<cell*> space) {
	parallel_for(0,HEIGHT,[&](int i) {
		parallel_for(0,WIDTH,[&](int j) {
			if (is_on_the_board(i, j, &space)) {
				vect->push_back(space.at(i)[j]);
			}
		});
	});

}

bool MonteCarlo::is_on_the_board(int idx_i, int idx_j, concurrent_vector<cell*> *space_of_cells) {
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
			if (space_of_cells->at(i)[j].id != space_of_cells->at(idx_i)[idx_j].id) {
				return true;
			}
			tab[k] = space_of_cells->at(i)[j].id;
			k++;
			j++;
		}
		i++;
		j=m;
	}
	return false;


}

void MonteCarlo::copy_spaces(concurrent_vector<cell*> space, concurrent_vector<cell*> source_space) {
	clock_t start, stop;
	for(int i = 0;i< HEIGHT;i++){
		parallel_for(0,WIDTH, [&](int j){
			space.at(i)[j].id = source_space.at(i)[j].id; 
			space.at(i)[j].idx_i = source_space.at(i)[j].idx_i;
			space.at(i)[j].idx_j = source_space.at(i)[j].idx_j;
			space.at(i)[j].flag = source_space.at(i)[j].flag;
			space.at(i)[j].energy = source_space.at(i)[j].energy;
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

void MonteCarlo::set_cells(concurrent_vector<cell*> *cells) {
	parallel_for(0,HEIGHT,[&](int i){
		parallel_for(0,WIDTH,[&](int j){
			cells->at(i)[j].id = this->cells.at(i)[j].id;
			cells->at(i)[j].idx_i = this->cells.at(i)[j].idx_i;
			cells->at(i)[j].idx_j = this->cells.at(i)[j].idx_j;
			cells->at(i)[j].energy = this->cells.at(i)[j].energy;
			cells->at(i)[j].flag = this->cells.at(i)[j].flag;
		});
	});

}
*/

void MonteCarlo::draw_energy() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << cells[i][j].energy << " ";
		}
		std::cout << std::endl;
	}
}

void MonteCarlo::draw_space() {
	for (int i = 0; i < HEIGHT; i++) {
		for(int j=0;j<WIDTH;j++){
			cout<<cells[i][j].id<<" ";
		}
		cout<<endl;
	}
}
