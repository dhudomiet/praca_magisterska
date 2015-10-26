#pragma once
#ifndef COPYSPACES_H
#define COPYSPACES_H

#include "Task.h"
#include "constans.h"

class CopySpaces : public Task
{
public:
	CopySpaces(void);
	CopySpaces(int params[4], cell** source, cell** space);
	~CopySpaces(void);
	void start();
	void execute();
	void toString();
private:
	int params[4];
	cell** source;
	cell** space;
};

#endif
