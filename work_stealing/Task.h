#pragma once
#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <deque>
#include <boost\thread.hpp>
using namespace std;

class Task
{
public:
	Task(void);
	~Task(void);
	virtual void start();
	void join();
	virtual void execute();
	void detach();
	virtual void toString();
protected:
	boost::thread *th;
};

#endif