/*
 * MonteCarlo.h
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#ifndef MONTECARLO_H_
#define MONTECARLO_H_

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Cell.h"

#define HEIGHT 10
#define WIDTH 10
#define NUMBER_OF_IDS 5

class MonteCarlo {
public:
	MonteCarlo();
	virtual ~MonteCarlo();
	void initialize_ids();
	int* cal_energy(int idx_i, int idx_j, Cell (*space_of_cells)[WIDTH]);
	int cal_energy(int idx_i, int idx_j,int id, Cell (*space_of_cells)[WIDTH]);
	void monte_carlo_algorithm();
	void fill_list(std::vector<Cell> *vect, Cell (*space)[WIDTH]);
	bool is_on_the_board(int idx_i, int idx_j, Cell (*space_of_cells)[WIDTH]);
	void copy_spaces(Cell (*space)[WIDTH], Cell (*source_space)[WIDTH]);
	void calculate_energy();
	void draw_space();
private:
	Cell cells[HEIGHT][WIDTH];
	Cell oldstate[HEIGHT][WIDTH];
};;

#endif /* MONTECARLO_H_ */
