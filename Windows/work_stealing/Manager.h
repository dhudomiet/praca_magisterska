#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "constans.h"
#include <boost\thread.hpp>
#include <vector>
#include <concurrent_vector.h>

using namespace std;
using namespace concurrency;

class Manager
{
public:
	virtual ~Manager(){};
	virtual void run()=0;
	virtual void initializeIds(cell** cells)=0;
	virtual void initializeSpace(int** space)=0;
	virtual void calculateEnergy(cell** cells)=0;
	virtual void executeList(concurrent_vector<cell*> *list, cell** cells, cell** oldstate)=0;
	virtual void fillList(concurrent_vector<cell*> *vect, cell** space)=0;
	virtual void copySpaces(cell** space, cell** source_space)=0;
	virtual void copyGrows(int** space, int** source)=0;
	virtual void initializeEnergy(cell** cells)=0;
	virtual void executeRec(vector<cell> *noRect, vector<cell> *rect, cell** cells, cell** oldstate)=0;
	virtual void fillNoRectList(vector<cell> *list, cell** cells)=0;
	virtual void executeGrainGrow(int** space, int** old_space)=0;

protected:
	boost::thread_group group;
};

#endif

