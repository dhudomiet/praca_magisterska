#include "BusyLeafs.h"

vector<BusyLeafs*> BusyLeafs::cores;
deque<Task*> BusyLeafs::tasksPool;
boost::shared_mutex BusyLeafs::shr_mut;

BusyLeafs::BusyLeafs(void)
{
	boost::lock_guard<boost::shared_mutex> lock(shr_mut);
	cores.push_back(this);
	id = cores.size()-1;
}


BusyLeafs::~BusyLeafs(void)
{

}

boost::thread* BusyLeafs::start(){
	return new boost::thread(&BusyLeafs::execute,this);
}

void BusyLeafs::tryPop(){
	boost::unique_lock<boost::shared_mutex> lock(shr_mut);
	if(tasksPool.size()>0){
		cout<<"core id: "<<id<<" pop data from list"<<endl;
		Task* t = tasksPool.at(0);
		tasksPool.pop_front();
		lock.unlock();
		cout<<"core id: "<<id<<" ";
		t->toString();
		t->start();
		t->join();
	}
}

int BusyLeafs::getTasksPoolSize(){
	boost::lock_guard<boost::shared_mutex> lock(shr_mut);
	return tasksPool.size();

}
void BusyLeafs::execute(){
	while(getTasksPoolSize() >0){
		tryPop();
	}
}

BusyLeafs* BusyLeafs::getCore(int idx){
	return cores.at(idx);
}


int BusyLeafs::getCoreSize(){
	return cores.size();
}

void BusyLeafs::addTask(Task* task){
	tasksPool.push_back(task);
}


