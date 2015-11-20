#include "WorkStealingManager.h"


WorkStealingManager::WorkStealingManager(void)
{
	cores = new WorkStealing[CORES-1];
}

WorkStealingManager::~WorkStealingManager(void)
{
	delete [] cores;
}

void WorkStealingManager::run(){
	//cout<<"run calculate..."<<endl;
	for(int i=0;i<(CORES-1);i++){
		group.add_thread(WorkStealing::getCore(i)->start());
	}
	group.join_all();
	//cout<<"end run calculate..."<<endl;
}

void WorkStealingManager::initializeIds(cell** cells){
	int sum = 0;
	int step = HEIGHT/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = WIDTH/((t>WIDTH)? WIDTH : t);
	int i=0;
	while(sum<HEIGHT){
		if(sum<HEIGHT && (sum+step)>=HEIGHT){
			step = HEIGHT-sum;
		}
		while(sumWid<WIDTH){
			int params[4];
			if(sumWid<WIDTH && (sumWid+stepWid)>=WIDTH){
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH-sumWid;
			}else{
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			InitializeIds* wsk = new InitializeIds(params,cells);
			WorkStealing::getCore(i)->addTask(wsk);
			//delete wsk;
			sumWid+=stepWid;
		}
		sum+=step;
		sumWid=0;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}
}

void WorkStealingManager::initializeSpace(int** space){
	int sum = 0;
	int step = HEIGHT/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = WIDTH/((t>WIDTH)? WIDTH : t);
	int i=0;
	while(sum<HEIGHT){
		if(sum<HEIGHT && (sum+step)>=HEIGHT){
			step = HEIGHT-sum;
		}
		while(sumWid<WIDTH){
			int params[4];
			if(sumWid<WIDTH && (sumWid+stepWid)>=WIDTH){
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH-sumWid;
			}else{
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			InitializeSpace* wsk = new InitializeSpace(params,space);
			WorkStealing::getCore(i)->addTask(wsk);
			sumWid+=stepWid;
		}
		sum+=step;
		sumWid=0;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}
}

void WorkStealingManager::calculateEnergy(cell** cells){
	int sum = 0;
	int step = HEIGHT/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = WIDTH/((t>WIDTH)? WIDTH : t);
	int i=0;
	//cout<<"prepare data to calculate energy..."<<endl;
	while(sum<HEIGHT){
		if(sum<HEIGHT && (sum+step)>=HEIGHT){
			step = HEIGHT-sum;
		}
		while(sumWid<WIDTH){
			int params[4];
			if(sumWid<WIDTH && (sumWid+stepWid)>=WIDTH){
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH-sumWid;
			}else{
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			CalculateEnergy* wsk = new CalculateEnergy(params,cells);
			WorkStealing::getCore(i)->addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}
	//cout<<"end prepare data to calculate energy..."<<endl;
}

void WorkStealingManager::executeList(concurrent_vector<cell*> *list, cell** cells, cell** oldstate){
	int sum = 0;
	int step = list->size()/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = step/((t>step)? step : t);
	int i=0;
	while(sum<list->size()){
		if(sum<list->size() && (sum+step)>=list->size()){
			step = list->size()-sum;
		}
		int size = sum+step;
		while(sumWid<size){
			if(sumWid<size && (sumWid+stepWid)>=size){
				stepWid = size-sumWid;
			}
			ExecuteList* init = new ExecuteList(sumWid,sumWid+stepWid,list,cells,oldstate);
			WorkStealing::getCore(i)->addTask(init);
			sumWid+=stepWid;
			//delete init;
		}
		sum+=step;
		sumWid=sum;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}	
}

void WorkStealingManager::fillList(concurrent_vector<cell*> *vect, cell** space){
	int sum = 0;
	int step = HEIGHT/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = WIDTH/((t>WIDTH)? WIDTH : t);
	int i=0;
	
	while(sum<HEIGHT){
		if(sum<HEIGHT && (sum+step)>=HEIGHT){
			step = HEIGHT-sum;
		}
		while(sumWid<WIDTH){
			int params[4];
			if(sumWid<WIDTH && (sumWid+stepWid)>=WIDTH){
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH-sumWid;
			}else{
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			FillList* wsk = new FillList(params,vect, space);
			WorkStealing::getCore(i)->addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}
}

void WorkStealingManager::copySpaces(cell** space, cell** source_space){
	int sum = 0;
	int step = HEIGHT/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = WIDTH/((t>WIDTH)? WIDTH : t);
	int i=0;
	while(sum<HEIGHT){
		if(sum<HEIGHT && (sum+step)>=HEIGHT){
			step = HEIGHT-sum;
		}
		while(sumWid<WIDTH){
			int params[4];
			if(sumWid<WIDTH && (sumWid+stepWid)>=WIDTH){
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH-sumWid;
			}else{
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			CopySpaces* wsk = new CopySpaces(params,source_space, space);
			WorkStealing::getCore(i)->addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}
}

void WorkStealingManager::copyGrows(int** space, int** source){
	int sum = 0;
	int step = HEIGHT/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = WIDTH/((t>WIDTH)? WIDTH : t);
	int i=0;
	while(sum<HEIGHT){
		if(sum<HEIGHT && (sum+step)>=HEIGHT){
			step = HEIGHT-sum;
		}
		while(sumWid<WIDTH){
			int params[4];
			if(sumWid<WIDTH && (sumWid+stepWid)>=WIDTH){
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH-sumWid;
			}else{
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			CopyGrows* wsk = new CopyGrows(params,space, source);
			WorkStealing::getCore(i)->addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}
}

void WorkStealingManager::initializeEnergy(cell** cells){
	int sum = 0;
	int step = HEIGHT/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = WIDTH/((t>WIDTH)? WIDTH : t);
	int i=0;
	while(sum<HEIGHT){
		if(sum<HEIGHT && (sum+step)>=HEIGHT){
			step = HEIGHT-sum;
		}
		while(sumWid<WIDTH){
			int params[4];
			if(sumWid<WIDTH && (sumWid+stepWid)>=WIDTH){
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH-sumWid;
			}else{
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			InitializeEnergy* wsk = new InitializeEnergy(params,cells);
			WorkStealing::getCore(i)->addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}
}

void WorkStealingManager::executeRec(vector<cell> *noRect, vector<cell> *rect, cell** cells, cell** oldstate){
	int sum = 0;
	int step = noRect->size()/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = step/((t>step)? ((step>0)? step : t): t);
	int i=0;
	while(sum<noRect->size()){
		if(sum<noRect->size() && (sum+step)>=noRect->size()){
			step = noRect->size()-sum;
		}
		int size = sum+step;
		while(sumWid<size){
			if(sumWid<size && (sumWid+stepWid)>=size){
				stepWid = size-sumWid;
			}
			ExecuteRec* init = new ExecuteRec(sumWid,sumWid+stepWid,noRect,rect,cells,oldstate);
			WorkStealing::getCore(0)->addTask(init);
			sumWid+=stepWid;
			//delete init;
		}
		sum+=step;
		sumWid=sum;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}
}

void WorkStealingManager::fillNoRectList(vector<cell> *list, cell** cells){
	int sum = 0;
	int step = HEIGHT/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = WIDTH/((t>WIDTH)? WIDTH : t);
	int i=0;
	while(sum<HEIGHT){
		if(sum<HEIGHT && (sum+step)>=HEIGHT){
			step = HEIGHT-sum;
		}
		while(sumWid<WIDTH){
			int params[4];
			if(sumWid<WIDTH && (sumWid+stepWid)>=WIDTH){
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH-sumWid;
			}else{
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			FillNoRecList* wsk = new FillNoRecList(params,list,cells);
			WorkStealing::getCore(i)->addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}
}

void WorkStealingManager::executeGrainGrow(int** space, int** old_space){
	int sum = 0;
	int step = HEIGHT/(CORES-1);
	int sumWid = 0;
	int t = TASKS;
	int stepWid = WIDTH/((t>WIDTH)? WIDTH : t);
	int i=0;
	while(sum<HEIGHT){
		if(sum<HEIGHT && (sum+step)>=HEIGHT){
			step = HEIGHT-sum;
		}
		while(sumWid<WIDTH){
			int params[4];
			if(sumWid<WIDTH && (sumWid+stepWid)>=WIDTH){
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH-sumWid;
			}else{
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			ExecuteGrainGrow* wsk = new ExecuteGrainGrow(params,space,old_space);
			WorkStealing::getCore(i)->addTask(wsk);
			sumWid+=stepWid;
		}
		sum+=step;
		sumWid=0;
		if(++i==WorkStealing::getCoreSize()){
			--i;
		}
	}
}
