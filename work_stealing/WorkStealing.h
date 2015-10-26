#pragma once
#ifndef WORKSTEALING_H
#define WORKSTEALING_H
#include "Task.h"
#include <boost\random.hpp>
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
	void addTask(Task* task);
	static WorkStealing* getCore(int idx);
	static int getCoreSize();
	static void clear();
	static void stop();
private:
	static vector<WorkStealing*> cores;
	boost::shared_mutex mut;
	static bool flag;
	boost::thread *th;
	deque<Task*> tasks;
	int id;
	static boost::mt19937 type;
	static boost::uniform_int<> numbers;
	static boost::variate_generator< boost::mt19937, boost::uniform_int<> > dice;
};

#endif

