/*
 * MonteCarlo.h
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#ifndef MONTECARLO_H_
#define MONTECARLO_H_

#include <iostream>
#include <ppl.h>
#include <vector>
#include <concurrent_vector.h>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "constans.h"

typedef struct {
	int id;
	int idx_i;
	int idx_j;
	bool flag;
	int energy;
}cell;

using namespace concurrency;
class MonteCarlo {
public:
	MonteCarlo();
	MonteCarlo(concurrent_vector<cell*> cells);
	void initialize_ids();
	void draw_space();
	void cal_energy(int idx_i, int idx_j,int * point, concurrent_vector<cell*> space_of_cells);
	int cal_energy(int idx_i, int idx_j,int id, concurrent_vector<cell*> space_of_cells);
	void monte_carlo_algorithm();
	void fill_list(concurrent_vector<cell> *vect, concurrent_vector<cell*> space);
	bool is_on_the_board(int idx_i, int idx_j, concurrent_vector<cell*> space_of_cells);
	void copy_spaces(concurrent_vector<cell*> space, concurrent_vector<cell*> source_space);
	void calculate_energy();
	
	void draw_energy();
	void set_cells(concurrent_vector<cell*> cells);
	concurrent_vector<cell*> cells;
	concurrent_vector<cell*> oldstate;
private:

};

#endif /* MONTECARLO_H_ */
