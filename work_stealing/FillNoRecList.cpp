#include "FillNoRecList.h"


FillNoRecList::FillNoRecList(void) : Task()
{
}

FillNoRecList::FillNoRecList(int begin, int end, vector<cell> *vect, cell** cells) : Task(){
	this->begin = begin;
	this->end = end;
	this->vect = vect;
	this->cells = cells;
}

FillNoRecList::~FillNoRecList(void)
{
}

void FillNoRecList::start(){
	th = boost::thread(&FillNoRecList::execute,this);
}

void FillNoRecList::execute(){
	for(int i=begin;i<end;i++) {
		for(int j=0;j<WIDTH;j++) {
			if (cells[i][j].energy > 0) {
				vect->push_back(cells[i][j]);
			}
		}
	}
}
