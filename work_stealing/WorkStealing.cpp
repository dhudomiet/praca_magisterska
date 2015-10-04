#include "WorkStealing.h"

boost::mutex WorkStealing::mut;
bool WorkStealing::flag = false;
vector<WorkStealing*> WorkStealing::cores;

WorkStealing::WorkStealing(void)
{
	mut.lock();
	cores.push_back(this);
	id = cores.size()-1;
	mut.unlock();
}


WorkStealing::~WorkStealing(void)
{
	cout<<"destruct"<<endl;
}

void WorkStealing::steal(){
	srand(time(NULL));
	int r = rand()%cores.size();
	while(r == id){
		r = rand()%cores.size();
	}
	WorkStealing* work = cores.at(r);
	//cout<<"core id: "<<id<<" steal data from core id: "<<work->getID()<<endl;
	if(work->getTaskSize()>0){
		tasks.push_back(work->getLastTask());
	}
}

void WorkStealing::execute(){
	flag = false;
	while(flag == false){
		if(tasks.size()>0){
			Task* t = getFirstTask();
			//cout<<"core id: "<<id<<" execute task..."<<endl;
			t->start();
			t->join();
		}else{
			steal();
		}
		int count = 0;
		for(int i=0;i<cores.size();i++){
			count+=cores.at(i)->getTaskSize();
		}
		if(count == 0){
			flag = true;
		}
	}

}

boost::thread* WorkStealing::start(){
	th = boost::thread(&WorkStealing::execute,this);
	return &th;
}

void WorkStealing::join(){
	th.join();
}

Task* WorkStealing::getLastTask(){
	mut.lock();
	Task* task = tasks.at(tasks.size()-1);
	tasks.pop_back();
	mut.unlock();
	return task;
}

Task* WorkStealing::getFirstTask(){
	mut.lock();
	Task* task = tasks.at(0);
	tasks.pop_front();
	mut.unlock();
	return task;
}

int WorkStealing::getTaskSize(){
	mut.lock();
	int szs = tasks.size();
	mut.unlock();
	return szs;
}

int WorkStealing::getID(){
	return id;
}

void WorkStealing::addTask(Task* task){
	mut.lock();
	tasks.push_back(task);
	mut.unlock();
}

Task* WorkStealing::getIndex(int idx){
	return tasks.at(idx);
}

WorkStealing* WorkStealing::getCore(int idx){
	return cores.at(idx);
}

int WorkStealing::getCoreSize(){
	return cores.size();
}

void WorkStealing::clear(){
	while(cores.size()){
		cores.erase(cores.begin());
	}
}