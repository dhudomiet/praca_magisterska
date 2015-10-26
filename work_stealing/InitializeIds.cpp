#include "InitializeIds.h"


InitializeIds::InitializeIds(int params[4], cell** cells) : engine(1), dist(1,NUMBER_OF_IDS), generator(engine,dist) {
	for(int i=0;i<4;i++){
		this->params[i] = params[i];
	}
	this->cells = cells;
	
}

InitializeIds::~InitializeIds(void)
{
	th->detach();
}

void InitializeIds::start(){
	th = new boost::thread(&InitializeIds::execute,this);
}

void InitializeIds::execute(){
	int end1 = params[0]+params[1];
	int end2 = params[2]+params[3];
	srand(time(NULL));
	for(int i=params[0];i<end1;i++){
		for(int j=params[2];j<end2;j++){
			cells[i][j].id = rand()%(NUMBER_OF_IDS)+1;
			cells[i][j].energy = 0;
			cells[i][j].idx_i = i;
			cells[i][j].idx_j = j;
		}
	}
}

void InitializeIds::toString(){
	cout<<"execute task InitializeIds..."<<endl;
}

