#include "Task.h"


Task::Task(void)
{
}


Task::~Task(void)
{
}

void Task::start(){
	th = boost::thread(&Task::execute,this);
}

void Task::join(){
	th.join();
}

void Task::execute(){
	cout<<"hehe to moja funkcja"<<endl;
}