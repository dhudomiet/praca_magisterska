/*
 * Graingrow.cpp
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#include "GrainGrow.h"

Grain_grow::Grain_grow() {
	manager = new BusyLeafsManager();
	initialize_space();
}

Grain_grow::~Grain_grow() {
	// TODO Auto-generated destructor stub
}

void Grain_grow::initialize_space() {
	space_of_cells = new int*[HEIGHT];
	old_space = new int*[HEIGHT];
	for(int i=0;i<HEIGHT;i++){
		space_of_cells[i] = new int[WIDTH];
		old_space[i] = new int[WIDTH];
	}
	manager->initializeSpace(space_of_cells);
	manager->run();
	int m = 1;
	for (int i = 0; i < HEIGHT; i+=5) {
		for(int j = 0; j < WIDTH; j+=5){
			space_of_cells[i][j] = (m++);
		}
	}
	//draw_space();
}

void Grain_grow::copy_spaces(int** space, int** source_space) {
	manager->copyGrows(space,source_space);
	manager->run();
}

void Grain_grow::draw_space() {
	cout<<endl;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout<<space_of_cells[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
}

void Grain_grow::grain_grow_algorithm() {
	cout<<"start execute grain grow..."<<endl;
	clock_t start, stop;
	start = clock();
	while (!is_fill_all()) {
		copy_spaces(old_space, space_of_cells);
		executeGrainGrow(space_of_cells,old_space);
	}
	stop = clock();
	float time = (float)stop - (float)start;
	cout<<"time of execution : "<<time<<endl;
	//draw_space();

}

void Grain_grow::executeGrainGrow(int** space, int** old_space){
	manager->executeGrainGrow(space,old_space);
	manager->run();
}

bool Grain_grow::is_fill_all(){
	int count = 0;
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			if(space_of_cells[i][j] !=0){
				count++;
			}
		}
	}
	if(count == WIDTH*HEIGHT){
		return true;
	}else{
		return false;
	}
}


