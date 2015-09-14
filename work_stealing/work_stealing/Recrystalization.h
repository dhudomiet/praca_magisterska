/*
 * Recrystalization.h
 *
 *  Created on: Aug 23, 2015
 *      Author: damian
 */
/*
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
	bool is_on_the_board(int idx_i, int idx_j, Cell (&space_of_cells)[HEIGHT][WIDTH]);
	void cal_energy(int idx_i, int idx_j,int * point, Cell (&space_of_cells)[HEIGHT][WIDTH]);
	void fill_no_recrystalization_list(std::vector<Cell> *list);
	void randomRecGrains();
	void draw_data();
private:
	Cell cells[HEIGHT][WIDTH];
	MonteCarlo mc;
	std::vector<Cell> recrystalizationList;

};



#endif /* RECRYSTALIZATION_H_ */
*/