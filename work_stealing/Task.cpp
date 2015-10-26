#include "Task.h"


Task::Task(void)
{
}


Task::~Task(void)
{
	th->detach();
}

void Task::start(){
	th = new boost::thread(&Task::execute,this);
}

void Task::join(){
	th->join();
}

void Task::execute(){
	cout<<"hehe to moja funkcja"<<endl;
}

void Task::detach(){
	th->detach();
}

void Task::toString(){
	cout<<"execute Task..."<<endl;
}