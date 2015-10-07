#pragma once
#ifndef COPYSPACES_H
#define COPYSPACES_H

#include "Task.h"
#include "constans.h"

class CopySpaces : public Task
{
public:
	CopySpaces(void);
	CopySpaces(int begin, int end, cell** source, cell** space);
	~CopySpaces(void);
	void start();
	void execute();
private:
	int begin,end;
	cell** source;
	cell** space;
};

#endif
