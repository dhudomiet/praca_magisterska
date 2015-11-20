#pragma once
#ifndef EXECUTERECT_H
#define EXECUTERECT_H

#include "Task.h"
#include "constans.h"

class ExecuteRec : public Task
{
public:
	ExecuteRec(void);
	ExecuteRec(int begin, int end, vector<cell> *noRect, vector<cell> *vect, cell** cells, cell** oldstate);
	~ExecuteRec(void);
	void start();
	void execute();
	void cal_energy(int idx_i, int idx_j, int * point, cell** space_of_cells);
	void toString();

private:
	int begin, end;
	cell** cells;
	cell** oldstate;
	vector<cell> *vect;
	vector<cell> *noRect;
};

#endif

