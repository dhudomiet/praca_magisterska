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
#include <stdlib.h>
#include <time.h>
#include "Cell.h"
#include "MonteCarlo.h"
#include "constans.h"



class Recrystalization {
public:
	Recrystalization();
	void recrystalization_algorithm();
	void initializeSpace();
	void initializeEnergy();
	void cal_energy(int idx_i, int idx_j,int * point, cell** space_of_cells);
	void fill_no_recrystalization_list(std::vector<cell> *list);
	void randomRecGrains();
	void draw_data();
private:
	cell** cells;
	MonteCarlo mc;
	std::vector<cell> recrystalizationList;

};



#endif /* RECRYSTALIZATION_H_ */
