#pragma once
#ifndef INITIALIZEIDS_H
#define INITIALIZEIDS_H
#include "Task.h"
#include "constans.h"
#include <boost\random.hpp>
class InitializeIds : public Task
{
public:
	InitializeIds(void);
	InitializeIds(int begin, int end, cell** cells);
	~InitializeIds(void);
	void start();
	void execute();
private:
	int begin,end;
	cell** cells;
};

#endif
