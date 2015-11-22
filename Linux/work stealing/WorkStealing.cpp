#include "WorkStealing.h"

bool WorkStealing::flag = false;
int WorkStealing::num = 0;
vector<WorkStealing*> WorkStealing::cores;
boost::mutex WorkStealing::gmut;

WorkStealing::WorkStealing(void) : type(++num), numbers(0, (CORES-2))
{
	boost::lock_guard<boost::mutex> lock(gmut);
	cores.push_back(this);
	id = cores.size()-1;
}


WorkStealing::~WorkStealing(void)
{
	cout<<"destroy workstealing..."<<endl;
	boost::lock_guard<boost::mutex> lock(gmut);
	int number = (id<0)? 0 : id;
	cores.erase(cores.begin()+number);
	cout<<"end destroy workstealing"<<endl;
	//th.detach();
}

void WorkStealing::detach(){
	//th->detach();
}

void WorkStealing::steal(){
	int r = numbers(type);
	if(r==id){
		return;
	}
	WorkStealing* work = cores.at(r);
	//cout<<"core id: "<<id<<" steal data from core id: "<<work->getID()<<endl;
	Task* t = work->getLastTask();
	//cout<<"core id: "<<id;
	if(t!=NULL){
		//t->toString();
		//cout<<"execute"<<endl;
		t->execute();
		//cout<<"end execute"<<endl;
		delete t;
	}
	//cout<<"end steal"<<endl;
}

void WorkStealing::execute(){
	flag = (flag == true)? false : false;
	while(flag == false){
		Task *t = getFirstTask();
		//cout<<"core id: "<<id;
		if(t!= NULL){
			//cout<<"execute"<<endl;
			t->execute();
			//cout<<"end execute"<<endl;
		}else{
			steal();
		}
		delete t;
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
	//cout<<"start thread..."<<endl;
	return new boost::thread(&WorkStealing::execute,this);
}

void WorkStealing::join(){
	//th->join();
}

Task* WorkStealing::getLastTask(){
	boost::unique_lock<boost::mutex> lock(mut);
	if(tasks.size()>1){
		Task *task = tasks.at(tasks.size()-1);
		tasks.pop_back();
		lock.unlock();
		return task;
	}else{
		lock.unlock();
		return NULL;
	}
}

Task* WorkStealing::getFirstTask(){
	boost::unique_lock<boost::mutex> lock(mut);
	if(tasks.size()>0){
		Task *task = tasks.at(0);
		tasks.pop_front();
		lock.unlock();
		return task;
	}else{
		lock.unlock();
		return NULL;
	}
	
}

int WorkStealing::getTaskSize(){
	boost::lock_guard<boost::mutex> lock(mut);
	return tasks.size();
}

int WorkStealing::getID(){
	return id;
}

void WorkStealing::addTask(Task* task){
	boost::lock_guard<boost::mutex> lock(mut);
	tasks.push_back(task);
	return;
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

void WorkStealing::stop(){
	flag = true;
}