#pragma once
#ifndef INITIALIZEIDS_H
#define INITIALIZEIDS_H
#include <ctime>
#include "Task.h"
#include "constans.h"
#include <boost\random.hpp>
class InitializeIds : public Task
{
public:
	InitializeIds(int params[4], cell** cells);
	~InitializeIds(void);
	void start();
	void execute();
	void toString();
	typedef boost::mt19937                          ENG; //engine
	typedef boost::uniform_real <>                  UDIST; //distribution
	typedef boost::variate_generator <ENG, UDIST>  UGEN; //generator
private:
	int params[4];
	cell** cells;
	ENG engine;
	UDIST dist;
	UGEN generator;
	


};

#endif
