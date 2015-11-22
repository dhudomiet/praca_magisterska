/*
 * Graingrow.cpp
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#include "GrainGrow.h"

Grain_grow::Grain_grow() {
	// TODO Auto-generated constructor stub

}

Grain_grow::~Grain_grow() {
	// TODO Auto-generated destructor stub
}

void Grain_grow::initialize_space() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			space_of_cells[i][j] = 0;
		}
	}
	srand(time(NULL));
	for (int i = 0; i < NUMBER_OF_GRAINS; i++) {
		space_of_cells[rand() % HEIGHT][rand() % WIDTH] = i;
	}
}

void Grain_grow::copy_spaces(int (*space)[WIDTH], int (*source_space)[WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			space[i][j] = source_space[i][j];
		}
	}

}

bool Grain_grow::is_neighbor(int idx_i, int idx_j, int *tab, int (*space_of_cells)[WIDTH]) {
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

void Grain_grow::draw_space() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout<<space_of_cells[i][j];
		}
		std::cout<<std::endl;
	}
}

void Grain_grow::grain_grow_algorithm() {

	int count = NUMBER_OF_GRAINS;
	while (count < WIDTH * HEIGHT) {
		copy_spaces(old_space, space_of_cells);
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (space_of_cells[i][j] == 0) {
					int tab[2];
					if (is_neighbor(i, j, tab, old_space)) {
						space_of_cells[i][j] = old_space[tab[0]][tab[1]];
					}
				}
			}
		}
		count++;
		std::cout<<std::endl;
		draw_space();
	}

}


