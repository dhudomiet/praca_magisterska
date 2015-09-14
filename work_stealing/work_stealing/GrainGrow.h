/*
 * Graingrow.h
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#ifndef GRAINGROW_H_
#define GRAINGROW_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 100
#define WIDTH 100
#define NUMBER_OF_GRAINS 9



class Grain_grow {
public:
	Grain_grow();
	~Grain_grow();
	void initialize_space();
	void copy_spaces(int (*space)[WIDTH], int (*source_space)[WIDTH]);
	bool is_neighbor(int idx_i, int idx_j, int *tab, int (*space_of_cells)[WIDTH]);
	void draw_space();
	void grain_grow_algorithm();

	int space_of_cells[HEIGHT][WIDTH];
	int old_space[HEIGHT][WIDTH];

};

#endif /* GRAINGROW_H_ */
