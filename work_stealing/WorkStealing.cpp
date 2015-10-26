#include "WorkStealing.h"

bool WorkStealing::flag = false;
vector<WorkStealing*> WorkStealing::cores;
boost::mt19937 WorkStealing::type;
boost::uniform_int<> WorkStealing::numbers = boost::uniform_int<>( 0, (CORES-2));
boost::variate_generator< boost::mt19937, boost::uniform_int<> > WorkStealing::dice = boost::variate_generator< boost::mt19937, boost::uniform_int<> > (type, numbers);

WorkStealing::WorkStealing(void)
{
	boost::lock_guard<boost::shared_mutex> lock(mut);
	cores.push_back(this);
	id = cores.size()-1;
}


WorkStealing::~WorkStealing(void)
{
	th->detach();
}

void WorkStealing::detach(){
	th->detach();
}

void WorkStealing::steal(){
	srand(time(NULL));
	int r = dice();
	while(r == id){
		r = dice();
	}
	WorkStealing* work = cores.at(r);
	//cout<<"core id: "<<id<<" steal data from core id: "<<work->getID()<<endl;

	Task *t = work->getLastTask();
	//cout<<"core id: "<<id;
	if(t !=NULL){
		//t->toString();
		t->start();
		t->join();
		delete t;
	}
}

void WorkStealing::execute(){
	flag = (flag == true)? false : false;
	while(flag == false){
		
		Task* t = getFirstTask();
		//cout<<"core id: "<<id;
		if(t!=NULL){
			//t->toString();
			t->start();
			t->join();
			delete t;
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
	th = new boost::thread(&WorkStealing::execute,this);
	return th;
}

void WorkStealing::join(){
	th->join();
}

Task* WorkStealing::getLastTask(){
	boost::unique_lock<boost::shared_mutex> lock(mut);
	if(tasks.size()>1){
		Task* task = tasks.at(tasks.size()-1);
		tasks.pop_back();
		lock.unlock();
		return task;
	}else{
		lock.unlock();
		return NULL;
	}
}

Task* WorkStealing::getFirstTask(){
	boost::unique_lock<boost::shared_mutex> lock(mut);
	if(tasks.size()>0){
		Task* task = tasks.at(0);
		tasks.pop_front();
		lock.unlock();
		return task;
	}else{
		lock.unlock();
		return NULL;
	}
	
}

int WorkStealing::getTaskSize(){
	boost::lock_guard<boost::shared_mutex> lock(mut);
	return tasks.size();
}

int WorkStealing::getID(){
	return id;
}

void WorkStealing::addTask(Task* task){
	boost::lock_guard<boost::shared_mutex> lock(mut);
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