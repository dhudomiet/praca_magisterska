/*
 * Recrystalization.cpp
 *
 *  Created on: Aug 23, 2015
 *      Author: damian
 */

#include "Recrystalization.h"

Recrystalization::Recrystalization() {
	manager = mc.getManager();
	duraction = 0;
	initializeSpace();
}

Recrystalization::~Recrystalization() {
	delete cells;
	delete oldstate;
}
void Recrystalization::recrystalization_algorithm() {
	std::vector<cell> noRecrystalizationCells;
	cout << "start of recrystalization algorithm..." << endl;
	std::chrono::steady_clock::time_point st = std::chrono::steady_clock::now();
	randomRecGrains();
	mc.copySpaces(oldstate, cells);
	fill_no_recrystalization_list(&noRecrystalizationCells);
	while (noRecrystalizationCells.size() != 0/*++i<200*/) {
		executeRec(&noRecrystalizationCells, &recrystalizationList);
		noRecrystalizationCells.clear();
		mc.copySpaces(oldstate, cells);
		fill_no_recrystalization_list(&noRecrystalizationCells);

	}
	std::chrono::steady_clock::time_point end =
			std::chrono::steady_clock::now();
	duraction = std::chrono::duration_cast < std::chrono::milliseconds> (end - st).count();
	loggTime("time of execution recrystalization: ", duraction);
	saveToFile();
	//draw_data();
}

void Recrystalization::draw_data() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << cells[i][j].id << " ";
		}
		std::cout << std::endl;
	}
}

void Recrystalization::draw_energy() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << cells[i][j].energy << " ";
		}
		std::cout << std::endl;
	}
}

void Recrystalization::initializeSpace() {
	cells = new cell*[HEIGHT];
	oldstate = new cell*[HEIGHT];
	for (int i = 0; i < HEIGHT; i++) {
		cells[i] = new cell[WIDTH];
		oldstate[i] = new cell[WIDTH];
	}
	cout << "start initializeSpace..." << endl;
	mc.monteCarloAlgorithm();
	mc.setCells(cells);
	initializeEnergy();
	cout << "end initializeSpace" << endl;
}

void Recrystalization::initializeEnergy() {
	/*int sum = 0;
	 int step = HEIGHT/CORES;
	 boost::thread_group group;
	 while(sum<HEIGHT){
	 InitializeEnergy* init = new InitializeEnergy(sum,sum+step,cells);
	 WorkStealing::getCore(0)->addTask(init);
	 sum+=step;
	 }
	 for(int i=CORES-1;i>=0;i--){
	 group.add_thread(WorkStealing::getCore(i)->start());
	 }
	 group.join_all();*/
	cout << "start initialize energy..." << endl;
	manager->initializeEnergy(cells);
	manager->run();
	cout << "end initialize energy" << endl;
}

void Recrystalization::executeRec(vector<cell> *noRect, vector<cell> *rect) {
	/*int sum = 0;
	 int step = HEIGHT/CORES;
	 boost::thread_group group;
	 while(sum<noRect->size()){
	 ExecuteRec* init = new ExecuteRec(sum,sum+step,noRect,rect,cells);
	 WorkStealing::getCore(0)->addTask(init);
	 sum+=step;
	 }
	 for(int i=CORES-1;i>=0;i--){
	 group.add_thread(WorkStealing::getCore(i)->start());
	 }
	 group.join_all();*/
	//cout<<"start executeRec..."<<endl;
	manager->executeRec(noRect, rect, cells, oldstate);
	//cout<<"end executeRec"<<endl;
	manager->run();

}

void Recrystalization::fill_no_recrystalization_list(vector<cell> *list) {
	/*int sum = 0;
	 int step = HEIGHT/CORES;
	 boost::thread_group group;
	 while(sum<HEIGHT){
	 FillNoRecList* init = new FillNoRecList(sum,sum+step,list,cells);
	 WorkStealing::getCore(0)->addTask(init);
	 sum+=step;
	 }
	 for(int i=CORES-1;i>=0;i--){
	 group.add_thread(WorkStealing::getCore(i)->start());
	 }
	 group.join_all();*/
	//cout<<"fill no rect grains..."<<endl;
	//cout<<"start fillNoRectList"<<endl;
	manager->fillNoRectList(list, cells);
	manager->run();
	//cout<<"end fillNoRectList"<<endl;
	//cout<<"end fill no rect grains"<<endl;
}

void Recrystalization::randomRecGrains() {
	srand(time(NULL));
	for (int i = 1; i <= RECRYSTALIZATION_GRAINS; i++) {
		int x = rand() % HEIGHT;
		int y = rand() % WIDTH;
		if (is_on_the_board(x, y, cells)) {
			cells[x][y].id = -i;
			cells[x][y].energy = 0;
			recrystalizationList.push_back(cells[x][y]);
		} else {
			i--;
		}
	}
}

void Recrystalization::clean(vector<cell> *vect) {
	while (vect->size() > 0) {
		vect->erase(vect->begin());
	}
}

bool Recrystalization::is_on_the_board(int idx_i, int idx_j,
		cell** space_of_cells) {
	int *tab;
	int k = 0, i = 0, j = 0, endI = 0, endJ = 0;
	if (idx_i == 0 && idx_j == 0) {
		tab = new int[3];
		i = idx_i;
		endI = idx_i + 2;
		j = idx_j;
		endJ = idx_j + 2;
	} else if (idx_i == 0 && idx_j == WIDTH - 1) {
		tab = new int[3];
		i = idx_i;
		endI = idx_i + 2;
		j = idx_j - 1;
		endJ = idx_j + 1;
	} else if (idx_i == HEIGHT - 1 && idx_j == 0) {
		tab = new int[3];
		i = idx_i - 1;
		endI = idx_i + 1;
		j = idx_j;
		endJ = idx_j + 2;
	} else if (idx_i == HEIGHT - 1 && idx_j == WIDTH - 1) {
		tab = new int[3];
		i = idx_i - 1;
		endI = idx_i + 1;
		j = idx_j - 1;
		endJ = idx_j + 1;
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == 0) {
		tab = new int[5];
		i = idx_i - 1;
		endI = idx_i + 2;
		j = idx_j;
		endJ = idx_j + 2;
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == WIDTH - 1) {
		tab = new int[5];
		i = idx_i - 1;
		endI = idx_i + 2;
		j = idx_j - 1;
		endJ = idx_j + 1;
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == 0) {
		tab = new int[5];
		i = idx_i;
		endI = idx_i + 2;
		j = idx_j - 1;
		endJ = idx_j + 2;
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == HEIGHT - 1) {
		tab = new int[5];
		i = idx_i - 1;
		endI = idx_i + 1;
		j = idx_j - 1;
		endJ = idx_j + 2;
	} else {
		tab = new int[8];
		i = idx_i - 1;
		endI = idx_i + 2;
		j = idx_j - 1;
		endJ = idx_j + 2;
	}

	int m = j;
	while (i < endI) {
		while (j < endJ) {
			if (i == idx_i && j == idx_j) {
				j++;
				continue;
			}
			if (space_of_cells[i][j].id != space_of_cells[idx_i][idx_j].id) {
				return true;
			}
			tab[k] = space_of_cells[i][j].id;
			k++;
			j++;
		}
		i++;
		j = m;
	}
	return false;
}

void Recrystalization::saveToFile() {
	std::ofstream file;
	file.open("results.txt", ios::app);
	if (file.good()) {
		file<<"\n\n";
		file << "Recrystalization algorithm: space HeightxWidth: " << HEIGHT<< "x" << WIDTH << "\n";
		file << "number of recrystalization grains on the start: "<< NUMBER_OF_GRAINS << "\n";
		file<<"number of cores: "<<CORES<<"\n";
		int t = TASKS;
		file << "number of tasks: " <<t<<"\n";
		file << "time of execution algorithm: "<<duraction<<"\n";
		file.close();
	}
}

