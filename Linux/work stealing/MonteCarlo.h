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
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "constans.h"
#include "WorkStealingManager.h"
#include "BusyLeafsManager.h"
#include "Manager.h"

typedef boost::posix_time::ptime Time;
typedef boost::posix_time::time_duration TimeDuraction;

class MonteCarlo {
public:
	MonteCarlo();
	~MonteCarlo();
	void initializeIds();
	void drawSpace();
	void calEnergy(int idx_i, int idx_j,int * point, cell** space_of_cells);
	void monteCarloAlgorithm();
	void fillList(vector<cell*> *vect, cell** space);
	void executeList(vector<cell*> *list, cell** cells, cell** oldstate);
	void copySpaces(cell** space, cell** source_space);
	void calculateEnergy();
	void drawEnergy();
	void initializeCores();
	void setCells(cell** cells);
	void clean(vector<cell> *vect);
	void saveToFile();
	Manager* getManager();
	cell** cells;
	cell** oldstate;
private:
	Manager* manager;
	long duraction;
};

#endif
