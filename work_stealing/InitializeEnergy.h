#pragma once
#ifndef INITIALIZENERGY_H
#define INITIALIZENERGY_H

#include "Task.h"
#include "constans.h"

class InitializeEnergy : public Task
{
public:
	InitializeEnergy(void);
	InitializeEnergy(int begin, int end, cell** cells);
	~InitializeEnergy(void);
	void start();
	void execute();
	bool is_on_the_board(int idx_i, int idx_j, cell** space_of_cells);

private:
	int begin, end;
	cell** cells;
};

#endif
