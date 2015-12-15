#pragma once

#ifndef COPYGROWS_H
#define COPYGROWS_H

#include "Task.h"

class CopyGrows : public Task
{
public:
	CopyGrows(void);
	CopyGrows(int params[4], int** space, int** source);
	~CopyGrows(void);
	void start();
	void execute();
	void toString();

private:
	int params[4];
	int** space;
	int** source;
};

#endif

