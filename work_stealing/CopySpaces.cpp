#include "CopySpaces.h"


CopySpaces::CopySpaces(void) : Task()
{
}

CopySpaces::CopySpaces(int begin, int end, cell** source, cell** space) : Task(){
	this->begin = begin;
	this->end = end;
	this->source = source;
	this->space = space;
}

CopySpaces::~CopySpaces(void)
{
}

void CopySpaces::start(){
	th = boost::thread(&CopySpaces::execute,this);
}

void CopySpaces::execute(){
	for(int i=begin;i<end;i++){
		for(int j=0;j<WIDTH;j++){
			space[i][j].id = source[i][j].id; 
			space[i][j].idx_i = source[i][j].idx_i;
			space[i][j].idx_j = source[i][j].idx_j;
			space[i][j].flag = source[i][j].flag;
			space[i][j].energy = source[i][j].energy;
		}
	}
}
