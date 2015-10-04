#pragma once
#ifndef WORKSTEALING_H
#define WORKSTEALING_H
#include "Task.h"
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
	Task* getLastTask();
	Task* getFirstTask();
	int getTaskSize();
	int getID();
	void addTask(Task* task);
	Task* getIndex(int idx);
	static WorkStealing* getCore(int idx);
	static int getCoreSize();
	static void clear();
private:
	static vector<WorkStealing*> cores;
	static boost::mutex mut;
	static bool flag;
	boost::thread th;
	deque<Task*> tasks;
	int id;
};

#endif

