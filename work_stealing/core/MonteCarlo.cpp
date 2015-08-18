/*
 * MonteCarlo.cpp
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#include "MonteCarlo.h"

MonteCarlo::MonteCarlo() {
	// TODO Auto-generated constructor stub

}

MonteCarlo::~MonteCarlo() {
	// TODO Auto-generated destructor stub
}

void MonteCarlo::initialize_ids() {
	srand(time(NULL));
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			cells[i][j].set_id(rand() % NUMBER_OF_IDS);
			cells[i][j].set_idx_i(i);
			cells[i][j].set_idx_j(j);
			cells[i][j].set_flag(true);
		}
	}
}

void MonteCarlo::calculate_energy() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			cells[i][j].set_energy(
					cal_energy(i, j, cells[i][j].get_id(), cells));
		}
	}
}

void MonteCarlo::cal_energy(int idx_i, int idx_j, int * point,
		Cell (*space_of_cells)[WIDTH]) {
	srand(time(NULL));
	if (idx_i == 0 && idx_j == 0) {
		int tab[3];
		int k = 0;
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == 0 && j == 0)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}

		int energy = 0;
		int id = -1;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].get_id()) {
				for (int j = 0; j < 3; j++) {
					if (tab[j] != id) {
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

	} else if (idx_i == 0 && idx_j == WIDTH - 1) {
		int tab[3];
		int k = 0;
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].get_id()) {
				for (int i = 0; i < 3; i++) {
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
	} else if (idx_i == HEIGHT - 1 && idx_j == 0) {
		int tab[3];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].get_id()) {
				for (int i = 0; i < 3; i++) {
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
	} else if (idx_i == HEIGHT - 1 && idx_j == WIDTH - 1) {
		int tab[3];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].get_id()) {
				for (int i = 0; i < 3; i++) {
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
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == 0) {
		int tab[5];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].get_id()) {
				for (int i = 0; i < 5; i++) {
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
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == WIDTH - 1) {
		int tab[5];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].get_id()) {
				for (int i = 0; i < 5; i++) {
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
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == 0) {
		int tab[5];
		int k = 0;
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].get_id()) {
				for (int i = 0; i < 5; i++) {
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
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == HEIGHT - 1) {
		int tab[5];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].get_id()) {
				for (int i = 0; i < 5; i++) {
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
	} else {
		int tab[8];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 8; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].get_id()) {
				for (int i = 0; i < 8; i++) {
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
	}

}

int MonteCarlo::cal_energy(int idx_i, int idx_j, int id,
		Cell (*space_of_cells)[WIDTH]) {
	srand(time(NULL));
	if (idx_i == 0 && idx_j == 0) {
		int tab[3];
		int k = 0;
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == 0 && j == 0)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		for (int i = 0; i < 3; i++) {
			if (tab[i] != id) {
				energy++;
			}
		}
		return energy;
	} else if (idx_i == 0 && idx_j == WIDTH - 1) {
		int tab[3];
		int k = 0;
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		for (int i = 0; i < 3; i++) {
			if (tab[i] != id) {
				energy++;
			}
		}
		return energy;
	} else if (idx_i == HEIGHT - 1 && idx_j == 0) {
		int tab[3];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		for (int i = 0; i < 3; i++) {
			if (tab[i] != id) {
				energy++;
			}
		}
		return energy;
	} else if (idx_i == HEIGHT - 1 && idx_j == WIDTH - 1) {
		int tab[3];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		for (int i = 0; i < 3; i++) {
			if (tab[i] != id) {
				energy++;
			}
		}
		return energy;
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == 0) {
		int tab[5];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		for (int i = 0; i < 5; i++) {
			if (tab[i] != id) {
				energy++;
			}
		}
		return energy;
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == WIDTH - 1) {
		int tab[5];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		for (int i = 0; i < 5; i++) {
			if (tab[i] != id) {
				energy++;
			}
		}
		return energy;
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == 0) {
		int tab[5];
		int k = 0;
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		for (int i = 0; i < 5; i++) {
			if (tab[i] != id) {
				energy++;
			}
		}
		return energy;
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == HEIGHT - 1) {
		int tab[5];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
				k++;
			}
		}
		int energy = 0;
		for (int i = 0; i < 5; i++) {
			if (tab[i] != id) {
				energy++;
			}
		}
		return energy;
	} else {
		int tab[8];
		int k = 0;
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				tab[k] = space_of_cells[i][j].get_id();
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

}

void MonteCarlo::monte_carlo_algorithm() {
	initialize_ids();
	calculate_energy();
	draw_space();
	std::vector<Cell> listCells;
	copy_spaces(oldstate, cells);
	srand(time(NULL));
	for (int i = 0; i < 200; i++) {
		fill_list(&listCells, cells);
		while (listCells.size() > 0) {
			int number = rand() % listCells.size();
			Cell data = listCells.at(number);
			listCells.erase(listCells.begin() + number - 1);
			int tab[2];
			int *p = tab;
			cal_energy(data.get_idx_i(), data.get_idx_j(), p, oldstate);
			if (p[0] == -1) {
				continue;
			}
			int delta = p[1] - data.get_energy();
			if (delta <= 0) {
				cells[data.get_idx_i()][data.get_idx_j()].set_id(p[0]);
				cells[data.get_idx_i()][data.get_idx_j()].set_energy(p[1]);
			}
		}
		copy_spaces(oldstate, cells);
		draw_space();
		std::cout << std::endl;
		std::cout << std::endl;
	}

}

void MonteCarlo::fill_list(std::vector<Cell> *vect, Cell (*space)[WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (is_on_the_board(i, j, space)) {
				vect->push_back(space[i][j]);
			}
		}
	}
}

bool MonteCarlo::is_on_the_board(int idx_i, int idx_j,
		Cell (*space_of_cells)[WIDTH]) {
	if (idx_i == 0 && idx_j == 0) {
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == 0 && j == 0)
					continue;
				if (space_of_cells[i][j].get_id()
						!= space_of_cells[idx_i][idx_j].get_id()) {
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
				if (space_of_cells[i][j].get_id()
						!= space_of_cells[idx_i][idx_j].get_id()) {
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
				if (space_of_cells[i][j].get_id()
						!= space_of_cells[idx_i][idx_j].get_id()) {
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
				if (space_of_cells[i][j].get_id()
						!= space_of_cells[idx_i][idx_j].get_id()) {
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
				if (space_of_cells[i][j].get_id()
						!= space_of_cells[idx_i][idx_j].get_id()) {
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
				if (space_of_cells[i][j].get_id()
						!= space_of_cells[idx_i][idx_j].get_id()) {
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
				if (space_of_cells[i][j].get_id()
						!= space_of_cells[idx_i][idx_j].get_id()) {
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
				if (space_of_cells[i][j].get_id()
						!= space_of_cells[idx_i][idx_j].get_id()) {
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
				if (space_of_cells[i][j].get_id()
						!= space_of_cells[idx_i][idx_j].get_id()) {
					return true;
				}
			}
		}
		return false;
	}

}

void MonteCarlo::draw_space() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << cells[i][j].get_id() << " ";
		}
		std::cout << std::endl;
	}
}

void MonteCarlo::draw_energy() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << cells[i][j].get_energy() << " ";
		}
		std::cout << std::endl;
	}
}

void MonteCarlo::copy_spaces(Cell (*space)[WIDTH],
		Cell (*source_space)[WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			space[i][j] = source_space[i][j];
		}
	}

}
