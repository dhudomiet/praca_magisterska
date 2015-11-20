#pragma once
#ifndef INITIALIZESPACE_H
#define INITIALIZESPACE_H

#include "constans.h"
#include "Task.h"

class InitializeSpace : public Task
{
public:
	InitializeSpace(void);
	InitializeSpace(int params[4], int** space);
	~InitializeSpace(void);
	void start();
	void execute();
	void toString();
private:
	int params[4];
	int** space;
};

#endif