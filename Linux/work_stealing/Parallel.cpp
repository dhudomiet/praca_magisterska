/*
 * Parallel.cpp
 *
 *  Created on: Dec 13, 2015
 *      Author: damian
 */

#include "Parallel.h"

vector<Parallel*> Parallel::cores;

Parallel::Parallel() {
	cores.push_back(this);
	CORES = 2;

}

Parallel::Parallel(int cores){
	this->CORES = cores;
	Parallel::cores.push_back(this);
}

Parallel::~Parallel() {
	// TODO Auto-generated destructor stub
}

Task* Parallel::getTask(){
	if(tasks.size()>0){
		Task* t = tasks.at(0);
		tasks.pop_front();
		return t;
	}else{
		return NULL;
	}
}

int Parallel::getSizeTasks(){
	return tasks.size();
}

boost::thread* Parallel::start(){
	return new boost::thread(&Parallel::execute,this);
}

void Parallel::execute(){
	while(getSizeTasks()>0){
		Task* t = getTask();
		if(t!=NULL){
			t->execute();
		}
	}
}

void Parallel::addTask(Task* task){
	tasks.push_back(task);
}

int Parallel::getCoreSize(){
	return cores.size();
}

Parallel* Parallel::getCore(const int index){
	if(index<0 || index > cores.size()){
		return NULL;
	}else{
		return cores.at(index);
	}
}

