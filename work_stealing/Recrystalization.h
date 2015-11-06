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
#include "InitializeEnergy.h"
#include "FillNoRecList.h"
#include "ExecuteRec.h"

using namespace concurrency;

class Recrystalization {
public:
	Recrystalization();
	~Recrystalization();
	void recrystalization_algorithm();
	void initializeSpace();
	void initializeEnergy();
	void cal_energy(int idx_i, int idx_j,int * point, cell** space_of_cells);
	void fill_no_recrystalization_list(vector<cell> *list);
	void executeRec(vector<cell>* noRect, vector<cell> *rect);
	bool is_on_the_board(int idx_i, int idx_j, cell** space_of_cells);
	void randomRecGrains();
	void draw_data();
	void draw_energy();
	void clean(vector<cell> *vect);
private:
	cell** cells;
	cell** oldstate;
	MonteCarlo mc;
	vector<cell> recrystalizationList;
	Manager* manager;
	//BusyLeafsManager* manager;

};



#endif /* RECRYSTALIZATION_H_ */
