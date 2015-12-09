/*
 * MonteCarlo.h
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#ifndef MONTECARLO_H_
#define MONTECARLO_H_
typedef struct {
	int id;
	int idx_i;
	int idx_j;
	bool flag;
	int energy;
}cell;

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
	MonteCarlo(cell cells[HEIGHT][WIDTH]);
	virtual ~MonteCarlo();
	void initialize_ids();
	void cal_energy(int idx_i, int idx_j,int * point, cell** space_of_cells);
	int cal_energy(int idx_i, int idx_j,int id, cell** space_of_cells);
	void monte_carlo_algorithm();
	void fill_list(std::vector<cell> *vect, cell** space);
	bool is_on_the_board(int idx_i, int idx_j, cell** space_of_cells);
	void copy_spaces(cell** space, cell** source_space);
	void calculate_energy();
	void draw_space();
	void draw_energy();
	void set_cells(cell** cells);
	cell **cells;
	cell** oldstate;
private:

};

#endif /* MONTECARLO_H_ */
