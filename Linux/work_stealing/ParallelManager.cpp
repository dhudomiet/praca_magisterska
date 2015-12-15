/*
 * ParallelManager.cpp
 *
 *  Created on: Dec 13, 2015
 *      Author: damian
 */

#include "ParallelManager.h"

ParallelManager::ParallelManager() {
	this->CORES = 2;
	this->cores = new Parallel[CORES];
	this->duraction = 0;
	this->threadsTime = 0;

}

ParallelManager::ParallelManager(int cores) {
	this->CORES = cores;
	this->cores = new Parallel[CORES];
	this->duraction = 0;
	this->threadsTime = 0;

}

ParallelManager::~ParallelManager() {
		delete cores;

}

void ParallelManager::run() {
	Time start(boost::posix_time::microsec_clock::local_time());
	for (int i = 0; i < (CORES); i++) {
		group.add_thread(Parallel::getCore(i)->start());
	}
	Time stop(boost::posix_time::microsec_clock::local_time());
	TimeDuraction d = stop - start;
	duraction += d.total_microseconds();
}
void ParallelManager::initializeIds(cell** cells) {
	int sum = 0;
	int step = HEIGHT / (CORES);
	int sumWid = 0;
	int t = TASKS
	;
	int stepWid = WIDTH / ((t > WIDTH) ? WIDTH : t);
	int i = 0;
	while (sum < HEIGHT) {
		if (sum < HEIGHT && (sum + step) >= HEIGHT) {
			step = HEIGHT - sum;
		}
		while (sumWid < WIDTH) {
			int params[4];
			if (sumWid < WIDTH && (sumWid + stepWid) >= WIDTH) {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH - sumWid;
			} else {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			InitializeIds* wsk = new InitializeIds(params, cells);
			Parallel::getCore(i)->addTask(wsk);
			//delete wsk;
			sumWid += stepWid;
		}
		sum += step;
		sumWid = 0;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::initializeSpace(int** space) {
	int sum = 0;
	int step = HEIGHT / (CORES);
	int sumWid = 0;
	int t = calculateTasksForThread(); //TASKS;
	int stepWid = WIDTH / ((t > WIDTH) ? WIDTH : t);
	int i = 0;
	while (sum < HEIGHT) {
		if (sum < HEIGHT && (sum + step) >= HEIGHT) {
			step = HEIGHT - sum;
		}
		while (sumWid < WIDTH) {
			int params[4];
			if (sumWid < WIDTH && (sumWid + stepWid) >= WIDTH) {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH - sumWid;
			} else {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			InitializeSpace* wsk = new InitializeSpace(params, space);
			Parallel::getCore(i)->addTask(wsk);
			sumWid += stepWid;
		}
		sum += step;
		sumWid = 0;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::calculateEnergy(cell** cells) {
	int sum = 0;
	int step = HEIGHT / (CORES);
	int sumWid = 0;
	int t = TASKS
	;
	int stepWid = WIDTH / ((t > WIDTH) ? WIDTH : t);
	int i = 0;
	//cout<<"prepare data to calculate energy..."<<endl;
	while (sum < HEIGHT) {
		if (sum < HEIGHT && (sum + step) >= HEIGHT) {
			step = HEIGHT - sum;
		}
		while (sumWid < WIDTH) {
			int params[4];
			if (sumWid < WIDTH && (sumWid + stepWid) >= WIDTH) {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH - sumWid;
			} else {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			CalculateEnergy* wsk = new CalculateEnergy(params, cells);
			Parallel::getCore(i)->addTask(wsk);
			sumWid += stepWid;
			//delete wsk;
		}
		sum += step;
		sumWid = 0;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::executeList(vector<cell*> *list, cell** cells,cell** oldstate) {
	unsigned int sum = 0;
	int step = list->size() / (CORES);
	int sumWid = 0;
	int t = TASKS
	;
	int stepWid = step / ((t > step) ? step : t);
	int i = 0;
	while (sum < list->size()) {
		if (sum < list->size() && (sum + step) >= list->size()) {
			step = list->size() - sum;
		}
		int size = sum + step;
		while (sumWid < size) {
			if (sumWid < size && (sumWid + stepWid) >= size) {
				stepWid = size - sumWid;
			}
			ExecuteList* init = new ExecuteList(sumWid, sumWid + stepWid, list,
					cells, oldstate);
			Parallel::getCore(i)->addTask(init);
			sumWid += stepWid;
			//delete init;
		}
		sum += step;
		sumWid = sum;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::fillList(vector<cell*> *vect, cell** space) {
	int sum = 0;
	int step = HEIGHT / (CORES);
	int sumWid = 0;
	int t = TASKS
	;
	int stepWid = WIDTH / ((t > WIDTH) ? WIDTH : t);
	int i = 0;

	while (sum < HEIGHT) {
		if (sum < HEIGHT && (sum + step) >= HEIGHT) {
			step = HEIGHT - sum;
		}
		while (sumWid < WIDTH) {
			int params[4];
			if (sumWid < WIDTH && (sumWid + stepWid) >= WIDTH) {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH - sumWid;
			} else {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			FillList* wsk = new FillList(params, vect, space);
			Parallel::getCore(i)->addTask(wsk);
			sumWid += stepWid;
			//delete wsk;
		}
		sum += step;
		sumWid = 0;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::copySpaces(cell** space, cell** source_space) {
	int sum = 0;
	int step = HEIGHT / (CORES);
	int sumWid = 0;
	int t = TASKS
	;
	int stepWid = WIDTH / ((t > WIDTH) ? WIDTH : t);
	int i = 0;
	while (sum < HEIGHT) {
		if (sum < HEIGHT && (sum + step) >= HEIGHT) {
			step = HEIGHT - sum;
		}
		while (sumWid < WIDTH) {
			int params[4];
			if (sumWid < WIDTH && (sumWid + stepWid) >= WIDTH) {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH - sumWid;
			} else {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			CopySpaces* wsk = new CopySpaces(params, source_space, space);
			Parallel::getCore(i)->addTask(wsk);
			sumWid += stepWid;
			//delete wsk;
		}
		sum += step;
		sumWid = 0;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::copyGrows(int** space, int** source) {
	int sum = 0;
	int step = HEIGHT / (CORES);
	int sumWid = 0;
	int t = calculateTasksForThread(); //TASKS;
	int stepWid = WIDTH / ((t > WIDTH) ? WIDTH : t);
	int i = 0;
	while (sum < HEIGHT) {
		if (sum < HEIGHT && (sum + step) >= HEIGHT) {
			step = HEIGHT - sum;
		}
		while (sumWid < WIDTH) {
			int params[4];
			if (sumWid < WIDTH && (sumWid + stepWid) >= WIDTH) {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH - sumWid;
			} else {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			CopyGrows* wsk = new CopyGrows(params, space, source);
			Parallel::getCore(i)->addTask(wsk);
			sumWid += stepWid;
			//delete wsk;
		}
		sum += step;
		sumWid = 0;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::initializeEnergy(cell** cells) {
	int sum = 0;
	int step = HEIGHT / (CORES);
	int sumWid = 0;
	int t = TASKS
	;
	int stepWid = WIDTH / ((t > WIDTH) ? WIDTH : t);
	int i = 0;
	while (sum < HEIGHT) {
		if (sum < HEIGHT && (sum + step) >= HEIGHT) {
			step = HEIGHT - sum;
		}
		while (sumWid < WIDTH) {
			int params[4];
			if (sumWid < WIDTH && (sumWid + stepWid) >= WIDTH) {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH - sumWid;
			} else {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			InitializeEnergy* wsk = new InitializeEnergy(params, cells);
			Parallel::getCore(i)->addTask(wsk);
			sumWid += stepWid;
			//delete wsk;
		}
		sum += step;
		sumWid = 0;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::executeRec(vector<cell> *noRect, vector<cell> *rect,cell** cells, cell** oldstate) {
	int sum = 0;
	int step =
			(noRect->size() / (CORES) == 0) ?
					noRect->size() : noRect->size() / (CORES);
	int sumWid = 0;
	int t = TASKS
	;
	int stepWid = step / ((t > step) ? ((step > 0) ? step : t) : t);
	int i = 0;
	while (sum < noRect->size()) {
		if (sum < noRect->size() && (sum + step) >= noRect->size()) {
			step = noRect->size() - sum;
		}
		int size = sum + step;
		while (sumWid < size) {
			if (sumWid < size && (sumWid + stepWid) >= size) {
				stepWid = size - sumWid;
			}
			ExecuteRec* init = new ExecuteRec(sumWid, sumWid + stepWid, noRect,
					rect, cells, oldstate);
			Parallel::getCore(0)->addTask(init);
			sumWid += stepWid;
			//delete init;
		}
		sum += step;
		sumWid = sum;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::fillNoRectList(vector<cell> *list, cell** cells) {
	int sum = 0;
	int step = HEIGHT / (CORES);
	int sumWid = 0;
	int t = TASKS
	;
	int stepWid = WIDTH / ((t > WIDTH) ? WIDTH : t);
	int i = 0;
	while (sum < HEIGHT) {
		if (sum < HEIGHT && (sum + step) >= HEIGHT) {
			step = HEIGHT - sum;
		}
		while (sumWid < WIDTH) {
			int params[4];
			if (sumWid < WIDTH && (sumWid + stepWid) >= WIDTH) {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH - sumWid;
			} else {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			FillNoRecList* wsk = new FillNoRecList(params, list, cells);
			Parallel::getCore(i)->addTask(wsk);
			sumWid += stepWid;
			//delete wsk;
		}
		sum += step;
		sumWid = 0;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::executeGrainGrow(int** space, int** old_space) {
	int sum = 0;
	int step = HEIGHT / (CORES);
	int sumWid = 0;
	int t = calculateTasksForThread(); //TASKS;
	int stepWid = WIDTH / ((t > WIDTH) ? WIDTH : t);
	int i = 0;
	while (sum < HEIGHT) {
		if (sum < HEIGHT && (sum + step) >= HEIGHT) {
			step = HEIGHT - sum;
		}
		while (sumWid < WIDTH) {
			int params[4];
			if (sumWid < WIDTH && (sumWid + stepWid) >= WIDTH) {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = WIDTH - sumWid;
			} else {
				params[0] = sum;
				params[1] = step;
				params[2] = sumWid;
				params[3] = stepWid;
			}
			ExecuteGrainGrow* wsk = new ExecuteGrainGrow(params, space,
					old_space);
			Parallel::getCore(i)->addTask(wsk);
			sumWid += stepWid;
		}
		sum += step;
		sumWid = 0;
		if (++i == Parallel::getCoreSize()) {
			--i;
		}
	}
}
void ParallelManager::join_all() {
	group.join_all();
}
int ParallelManager::getDuraction() {
	return duraction;
}
int ParallelManager::calculateHeightForTask() {
	return HEIGHT / (CORES / 2);
}
int ParallelManager::calculateWidthForTask() {
	return WIDTH / (CORES / 2);
}
int ParallelManager::calculateTasksForThread() {
	int tasks = TASKS
	;
	return tasks / CORES;
}

