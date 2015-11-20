#pragma once
#ifndef WORKSTEALING_H
#define WORKSTEALING_H
#include "Task.h"
#include <boost/random.hpp>
#include <boost/thread.hpp>
#include "constans.h"
#include <vector>
class WorkStealing
{
public:
	WorkStealing(void);
	~WorkStealing(void);
	void steal();
	void execute();
	boost::thread* start();
	void join();
	void detach();
	Task* getLastTask();
	Task* getFirstTask();
	int getTaskSize();
	int getID();
	void addTask(Task *task);
	static WorkStealing* getCore(int idx);
	static int getCoreSize();
	static void clear();
	static void stop();
private:
	static vector<WorkStealing*> cores;
	boost::mutex mut;
	static boost::mutex gmut;
	static bool flag;
	//boost::thread* th;
	deque<Task*> tasks;
	int id;
	static int num;
	boost::random::mt19937 type;
	boost::random::uniform_int_distribution <> numbers;
	//boost::variate_generator< boost::mt19937, boost::uniform_int<> > dice;
};

#endif

