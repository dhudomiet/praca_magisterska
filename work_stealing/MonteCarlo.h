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
#include "constans.h"
#include "WorkStealing.h"
#include "InitializeIds.h"

class MonteCarlo {
public:
	MonteCarlo();
	MonteCarlo(cell** cells);
	void initialize_ids();
	void draw_space();
	void cal_energy(int idx_i, int idx_j,int * point, cell** space_of_cells);
	int cal_energy(int idx_i, int idx_j,int id, cell** space_of_cells);
	void monte_carlo_algorithm();
	void fill_list(cell** vect, cell** space);
	bool is_on_the_board(int idx_i, int idx_j, cell** space_of_cells);
	void copy_spaces(cell** space, cell** source_space);
	void calculate_energy();
	
	void draw_energy();
	void set_cells(cell** cells);
	cell** cells;
	cell** oldstate;
private:
	//static deque<WorkStealing*> cores;
	static int cores;

};

#endif /* MONTECARLO_H_ */
