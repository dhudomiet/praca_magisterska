#include "CopyGrows.h"


CopyGrows::CopyGrows(void)
{
}

CopyGrows::CopyGrows(int params[4], int** space, int** source){
	for(int i=0;i<4; i++){
		this->params[i] = params[i];
	}
	this->space = space;
	this->source = source;
}

CopyGrows::~CopyGrows(void)
{
	
}

void CopyGrows::start(){

}

void CopyGrows::execute(){
	int end1 = params[0]+params[1];
	int end2 = params[2]+params[3];
	for (int i = params[0]; i < end1; i++) {
		for (int j = params[2]; j < end2; j++) {
			space[i][j] = source[i][j];
		}
	}
}

void CopyGrows::toString(){
	cout<<"execute task copyGrows..."<<endl;
}
