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
#include "WorkStealingManager.h"
#include "BusyLeafsManager.h"
#include "Manager.h"

class MonteCarlo {
public:
	MonteCarlo();
	~MonteCarlo();
	void initialize_ids();
	void draw_space();
	void cal_energy(int idx_i, int idx_j,int * point, cell** space_of_cells);
	void monte_carlo_algorithm();
	void fill_list(vector<cell> *vect, cell** space);
	void executeList(vector<cell> *list, cell** cells, cell** oldstate);
	void copy_spaces(cell** space, cell** source_space);
	void calculate_energy();
	void draw_energy();
	void initializeCores();
	void set_cells(cell** cells);
	void clean(vector<cell> *vect);
	Manager* getManager();
	cell** cells;
	cell** oldstate;
private:
	Manager* manager;
	//BusyLeafsManager* manager;
};

#endif
