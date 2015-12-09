#pragma once
#ifndef GRAINGROW_H
#define GRAINGROW_H

#include "constans.h"
#include <iostream>
#include <time.h>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

typedef boost::posix_time::ptime Time;
typedef boost::posix_time::time_duration TimeDuraction;

class GrainGrow
{
public:
	GrainGrow(void);
	~GrainGrow(void);
	void initialize_space();
	void copy_spaces(int** space, int** source_space);
	void executeGrainGrow(int** space, int** old_space);
	void draw_space();
	void grain_grow_algorithm();
	bool is_fill_all();
	bool is_neighbor(int idx_i, int idx_j, int *tab, int **space_of_cells);

private:
	int** space_of_cells;
	int** old_space;
};

#endif

