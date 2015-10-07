#include "WorkStealing.h"

bool WorkStealing::flag = false;
vector<WorkStealing*> WorkStealing::cores;

WorkStealing::WorkStealing(void)
{
	boost::lock_guard<boost::mutex> lock(mut);
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
	int r = rand()%cores.size();
	while(r == id){
		r = rand()%cores.size();
	}
	WorkStealing* work = cores.at(r);
	//cout<<"core id: "<<id<<" steal data from core id: "<<work->getID()<<endl;
	if(work->getTaskSize()>1){
		tasks.push_back(work->getLastTask());
		Task* t = getFirstTask();
		//cout<<"core id: "<<id<<" execute task..."<<endl;
		t->start();
		t->join();
	}
}

void WorkStealing::execute(){
	flag = (flag == true)? false : false;
	while(flag == false){
		if(getTaskSize()>0){
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
	th =new boost::thread(&WorkStealing::execute,this);
	return th;
}

void WorkStealing::join(){
	th->join();
}

Task* WorkStealing::getLastTask(){
	boost::lock_guard<boost::mutex> lock(mut);
	//cout<<"core id: "<<id<<" lock"<<endl;
	Task* task = tasks.at(tasks.size()-1);
	tasks.pop_back();
	//cout<<"core id: "<<id<<" unlock"<<endl;
	return task;
}

Task* WorkStealing::getFirstTask(){
	boost::lock_guard<boost::mutex> lock(mut);
	//cout<<"core id: "<<id<<" lock"<<endl;
	Task* task = tasks.at(0);
	tasks.pop_front();
	//cout<<"core id: "<<id<<" unlock"<<endl;
	return task;
}

int WorkStealing::getTaskSize(){
	boost::lock_guard<boost::mutex> lock(mut);
	//cout<<"core id: "<<id<<" lock"<<endl;
	//cout<<"core id: "<<id<<" unlock"<<endl;
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

void WorkStealing::stop(){
	flag = true;
}