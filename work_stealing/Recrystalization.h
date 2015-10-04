/*
 * Recrystalization.h
 *
 *  Created on: Aug 23, 2015
 *      Author: damian
 */

#ifndef RECRYSTALIZATION_H_
#define RECRYSTALIZATION_H_
#include <ppl.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "MonteCarlo.h"

using namespace concurrency;

class Recrystalization {
public:
	Recrystalization();
	/*
	void recrystalization_algorithm();
	void initializeSpace();
	void initializeEnergy();
	void cal_energy(int idx_i, int idx_j,int * point, concurrent_vector<cell*> *space_of_cells);
	void fill_no_recrystalization_list(concurrent_vector<cell> *list);
	void randomRecGrains();
	void draw_data();
private:
	concurrent_vector<cell*> cells;
	MonteCarlo mc;
	concurrent_vector<cell> recrystalizationList;
	*/
};



#endif /* RECRYSTALIZATION_H_ */
