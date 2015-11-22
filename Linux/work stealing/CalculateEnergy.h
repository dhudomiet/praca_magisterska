#pragma once
#ifndef CALCULATENERGY_H
#define CALCULATENERGY_H

#include "Task.h"
#include "constans.h"
#include <time.h>

class CalculateEnergy : public Task
{
public:
	CalculateEnergy(void);
	CalculateEnergy(int params[4], cell** cells);
	~CalculateEnergy(void);
	void start();
	void execute();
	int cal_energy(int idx_i, int idx_j,int id, cell** space_of_cells);
	void toString();
private:
	int params[4];
	cell** cells;
};

#endif