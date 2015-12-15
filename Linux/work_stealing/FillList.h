#pragma once
#ifndef FILLLIST_H
#define FILLLIST_H

#include "Task.h"
#include "constans.h"
#include <vector>
#include <boost/thread.hpp>

class FillList : public Task
{
public:
	FillList(void);
	FillList(int params[4], vector<cell*> *vect, cell** cells);
	~FillList(void);
	void start();
	void execute();
	bool is_on_the_board(int idx_i, int idx_j, cell** space_of_cells);
	void toString();
private:
	int params[4];
	vector<cell*> *vect;
	cell** cells;
	static boost::mutex mut;
};

#endif
