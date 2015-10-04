#pragma once
#ifndef INITIALIZEIDS_H
#define INITIALIZEIDS_H
#include "Task.h"
#include "constans.h"
#include <time.h>
class InitializeIds : public Task
{
public:
	InitializeIds(void);
	InitializeIds(int begin, int end, cell** cells);
	~InitializeIds(void);
	void start();
	void execute(int begin, int end, cell** cells);
private:
	int begin,end;
	cell** cells;
};

#endif
