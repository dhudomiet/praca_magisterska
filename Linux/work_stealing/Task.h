#pragma once
#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <deque>
using namespace std;

class Task
{
public:
	Task(void);
	virtual ~Task(void);
	virtual void start();
	void join();
	virtual void execute();
	void detach();
	virtual void toString();
	//virtual void gather();
protected:
};

#endif
