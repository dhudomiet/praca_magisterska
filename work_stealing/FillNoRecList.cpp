#include "FillNoRecList.h"

boost::mutex FillNoRecList::mut;

FillNoRecList::FillNoRecList(void) : Task()
{
}

FillNoRecList::FillNoRecList(int params[4], vector<cell> *vect, cell** cells) : Task(){
	for(int i=0;i<4;i++)
		this->params[i]=params[i];
	this->vect = vect;
	this->cells = cells;
}

FillNoRecList::~FillNoRecList(void)
{
}

void FillNoRecList::start(){
	th = new boost::thread(&FillNoRecList::execute,this);
}

void FillNoRecList::execute(){
	int end1 = params[0]+params[1];
	int end2 = params[2]+params[3];
	//cout<<end1<<"  "<<end2<<endl;
	for(int i=params[0];i<end1;i++) {
		for(int j=params[2];j<end2;j++) {
			if (cells[i][j].energy > 0) {
				mut.lock();
				vect->push_back(cells[i][j]);
				mut.unlock();
			}
		}
	}
}

void FillNoRecList::toString(){
	cout<<"execute task FillNoRecList..."<<endl;
}
