/*
* MonteCarlo.cpp
*
*  Created on: Aug 15, 2015
*      Author: damian
*/

#include "MonteCarlo.h"

MonteCarlo::MonteCarlo() {
	manager = new WorkStealingManager();
	duraction = 0;
	initializeIds();
}

MonteCarlo::~MonteCarlo(){
	cout<<"destroy MOnteCarlo"<<endl;
	for(int i=0;i<HEIGHT;i++){
		delete [] cells[i];
		delete [] oldstate[i];
	}
	
	delete [] cells;
	delete [] oldstate;
	delete manager;
	cout<<"end destroy MOnteCarlo"<<endl;
	
	
}
void MonteCarlo::initializeIds() {
	cells = new cell*[HEIGHT];
	oldstate = new cell*[HEIGHT];
	for(int i=0;i<HEIGHT;i++){
		cells[i] = new cell[WIDTH];
		oldstate[i] = new cell[WIDTH];
	}
	cout<<"start initializeIds..."<<endl;
	manager->initializeIds(cells);
	manager->run();
	cout<<"end initializeIds"<<endl;
	drawSpace();
	/*int sum = 0;
	int step = HEIGHT/CORES;
	clock_t start,stop;
	boost::thread_group group;
	cells = new cell*[HEIGHT];
	oldstate = new cell*[HEIGHT];
	for(int i=0;i<HEIGHT;i++){
		oldstate[i] = new cell[WIDTH];
	}
	start = clock();
	while(sum<HEIGHT){
		InitializeIds* init = new InitializeIds(sum,sum+step,cells);
		WorkStealing::getCore(0)->addTask(init);
		sum+=step;
	}
	for(int i= CORES-1;i>=0;i--){
		group.add_thread(WorkStealing::getCore(i)->start());
	}
	group.join_all();
	stop = clock();
	//cout<<"time execution: "<<(float)(stop-start)<<endl;
	//delete init;
	//draw_space();*/
}

void MonteCarlo::calculateEnergy() {
	cout<<"start calculate energy..."<<endl;
	manager->calculateEnergy(cells);
	manager->run();
	cout<<"end calculate energy"<<endl;
	//draw_energy();
/*	int sum = 0;
	int step = HEIGHT/CORES;
	boost::thread_group group;
	int i=0;
	while(sum<HEIGHT){
		CalculateEnergy* init = new CalculateEnergy(sum,sum+step,cells);
		WorkStealing::getCore(0)->addTask(init);
		sum+=step;
	}
	for(int i=CORES-1;i>=0;i--){
		group.add_thread(WorkStealing::getCore(i)->start());
	}
	group.join_all();
	//draw_energy();
}

void MonteCarlo::initializeCores(){
	for(unsigned i = 0;i<CORES;i++){
		WorkStealing* wo = new WorkStealing();
	}*/

}



void MonteCarlo::monteCarloAlgorithm() {
	logg("start monteCarlo algorithm...");
	Time st(boost::posix_time::microsec_clock::local_time());
	calculateEnergy();
	vector<cell*> listCells;
	for (int i = 0; i < 100; i++) {
		copySpaces(oldstate, cells);
		fillList(&listCells, cells);
		//cout<<listCells.size()<<endl;
		if(listCells.size()>0){
		executeList(&listCells,cells,oldstate);
		}
		listCells.clear();
	}
	Time end(boost::posix_time::microsec_clock::local_time());
	TimeDuraction d = end - st;
	duraction = d.total_milliseconds();
	loggTime("time execution montecarlo algorithm: ",duraction);
	saveToFile();
	//drawSpace();

}

void MonteCarlo::executeList(std::vector<cell*> *list, cell** cells, cell** oldstate){
	
	//cout<<"start execute list..."<<endl;
	manager->executeList(list,cells,oldstate);
	manager->run();
	//cout<<"end execute list"<<endl;
	/*int sum = 0;
	int step = HEIGHT/CORES;
	boost::thread_group group;
	while(sum<list->size()){
		ExecuteList* init = new ExecuteList(sum,sum+step,list,cells,oldstate);
		WorkStealing::getCore(0)->addTask(init);
		sum+=step;
	}
	for(int i=CORES-1;i>=0;i--){
		group.add_thread(WorkStealing::getCore(i)->start());
	}
	group.join_all();*/
}

void MonteCarlo::fillList(std::vector<cell*> *vect, cell** space) {
	//cout<<"start fill list..."<<endl;
	manager->fillList(vect,space);
	manager->run();
	//cout<<"end fill list"<<endl;
	/*int sum = 0;
	int step = HEIGHT/CORES;
	boost::thread_group group;
	while(sum<HEIGHT){
		FillList* init = new FillList(sum,sum+step,vect,cells);
		WorkStealing::getCore(0)->addTask(init);
		sum+=step;
	}
	for(int i=CORES-1;i>=0;i--){
		group.add_thread(WorkStealing::getCore(i)->start());
	}
	group.join_all();*/
}

void MonteCarlo::copySpaces(cell** space, cell** source_space) {
	//cout<<"start copy spaces..."<<endl;
	manager->copySpaces(space,source_space);
	manager->run();
	//cout<<"end copy spaces"<<endl;
	/*int sum = 0;
	int step = HEIGHT/CORES;
	boost::thread_group group;
	while(sum<HEIGHT){
		CopySpaces* init = new CopySpaces(sum,sum+step,source_space,space);
		WorkStealing::getCore(0)->addTask(init);
		sum+=step;
	}
	for(int i=CORES-1;i>=0;i--){
		group.add_thread(WorkStealing::getCore(i)->start());
	}
	group.join_all();*/
}

void MonteCarlo::drawEnergy() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << cells[i][j].energy << " ";
		}
		std::cout << std::endl;
	}
}

void MonteCarlo::drawSpace() {
	for (int i = 0; i < HEIGHT; i++) {
		for(int j=0;j<WIDTH;j++){
			cout<<cells[i][j].id<<" ";
		}
		cout<<endl;
	}
}

void MonteCarlo::clean(vector<cell> *vect){
	while(vect->size()>0){
		vect->erase(vect->begin());
	}
}

void MonteCarlo::setCells(cell** cells){
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			cells[i][j].id = this->cells[i][j].id;
			cells[i][j].idx_i = this->cells[i][j].idx_i;
			cells[i][j].idx_j = this->cells[i][j].idx_j;
			cells[i][j].energy = this->cells[i][j].energy;
		}
	}
}

Manager* MonteCarlo::getManager(){
	return manager;
}

void MonteCarlo::saveToFile(){
	std::ofstream file;
	file.open("results.txt",ios::out);
	if(file.good()){
		file<<"----------------------------------------------------------------------\n";
		file<<"									RESULTS								 \n";
		file<<"----------------------------------------------------------------------\n";
		file<<"Monte Carlo algorithm: space: HEIGHTxWIDTH "<<HEIGHT<<"x"<<WIDTH<<"\n";
		file<<"number of ids on the start: "<<NUMBER_OF_IDS<<"\n";
		file<<"number of cores: "<<CORES<<"\n";
		int t = TASKS;
		file<<"number of tasks: "<<t<<"\n";
		file<<"time of execution algorithm: "<<duraction<<"\n";
		file.close();
	}
}

