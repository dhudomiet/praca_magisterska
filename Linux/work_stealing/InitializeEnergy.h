#pragma once
#ifndef INITIALIZENERGY_H
#define INITIALIZENERGY_H

#include "Task.h"
#include "constans.h"

class InitializeEnergy : public Task
{
public:
	InitializeEnergy(void);
	InitializeEnergy(int params[4], cell** cells);
	~InitializeEnergy(void);
	void start();
	void execute();
	bool is_on_the_board(int idx_i, int idx_j, cell** space_of_cells);
	void toString();

private:
	int params[4];
	cell** cells;
};

#endif
