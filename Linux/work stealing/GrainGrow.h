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
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "constans.h"
#include "Manager.h"
#include "WorkStealingManager.h"
#include "BusyLeafsManager.h"

typedef boost::posix_time::ptime Time;
typedef boost::posix_time::time_duration TimeDuraction;

class Grain_grow {
public:
	Grain_grow();
	~Grain_grow();
	void initialize_space();
	void copySpaces(int** space, int** source_space);
	void executeGrainGrow(int** space, int** old_space);
	void drawSpace();
	void grainGrowAlgorithm();
	bool isFillAll();
	void saveToFile();

private:
	int** space_of_cells;
	int** old_space;
	Manager* manager;
	long duraction;
};

#endif /* GRAINGROW_H_ */
