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
#include "constans.h"

class MonteCarlo {
public:
	MonteCarlo();
	MonteCarlo(Cell cells[HEIGHT][WIDTH]);
	virtual ~MonteCarlo();
	void initialize_ids();
	void cal_energy(int idx_i, int idx_j,int * point, Cell (&space_of_cells)[HEIGHT][WIDTH]);
	int cal_energy(int idx_i, int idx_j,int id, Cell (&space_of_cells)[HEIGHT][WIDTH]);
	void monte_carlo_algorithm();
	void fill_list(std::vector<Cell> *vect, Cell (&space)[HEIGHT][WIDTH]);
	bool is_on_the_board(int idx_i, int idx_j, Cell (&space_of_cells)[HEIGHT][WIDTH]);
	void copy_spaces(Cell (&space)[HEIGHT][WIDTH], Cell (&source_space)[HEIGHT][WIDTH]);
	void calculate_energy();
	void draw_space();
	void draw_energy();
	void set_cells(Cell (&cells)[HEIGHT][WIDTH]);
private:
	Cell cells[HEIGHT][WIDTH];
	Cell oldstate[HEIGHT][WIDTH];
};

#endif /* MONTECARLO_H_ */
