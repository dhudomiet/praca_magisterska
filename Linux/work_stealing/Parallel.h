/*
 * Parallel.h
 *
 *  Created on: Dec 13, 2015
 *      Author: damian
 */

#ifndef PARALLEL_H_
#define PARALLEL_H_

#include "Task.h";
#include <deque>
#include <boost/thread.hpp>
class Parallel {
public:
	Parallel();
	Parallel(int cores);
	virtual ~Parallel();
	Task* getTask();
	int getSizeTasks();
	boost::thread* start();
	void execute();
	void addTask(Task* task);
	static int getCoreSize();
	static Parallel* getCore(const int index);
private:
	int CORES;
	deque<Task*> tasks;
	static vector<Parallel*> cores;
};

#endif /* PARALLEL_H_ */
