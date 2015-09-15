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

MonteCarlo::~MonteCarlo() {
	
}

void MonteCarlo::initialize_ids() {
	logg("initialize ids...");
	srand(time(NULL));
	oldstate = new cell*[HEIGHT];
	cells = new cell*[HEIGHT];
	for (int i = 0; i < HEIGHT; i++) {
		oldstate[i] = new cell[WIDTH];
		cells[i] = new cell[WIDTH];
		for (int j = 0; j < WIDTH; j++) {
			cells[i][j].id = rand() % NUMBER_OF_IDS + 1;
			cells[i][j].idx_i = i;
			cells[i][j].idx_j = j;
			cells[i][j].flag = true;
		}
	}
}

void MonteCarlo::calculate_energy() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			cells[i][j].energy = cal_energy(i, j, cells[i][j].id, cells);
		}
	}
}

void MonteCarlo::cal_energy(int idx_i, int idx_j, int * point,cell** space_of_cells) {
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
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].id) {
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
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].id) {
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
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].id) {
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
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 3; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].id) {
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
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].id) {
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
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].id) {
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
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].id) {
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
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 5; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].id) {
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
				tab[k] = space_of_cells[i][j].id;
				k++;
			}
		}
		int energy = 0;
		int id = -1;
		for (int i = 0; i < 8; i++) {
			id = tab[i];
			if (id != space_of_cells[idx_i][idx_j].id) {
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
										   tab[k] = space_of_cells[i][j].id;
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
										   tab[k] = space_of_cells[i][j].id;
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
										   tab[k] = space_of_cells[i][j].id;
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
										   tab[k] = space_of_cells[i][j].id;
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
										   tab[k] = space_of_cells[i][j].id;
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
										   tab[k] = space_of_cells[i][j].id;
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
										   tab[k] = space_of_cells[i][j].id;
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
										   tab[k] = space_of_cells[i][j].id;
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
	clock_t start, stop;
	logg("start execution monteCarlo algorithm...");
	start = clock();
	calculate_energy();
	std::vector<cell> listCells;
	copy_spaces(oldstate, cells);
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		fill_list(&listCells, cells);
		int size = listCells.size();
		while (size > 0) {
			int number = rand() % size;
			cell data = listCells.at(number);
			int er = number - 1;
			if (er < 0) {
				er = 0;
			}
			listCells.erase(listCells.begin() + (er));
			int tab[2];
			int *p = tab;
			cal_energy(data.idx_i, data.idx_j, p, oldstate);
			if (p[0] == -1) {
				continue;
			}
			int delta = p[1] - data.energy;
			if (delta <= 0) {
				cells[data.idx_i][data.idx_j].id = p[0];
				cells[data.idx_i][data.idx_j].energy = p[1];
			}
			size = listCells.size();
		}
		copy_spaces(oldstate, cells);
	}
	stop = clock();
	float time = (float) stop - (float) start;
	loggTime("time execution of monteCarlo algorithm: ", time);
	draw_space();

}

void MonteCarlo::fill_list(std::vector<cell> *vect,
						   cell** space) {
							   for (int i = 0; i < HEIGHT; i++) {
								   for (int j = 0; j < WIDTH; j++) {
									   if (is_on_the_board(i, j, space)) {
										   vect->push_back(space[i][j]);
									   }
								   }
							   }
}

bool MonteCarlo::is_on_the_board(int idx_i, int idx_j,
								 cell** space_of_cells) {
									 if (idx_i == 0 && idx_j == 0) {
										 for (int i = idx_i; i < idx_i + 2; i++) {
											 for (int j = idx_j; j < idx_j + 2; j++) {
												 if (i == 0 && j == 0)
													 continue;
												 if (space_of_cells[i][j].id
													 != space_of_cells[idx_i][idx_j].id) {
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
												 if (space_of_cells[i][j].id
													 != space_of_cells[idx_i][idx_j].id) {
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
												 if (space_of_cells[i][j].id
													 != space_of_cells[idx_i][idx_j].id) {
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
												 if (space_of_cells[i][j].id
													 != space_of_cells[idx_i][idx_j].id) {
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
												 if (space_of_cells[i][j].id
													 != space_of_cells[idx_i][idx_j].id) {
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
												 if (space_of_cells[i][j].id
													 != space_of_cells[idx_i][idx_j].id) {
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
												 if (space_of_cells[i][j].id
													 != space_of_cells[idx_i][idx_j].id) {
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
												 if (space_of_cells[i][j].id
													 != space_of_cells[idx_i][idx_j].id) {
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
												 if (space_of_cells[i][j].id
													 != space_of_cells[idx_i][idx_j].id) {
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
			std::cout << cells[i][j].id << " ";
		}
		std::cout << std::endl;
	}
}

void MonteCarlo::draw_energy() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << cells[i][j].energy << " ";
		}
		std::cout << std::endl;
	}
}

void MonteCarlo::copy_spaces(cell** space,
							 cell** source_space) {
								 for (int i = 0; i < HEIGHT; i++) {
									 for (int j = 0; j < WIDTH; j++) {
										 space[i][j] = source_space[i][j];
									 }
								 }
}

MonteCarlo::MonteCarlo(cell cells[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			this->cells[i][j] = cells[i][j];
		}
	}
}

void MonteCarlo::set_cells(cell** cells) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			cells[i][j].id = this->cells[i][j].id;
			cells[i][j].idx_i = this->cells[i][j].idx_i;
			cells[i][j].idx_j = this->cells[i][j].idx_j;
			cells[i][j].energy = this->cells[i][j].energy;
			cells[i][j].flag = this->cells[i][j].flag;
		}
	}

}
