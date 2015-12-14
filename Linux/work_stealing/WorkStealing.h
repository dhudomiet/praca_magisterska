#pragma once
#ifndef WORKSTEALING_H
#define WORKSTEALING_H
#include "Task.h"
#include <boost/random.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "constans.h"
#include <vector>

typedef boost::posix_time::ptime Time;
typedef boost::posix_time::time_duration TimeDuraction;

class WorkStealing
{
public:
	WorkStealing(void);
	WorkStealing(int CORES);
	~WorkStealing(void);
	void steal();
	void execute();
	boost::thread* start();
	int getTasksSize();
	Task* getLastTask();
	Task* getFirstTask();
	int getID();
	void addTask(Task *task);
	static WorkStealing* getCore(int idx);
	static int getCoreSize();
	bool tasksForCores();

private:
	static vector<WorkStealing*> cores;
	boost::mutex mut;
	static boost::mutex gmut;
	static bool flag;
	deque<Task*> tasks;
	int id;
	static int num;
	boost::random::mt19937 type;
	boost::random::uniform_int_distribution <> numbers;
	int CORES;
};

#endif

