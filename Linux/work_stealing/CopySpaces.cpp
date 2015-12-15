#include "CopySpaces.h"


CopySpaces::CopySpaces(void) : Task()
{
}

CopySpaces::CopySpaces(int params[4], cell** source, cell** space) : Task(){
	for(int i=0;i<4;i++){
		this->params[i] = params[i];
	}
	this->source = source;
	this->space = space;
}

CopySpaces::~CopySpaces(void)
{
	
}

void CopySpaces::start(){
	execute();
}

void CopySpaces::execute(){
	int end1 = params[0]+params[1];
	int end2 = params[2]+params[3];
	for(int i=params[0];i<end1;i++){
		for(int j=params[2];j<end2;j++){
			space[i][j].id = source[i][j].id; 
			space[i][j].idx_i = source[i][j].idx_i;
			space[i][j].idx_j = source[i][j].idx_j;
			space[i][j].flag = source[i][j].flag;
			space[i][j].energy = source[i][j].energy;
		}
	}
}

void CopySpaces::toString(){
	cout<<"execute task CopySpaces..."<<endl;
}
