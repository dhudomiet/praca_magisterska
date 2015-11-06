#include "InitializeSpace.h"


InitializeSpace::InitializeSpace(void)
{
}


InitializeSpace::~InitializeSpace(void)
{
	th->detach();
}

InitializeSpace::InitializeSpace(int params[4], int** space){
	for(int i=0;i<4;i++){
		this->params[i] = params[i];
	}
	this->space = space;
}

void InitializeSpace::start(){
	th = new boost::thread(&InitializeSpace::execute,this);
}

void InitializeSpace::execute(){
	int end1 = params[0]+params[1];
	int end2 = params[2]+params[3];
	for (int i = params[0]; i < end1; i++) {
		for (int j = params[2]; j < end2; j++) {
			space[i][j] = 0;
		}
	}
}

void InitializeSpace::toString(){
	cout<<"execute task initializeSpace..."<<endl;
}
