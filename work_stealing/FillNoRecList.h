#pragma once
#ifndef FILLNORECTLIST_H
#define FILLNORECTLIST_H

#include "Task.h"
#include "constans.h"

class FillNoRecList : public Task
{
public:
	FillNoRecList(void);
	FillNoRecList(int begin, int end, vector<cell> *vect, cell** cells);
	~FillNoRecList(void);
	void start();
	void execute();

private:
	int begin, end;
	cell** cells;
	vector<cell> *vect;
};

#endif

