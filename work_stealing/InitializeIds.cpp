#include "InitializeIds.h"


InitializeIds::InitializeIds(void) : Task()
{
}


InitializeIds::~InitializeIds(void)
{
}

InitializeIds::InitializeIds(int begin, int end, cell** cells) : Task(){
	this->begin = begin;
	this->end = end;
	this->cells = cells;
}

void InitializeIds::start(){
	th = boost::thread(&InitializeIds::execute,this,begin,end,cells);
}
void InitializeIds::execute(int begin, int end, cell** cells){
	//cout<<"InitializeIds working..."<<endl;
	srand(time(NULL));
	end = (end>HEIGHT)? HEIGHT : end;
	for(int i=begin;i<end;i++){
		cells[i] = new cell[WIDTH];
		for(int j=0;j<WIDTH;j++){
			cells[i][j].id = rand()%NUMBER_OF_IDS;
			cells[i][j].energy = 0;
			cells[i][j].idx_j = j;
			cells[i][j].idx_i = i;
		}
	}
	//cout<<"InitializeIds end work"<<endl;
}
