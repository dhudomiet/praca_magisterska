#pragma once
#ifndef BUSYLEAFSMANAGER_H
#define BUSYLEAFSMANAGER_H

#include "BusyLeafs.h"
#include "InitializeIds.h"
#include "CalculateEnergy.h"
#include "ExecuteList.h"
#include "FillList.h"
#include "CopySpaces.h"
#include "InitializeEnergy.h"
#include "ExecuteRec.h"
#include "FillNoRecList.h"
#include "constans.h"

class BusyLeafsManager
{
public:
	BusyLeafsManager(void);
	~BusyLeafsManager(void);
	void run();
	void initializeIds(cell** cells);
	void calculateEnergy(cell** cells);
	void executeList(vector<cell> *list, cell** cells, cell** oldstate);
	void fillList(vector<cell> *vect, cell** space);
	void copySpaces(cell** space, cell** source_space);
	void initializeEnergy(cell** cells);
	void executeRec(vector<cell> *noRect, vector<cell> *rect, cell** cells, cell** oldstate);
	void fillNoRectList(vector<cell> *list, cell** cells);
private:
	BusyLeafs* cores;
	boost::thread_group group;

};

#endif

