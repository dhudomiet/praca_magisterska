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
#include "InitializeSpace.h"
#include "CopyGrows.h"
#include "ExecuteGrainGrow.h"
#include "Manager.h"

class BusyLeafsManager : public Manager
{
public:
	BusyLeafsManager(void);
	~BusyLeafsManager(void);
	void run();
	void initializeIds(cell** cells);
	void initializeSpace(int** space);
	void calculateEnergy(cell** cells);
	void executeList(concurrent_vector<cell*> *list, cell** cells, cell** oldstate);
	void fillList(concurrent_vector<cell*> *vect, cell** space);
	void copySpaces(cell** space, cell** source_space);
	void copyGrows(int** space, int** source);
	void initializeEnergy(cell** cells);
	void executeRec(vector<cell> *noRect, vector<cell> *rect, cell** cells, cell** oldstate);
	void fillNoRectList(vector<cell> *list, cell** cells);
	void executeGrainGrow(int** space, int** old_space);
private:
	BusyLeafs* cores;

};

#endif

