/*
 * Graingrow.h
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#ifndef GRAINGROW_H_
#define GRAINGROW_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include "constans.h"
#include "Manager.h"
#include "WorkStealingManager.h"
#include "BusyLeafsManager.h"

class Grain_grow {
public:
	Grain_grow();
	~Grain_grow();
	void initialize_space();
	void copy_spaces(int** space, int** source_space);
	void executeGrainGrow(int** space, int** old_space);
	void draw_space();
	void grain_grow_algorithm();
	bool is_fill_all();

private:
	int** space_of_cells;
	int** old_space;
	Manager* manager;
};

#endif /* GRAINGROW_H_ */
