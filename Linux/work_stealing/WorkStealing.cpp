#include "WorkStealing.h"

bool WorkStealing::flag = false;
int WorkStealing::num = 0;
vector<WorkStealing*> WorkStealing::cores;
boost::mutex WorkStealing::gmut;

WorkStealing::WorkStealing(void) : type(++num), numbers(0, (CORES-2))
{
	this->CORES=2;
	cores.push_back(this);
	id = cores.size()-1;
}

WorkStealing::WorkStealing(int CORES) : type(++num), numbers(0, (CORES-1))
{
	this->CORES=CORES;
	cores.push_back(this);
	id = cores.size()-1;
}


WorkStealing::~WorkStealing(void)
{
	cout<<"destroy workstealing..."<<endl;
	int number = (id<0)? 0 : id;
	cores.erase(cores.begin()+number);
	cout<<"end destroy workstealing"<<endl;
}

void WorkStealing::steal(){
	while(tasksForCores()){
		int r = numbers(type);
		Task* task = cores.at(r)->getFirstTask();
		if(task!= NULL){
			task->execute();
		}
	}

}

void WorkStealing::execute(){
	flag = (flag == true)? false : false;
	while(true){
		Task *t = getFirstTask();
		if(t!= NULL){
			t->execute();
			delete t;
		}
		if(getTasksSize()==0){
			steal();
			break;
		}

	}

}

boost::thread* WorkStealing::start(){
	return new boost::thread(&WorkStealing::execute,this);
}

int WorkStealing::getTasksSize(){
	boost::lock_guard<boost::mutex> lock(mut);
	return tasks.size();
}

Task* WorkStealing::getLastTask(){
	boost::unique_lock<boost::mutex> lock(mut);
	if(tasks.size()>0){
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
	boost::unique_lock<boost::mutex> lock(mut);
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

bool WorkStealing::tasksForCores(){
	int count = 0;
	for(int i=0;i<cores.size();i++){
		count+=cores.at(i)->getTasksSize();
	}
	if(count !=0){
		return true;
	}else{
		return false;
	}
}

int WorkStealing::getID(){
	return id;
}

void WorkStealing::addTask(Task* task){
	boost::lock_guard<boost::mutex> lock(mut);
	tasks.push_back(task);
}

WorkStealing* WorkStealing::getCore(int idx){
	return cores.at(idx);
}

int WorkStealing::getCoreSize(){
	return cores.size();
}
