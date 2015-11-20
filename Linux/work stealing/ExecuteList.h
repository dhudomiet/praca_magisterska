#pragma once
#ifndef EXECUTELIST_H
#define EXECUTELIST_H

#include "Task.h"
#include "constans.h"
#include <concurrent_vector.h>

using namespace concurrency;
class ExecuteList : public Task
{
public:
	ExecuteList(void);
	ExecuteList(int begin,int end,concurrent_vector<cell*> *vect, cell** cells, cell** oldstate);
	~ExecuteList(void);
	void start();
	void execute();
	void cal_energy(int idx_i, int idx_j,int * point, cell** space_of_cells);
	void toString();
private:
	int begin,end;
	concurrent_vector<cell*> *vect;
	cell** cells;
	cell** oldstate;
};
#endif
