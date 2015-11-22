#pragma once
#ifndef INITIALIZEIDS_H
#define INITIALIZEIDS_H
#include <ctime>
#include <boost/random.hpp>
#include "Task.h"
#include "constans.h"
class InitializeIds : public Task
{
public:
	InitializeIds(int params[4], cell** cells);
	~InitializeIds(void);
	void start();
	void execute();
	void toString();
	void gather();
private:
	int params[4];
	cell** cells;
	//ENG engine;
	//UDIST dist;
	boost::random::uniform_int_distribution<>  dice_distribution;
	boost::random::mt19937 random_number_engine;
	//UGEN generator;
	static int num;
	


};

#endif
