#include "InitializeIds.h"


InitializeIds::InitializeIds(void) : Task()
{
}

InitializeIds::InitializeIds(int begin, int end, cell** cells) : Task(){
	this->begin = begin;
	this->end = end;
	this->cells = cells;
}

InitializeIds::~InitializeIds(void)
{
	th.detach();
}

void InitializeIds::start(){
	th = boost::thread(&InitializeIds::execute,this);
}

void InitializeIds::execute(){
	boost::mt19937 type;
	boost::uniform_int<> numbers( 1, NUMBER_OF_IDS);
	boost::variate_generator< boost::mt19937, boost::uniform_int<> > dice(type, numbers);
	for(int i=begin;i<end;i++){
		cells[i] = new cell[WIDTH];
		for(int j=0;j<WIDTH;j++){
			cells[i][j].id = dice();
			cells[i][j].energy = 0;
			cells[i][j].idx_i = i;
			cells[i][j].idx_j = j;
		}
	}
}
