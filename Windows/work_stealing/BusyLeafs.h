#pragma once
#ifndef BUSYLEAFS_H
#define BUSYLEAFS_H
#include "Task.h"
#include <deque>
#include <vector>
class BusyLeafs
{
public:
	BusyLeafs(void);
	~BusyLeafs(void);
	void tryPop();
	void execute();
	boost::thread* start();
	static int getTasksPoolSize();
	static BusyLeafs* getCore(int idx);
	static int getCoreSize();
	static void addTask(Task* task);
private:
	static vector<BusyLeafs*> cores;
	static deque<Task*> tasksPool;
	boost::thread th;
	static boost::shared_mutex shr_mut;
	int id;

};
#endif

