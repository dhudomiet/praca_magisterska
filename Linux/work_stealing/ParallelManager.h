/*
 * ParallelManager.h
 *
 *  Created on: Dec 13, 2015
 *      Author: damian
 */

#ifndef PARALLELMANAGER_H_
#define PARALLELMANAGER_H_

#include "InitializeIds.h"
#include "CalculateEnergy.h"
#include "ExecuteList.h"
#include "FillList.h"
#include "CopySpaces.h"
#include "InitializeEnergy.h"
#include "ExecuteRec.h"
#include "FillNoRecList.h"
#include "InitializeSpace.h"
#include "CopyGrows.h"
#include "ExecuteGrainGrow.h"
#include "Manager.h"
#include "Parallel.h"
#include <boost/date_time/posix_time/posix_time.hpp>

typedef boost::posix_time::ptime Time;
typedef boost::posix_time::time_duration TimeDuraction;

class ParallelManager : public Manager {
public:
	ParallelManager();
	ParallelManager(int cores);
	virtual ~ParallelManager();
	void run();
	void initializeIds(cell** cells);
	void initializeSpace(int** space);
	void calculateEnergy(cell** cells);
	void executeList(vector<cell*> *list, cell** cells, cell** oldstate);
	void fillList(vector<cell*> *vect, cell** space);
	void copySpaces(cell** space, cell** source_space);
	void copyGrows(int** space, int** source);
	void initializeEnergy(cell** cells);
	void executeRec(vector<cell> *noRect, vector<cell> *rect, cell** cells, cell** oldstate);
	void fillNoRectList(vector<cell> *list, cell** cells);
	void executeGrainGrow(int** space, int** old_space);
	void join_all();
	int getDuraction();
	int calculateHeightForTask();
	int calculateWidthForTask();
	int calculateTasksForThread();
private:
	Parallel* cores;
	int CORES;
	int duraction;
	int threadsTime;
};

#endif /* PARALLELMANAGER_H_ */
