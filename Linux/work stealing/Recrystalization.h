/*
 * Recrystalization.h
 *
 *  Created on: Aug 23, 2015
 *      Author: damian
 */

#ifndef RECRYSTALIZATION_H_
#define RECRYSTALIZATION_H_
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include "MonteCarlo.h"
#include "InitializeEnergy.h"
#include "FillNoRecList.h"
#include "ExecuteRec.h"

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
	void saveToFile();
private:
	cell** cells;
	cell** oldstate;
	MonteCarlo mc;
	vector<cell> recrystalizationList;
	Manager* manager;
	long duraction;

};



#endif /* RECRYSTALIZATION_H_ */
