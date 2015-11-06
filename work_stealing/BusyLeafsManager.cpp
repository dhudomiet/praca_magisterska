#include "BusyLeafsManager.h"


BusyLeafsManager::BusyLeafsManager(void)
{
	cores = new BusyLeafs[CORES-1];
}


BusyLeafsManager::~BusyLeafsManager(void)
{
	delete [] cores;
}

void BusyLeafsManager::run(){
	for(int i=0;i<(CORES-1);i++){
		group.add_thread(BusyLeafs::getCore(i)->start());
	}
	group.join_all();
}

void BusyLeafsManager::initializeIds(cell** cells){
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
			BusyLeafs::addTask(wsk);
			//delete wsk;
			sumWid+=stepWid;
		}
		sum+=step;
		sumWid=0;
	}
}

void BusyLeafsManager::initializeSpace(int** space){
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
			BusyLeafs::getCore(i)->addTask(wsk);
			sumWid+=stepWid;
		}
		sum+=step;
		sumWid=0;
		if(++i==BusyLeafs::getCoreSize()){
			--i;
		}
	}
}

void BusyLeafsManager::calculateEnergy(cell** cells){
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
			CalculateEnergy* wsk = new CalculateEnergy(params,cells);
			BusyLeafs::addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
	}
}

void BusyLeafsManager::executeList(vector<cell> *list, cell** cells, cell** oldstate){
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
			BusyLeafs::addTask(init);
			sumWid+=stepWid;
			//delete init;
		}
		sum+=step;
		sumWid=sum;
	}
}

void BusyLeafsManager::fillList(vector<cell> *vect, cell** space){
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
			BusyLeafs::addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
	}
}

void BusyLeafsManager::copySpaces(cell** space, cell** source_space){
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
			BusyLeafs::addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
	}
}

void BusyLeafsManager::copyGrows(int** space, int** source){
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
			BusyLeafs::addTask(wsk);
			sumWid+=stepWid;
		}
		sum+=step;
		sumWid=0;
	}
}

void BusyLeafsManager::initializeEnergy(cell** cells){
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
			BusyLeafs::addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
	}
}

void BusyLeafsManager::executeRec(vector<cell> *noRect, vector<cell> *rect, cell** cells, cell** oldstate){
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
			BusyLeafs::addTask(init);
			sumWid+=stepWid;
			//delete init;
		}
		sum+=step;
		sumWid=sum;
	}
}

void BusyLeafsManager::fillNoRectList(vector<cell> *list, cell** cells){
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
			BusyLeafs::addTask(wsk);
			sumWid+=stepWid;
			//delete wsk;
		}
		sum+=step;
		sumWid=0;
	}
}

void BusyLeafsManager::executeGrainGrow(int** space, int** old_space){
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
			BusyLeafs::getCore(i)->addTask(wsk);
			sumWid+=stepWid;
		}
		sum+=step;
		sumWid=0;
		if(++i==BusyLeafs::getCoreSize()){
			--i;
		}
	}
}
