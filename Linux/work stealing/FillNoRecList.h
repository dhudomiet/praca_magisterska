#pragma once
#ifndef FILLNORECTLIST_H
#define FILLNORECTLIST_H

#include "Task.h"
#include "constans.h"
#include <vector>
#include <boost/thread.hpp>

class FillNoRecList : public Task
{
public:
	FillNoRecList(void);
	FillNoRecList(int params[4], vector<cell> *vect, cell** cells);
	~FillNoRecList(void);
	void start();
	void execute();
	void toString();

private:
	int params[4];
	cell** cells;
	vector<cell> *vect;
	static boost::mutex mut;
};

#endif

