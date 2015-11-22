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
	std::vector<cell> noRecrystalizationCells;
	clock_t start,stop;
	logg("start of recrystalization algorithm...");
	start = clock();
	randomRecGrains();
	fill_no_recrystalization_list(&noRecrystalizationCells);
	for (int i = 0; i < 1000; i++) {
		srand(time(NULL));
		while (noRecrystalizationCells.size() > 0) {
			int number = rand() % noRecrystalizationCells.size();
			cell grain = noRecrystalizationCells.at(number);
			int era = number - 1;
			if(era<0){
				era = 0;
			}
			noRecrystalizationCells.erase(noRecrystalizationCells.begin() + era);
			int tab[2];
			int *p = tab;
			cal_energy(grain.idx_i, grain.idx_j, p, cells);
			if (p[0] < 0) {
				int energy = 0;
				energy = p[1] + H;
				int energyRec = cells[grain.idx_i][grain.idx_j].energy + energy;
				energy = cells[grain.idx_i][grain.idx_j].energy;
				if (energyRec > energy) {
					cells[grain.idx_i][grain.idx_j].energy = 0;
					cells[grain.idx_i][grain.idx_j].id = p[0];
					recrystalizationList.push_back(cells[grain.idx_i][grain.idx_j]);
				}

			}
		}
		fill_no_recrystalization_list(&noRecrystalizationCells);
		if (noRecrystalizationCells.size() == 0) {
			break;
		}
	}
	stop = clock();
	float t = (float)stop - (float)start;
	loggTime("time of execution recrystalization: ",t);
	//draw_data();
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
	cells = new cell*[HEIGHT];
	for(int i=0;i<HEIGHT;i++){
		cells[i] = new cell[WIDTH];
		
	}
	mc.monte_carlo_algorithm();
	mc.set_cells(cells);
	initializeEnergy();
}

void Recrystalization::initializeEnergy() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (mc.is_on_the_board(i, j, cells)) {
				cells[i][j].energy=ENERGY_ON_THE_BOARD;
			} else {
				cells[i][j].energy=ENERGY_ON_GRAIN;
			}
		}
	}
} 

void Recrystalization::cal_energy(int idx_i, int idx_j, int * point,
		cell** space_of_cells) {
	srand(time(NULL));
	if (idx_i == 0 && idx_j == 0) {
		int tab[3];
		int k = 0;
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == 0 && j == 0)
					continue;
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}

		int energy = 0;
		int id = -1;
		std::vector<int *> data;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id < 0) {
				for (int j = 0; j < 3; j++) {
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
	} else if (idx_i == 0 && idx_j == WIDTH - 1) {
		int tab[3];
		int k = 0;
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		std::vector<int *> data;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id < 0) {
				for (int j = 0; j < 3; j++) {
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
	} else if (idx_i == HEIGHT - 1 && idx_j == 0) {
		int tab[3];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		std::vector<int *> data;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id < 0) {
				for (int j = 0; j < 3; j++) {
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
	} else if (idx_i == HEIGHT - 1 && idx_j == WIDTH - 1) {
		int tab[3];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		std::vector<int *> data;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id < 0) {
				for (int j = 0; j < 3; j++) {
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
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == 0) {
		int tab[5];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		std::vector<int *> data;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id < 0) {
				for (int j = 0; j < 5; j++) {
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
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == WIDTH - 1) {
		int tab[5];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		std::vector<int *> data;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id < 0) {
				for (int j = 0; j < 5; j++) {
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
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == 0) {
		int tab[5];
		int k = 0;
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		std::vector<int *> data;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id < 0) {
				for (int j = 0; j < 5; j++) {
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
			point[1] = energy;
			return;
		}
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == HEIGHT - 1) {
		int tab[5];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		std::vector<int *> data;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id < 0) {
				for (int j = 0; j < 5; j++) {
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

	} else {
		int tab[8];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		std::vector<int *> data;
		for (int i = 0; i < 8; i++) {
			id = tab[i];
			if (id < 0) {
				for (int j = 0; j < 8; j++) {
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

}

void Recrystalization::fill_no_recrystalization_list(std::vector<cell>* list) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (cells[i][j].energy > 0) {
				list->push_back(cells[i][j]);
			}
		}
	}
}

void Recrystalization::randomRecGrains() {
	srand(time(NULL));
	for (int i = 1; i <= RECRYSTALIZATION_GRAINS; i++) {
		int x = rand() % HEIGHT;
		int y = rand() % WIDTH;
		if (mc.is_on_the_board(x, y, cells)) {
			cells[x][y].id=-i;
			cells[x][y].energy=0;
			recrystalizationList.push_back(cells[x][y]);
		} else {
			i--;
		}
	}
}
