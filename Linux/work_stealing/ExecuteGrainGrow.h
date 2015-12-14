#pragma once
#ifndef EXECUTEGRAINGROW_H
#define EXECUTEGRAINGROW_H

#include "Task.h"
#include "constans.h"

class ExecuteGrainGrow : public Task
{
public:
	ExecuteGrainGrow(void);
	ExecuteGrainGrow(int params[4], int** space, int** old_space);
	~ExecuteGrainGrow(void);
	void start();
	void execute();
	void toString();
	bool is_neighbor(int idx_i, int idx_j, int *tab, int **space_of_cells);

private:
	int params[4];
	int** space;
	int** old_space;
};
#endif
