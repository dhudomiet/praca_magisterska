#include "ExecuteRec.h"

boost::mutex ExecuteRec::mut;

ExecuteRec::ExecuteRec(void) {
}

ExecuteRec::ExecuteRec(int begin, int end, std::vector<cell> *noRect,
		std::vector<cell> *vect, cell** cells, cell** oldstate) {
	this->begin = begin;
	this->end = end;
	this->vect = vect;
	this->noRect = noRect;
	this->cells = cells;
	this->oldstate = oldstate;
}

ExecuteRec::~ExecuteRec(void) {
}

void ExecuteRec::start() {
}

void ExecuteRec::execute() {
	//cout<<"start calculate executeRec..."<<endl;
	for (int i = begin; i < end; i++) {
		cell grain = noRect->at(i);
		int tab[2];
		int *p = tab;
		cal_energy(grain.idx_i, grain.idx_j, p, oldstate);
		if (p[0] < 0) {
			int energy = 0;
			energy = p[1] + H;
			int energyRec = oldstate[grain.idx_i][grain.idx_j].energy + energy;
			energy = oldstate[grain.idx_i][grain.idx_j].energy;
			if (energyRec > energy) {
				cells[grain.idx_i][grain.idx_j].energy = 0;
				cells[grain.idx_i][grain.idx_j].id = p[0];
				boost::unique_lock<boost::mutex> lock(mut);
				vect->push_back(cells[grain.idx_i][grain.idx_j]);
				lock.unlock();
			}
		}
	}
	//cout<<"end calculate executeRec"<<endl;
}

void ExecuteRec::cal_energy(int idx_i, int idx_j, int * point, cell** space_of_cells) {
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
			tab[k++] = space_of_cells[i][j].id;
			j++;
		}
		i++;
		j = m;
	}
	int energy = 0;
	int id = -1;
	std::vector<int *> data;
	for (int i = 0; i < k; i++) {
		id = tab[i];
		if (id > 0) {
			continue;
		}
		int count = 0;
		energy = 0;
		if (data.size() > 0) {
			for (unsigned int i = 0; i < data.size(); i++) {
				if (id == data.at(i)[0]) {
					count = -1;
					break;
				}
			}
			if (count != -1) {
				for (int j = 0; j < k; j++) {
					if (tab[j] == id) {
						energy++;

					}
				}
				int * d = new int[2];
				d[0] = id;
				d[1] = energy;
				energy = 0;
				data.push_back(d);
			}
		} else {
			for (int j = 0; j < k; j++) {
				if (tab[j] == id) {
					energy++;

				}
			}
			int * d = new int[2];
			d[0] = id;
			d[1] = energy;
			energy = 0;
			data.push_back(d);
		}
	}
	if (data.size() > 0) {
		int * w = data.at(0);
		for (unsigned int i = 0; i < data.size(); i++) {
			for (unsigned int j = 0; j < data.size(); j++) {
				if (w[1] < data.at(j)[1]) {
					w = data.at(j);
				}
			}
			break;
		}
		point[0] = w[0];
		point[1] = w[1];
		delete[] tab;
	} else {
		point[0] = 0;
		point[1] = 0;
		delete[] tab;
	}

}

void ExecuteRec::toString() {
	std::cout << "execute task ExecuteRex..." << std::endl;
}
