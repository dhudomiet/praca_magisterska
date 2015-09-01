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
	std::vector<Cell> noRecrystalizationCells;
	randomRecGrains();
	fill_no_recrystalization_list(&noRecrystalizationCells);
	for (int i = 0; i < 1000; i++) {
		srand(time(NULL));
		while (noRecrystalizationCells.size() > 0) {
			int number = rand() % noRecrystalizationCells.size();
			Cell grain = noRecrystalizationCells.at(number);
			int era = number - 1;
			if(era<0){
				era = 0;
			}
			noRecrystalizationCells.erase(
					noRecrystalizationCells.begin() + era);
			int tab[2];
			std::cout << grain.get_idx_i() << " " << grain.get_idx_j() << " ";
			int *p = tab;
			cal_energy(grain.get_idx_i(), grain.get_idx_j(), p, cells);
			std::cout << "id and energy: " << " " << p[0] << " " << p[1]
					<< std::endl;
			if (p[0] < 0) {
				int energy = 0;
				energy = p[1] + H;
				int energyRec =
						cells[grain.get_idx_i()][grain.get_idx_j()].get_energy()
								+ energy;
				energy =
						cells[grain.get_idx_i()][grain.get_idx_j()].get_energy();
				if (energyRec > energy) {
					cells[grain.get_idx_i()][grain.get_idx_j()].set_energy(0);
					cells[grain.get_idx_i()][grain.get_idx_j()].set_id(p[0]);
					recrystalizationList.push_back(
							cells[grain.get_idx_i()][grain.get_idx_j()]);
				}

			}
		}
		fill_no_recrystalization_list(&noRecrystalizationCells);
		if (noRecrystalizationCells.size() == 0) {
			break;
		}
	}
	MonteCarlo mc(this->cells);
	mc.monte_carlo_algorithm();

	//draw_data();
}

void Recrystalization::draw_data() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << cells[i][j].get_id() << " ";
		}
		std::cout << std::endl;
	}
}

void Recrystalization::initializeSpace() {
	mc.monte_carlo_algorithm();
	mc.set_cells(cells);
	initializeEnergy();

}

void Recrystalization::initializeEnergy() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (is_on_the_board(i, j, cells)) {
				cells[i][j].set_energy(ENERGY_ON_THE_BOARD);
			} else {
				cells[i][j].set_energy(ENERGY_ON_GRAIN);
			}
		}
		std::cout << std::endl;
	}
}

bool Recrystalization::is_on_the_board(int idx_i, int idx_j,
		Cell (&space_of_cells)[HEIGHT][WIDTH]) {
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

void Recrystalization::cal_energy(int idx_i, int idx_j, int * point,
		Cell (&space_of_cells)[HEIGHT][WIDTH]) {
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
				tab[k] = space_of_cells[i][j].get_id();
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
				tab[k] = space_of_cells[i][j].get_id();
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
				tab[k] = space_of_cells[i][j].get_id();
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
				tab[k] = space_of_cells[i][j].get_id();
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
				tab[k] = space_of_cells[i][j].get_id();
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
				tab[k] = space_of_cells[i][j].get_id();
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
				tab[k] = space_of_cells[i][j].get_id();
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
				tab[k] = space_of_cells[i][j].get_id();
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

void Recrystalization::fill_no_recrystalization_list(std::vector<Cell>* list) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (cells[i][j].get_energy() > 0) {
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
		if (is_on_the_board(x, y, cells)) {
			cells[x][y].set_id(-i);
			cells[x][y].set_energy(0);
			recrystalizationList.push_back(cells[x][y]);
		} else {
			i--;
		}
	}
}
