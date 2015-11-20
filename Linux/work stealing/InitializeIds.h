#pragma once
#ifndef INITIALIZEIDS_H
#define INITIALIZEIDS_H
#include <ctime>
#include "Task.h"
#include "constans.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <random>
#include <functional>
class InitializeIds : public Task
{
public:
	InitializeIds(int params[4], cell** cells);
	~InitializeIds(void);
	void start();
	void execute();
	void toString();
	void gather();
	typedef boost::random::mt19937                         ENG; //engine
	typedef boost::random::uniform_int_distribution <>       UDIST; //distribution
	typedef boost::variate_generator <ENG, UDIST>  UGEN; //generator
private:
	int params[4];
	cell** cells;
	//ENG engine;
	//UDIST dist;
	uniform_int_distribution<int> dice_distribution;
	mt19937 random_number_engine;
	//UGEN generator;
	static int num;
	


};

#endif
