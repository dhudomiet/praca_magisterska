/*
 * Graingrow.cpp
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#include "GrainGrow.h"

Grain_grow::Grain_grow() {
	CORES=2;
	manager = new WorkStealingManager(CORES);
	duraction = 0;
	initialize_space();
}

Grain_grow::Grain_grow(int CORES) {
	this->CORES=CORES;
	manager = new WorkStealingManager(CORES);
	duraction = 0;
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
	manager->join_all();
	int m = 1;
	int divideWid = 0;
		if(WIDTH>NUMBER_OF_GRAINS){
			divideWid = WIDTH/NUMBER_OF_GRAINS;
	}else{
		divideWid = NUMBER_OF_GRAINS/WIDTH;
	}
	cout<<"set grains..."<<endl;
	for (int i = 0; i < HEIGHT; i+=NUMBER_OF_GRAINS/(NUMBER_OF_GRAINS/2)) {
		for(int j = 0; j < WIDTH; j+=divideWid){
			space_of_cells[i][j] = (m++);
			if(m>NUMBER_OF_GRAINS){
				break;
			}
		}
	}
	cout<<"end set grains..."<<endl;
	//drawSpace();
}

void Grain_grow::copySpaces(int** space, int** source_space) {
	manager->copyGrows(space,source_space);
	Time st(boost::posix_time::microsec_clock::local_time());
	//manager->run();
	Time end(boost::posix_time::microsec_clock::local_time());
	TimeDuraction d = end - st;
	duraction += d.total_milliseconds();
}

void Grain_grow::drawSpace() {
	cout<<endl;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout<<space_of_cells[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
}

void Grain_grow::grainGrowAlgorithm() {
	cout<<"start execute grain grow..."<<endl;
	Time st(boost::posix_time::microsec_clock::local_time());
	copySpaces(old_space, space_of_cells);
	manager->run();
	for(int i=0;i<100;i++) {
		copySpaces(old_space, space_of_cells);
		executeGrainGrow(space_of_cells,old_space);
	}
	manager->join_all();
	Time end(boost::posix_time::microsec_clock::local_time());
	TimeDuraction d = end - st;
	long duraction = d.total_milliseconds();
	cout<<"time of execution : "<<duraction<<endl;
	cout<<"time of execution algorithm : "<<this->duraction<<endl;
	cout<<"time of creating threads: "<<manager->getDuraction()<<endl;
	saveToFile();
	//drawSpace();

}

void Grain_grow::executeGrainGrow(int** space, int** old_space){
	manager->executeGrainGrow(space,old_space);
	Time st(boost::posix_time::microsec_clock::local_time());
	//manager->run();
	Time end(boost::posix_time::microsec_clock::local_time());
	TimeDuraction d = end - st;
	duraction += d.total_milliseconds();
}

bool Grain_grow::isFillAll(){
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

void Grain_grow::saveToFile(){
	std::ofstream file;
	file.open("results.txt",ios::out);
	if(file.good()){
		file<<"----------------------------------------------------------------------\n";
		file<<"									RESULTS								 \n";
		file<<"----------------------------------------------------------------------\n";
		file<<"Grain Grow algorithm: space: HEIGHTxWIDTH "<<HEIGHT<<"x"<<WIDTH<<"\n";
		file<<"number of grains: "<<NUMBER_OF_GRAINS<<"\n";
		file<<"number of cores: "<<CORES<<"\n";
		int t = TASKS;
		file<<"number of tasks: "<<t<<"\n";
		file<<"time of execution algorithm: "<<duraction<<"\n";
		file.close();
	}
}


