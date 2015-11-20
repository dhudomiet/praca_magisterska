#include "InitializeIds.h"

//boost::mt19937   InitializeIds::engine;
//boost::uniform_real <>   InitializeIds::dist(0,NUMBER_OF_IDS);
//boost::variate_generator <boost::mt19937, boost::uniform_real <> > InitializeIds::generator(engine,dist);
int InitializeIds::num = 0;

InitializeIds::InitializeIds(int params[4], cell** cells) : random_number_engine(++num), dice_distribution(1,NUMBER_OF_IDS){
	for(int i=0;i<4;i++){
		this->params[i] = params[i];
	}
	this->cells = cells;	
}

InitializeIds::~InitializeIds(void)
{
}

void InitializeIds::start(){
	execute();
}

void InitializeIds::execute(){
	int end1 = params[0]+params[1];
	int end2 = params[2]+params[3];
	auto roller = bind(dice_distribution,random_number_engine);
	for(int i=params[0];i<end1;i++){
		for(int j=params[2];j<end2;j++){
			//cout<<"execute index: begin1: "<<params[0]<<" end1: "<<end1<<" begin2: "<<params[2]<<" end2: "<<end2<<endl;
			cells[i][j].id = roller();
			cells[i][j].energy = 0;
			cells[i][j].idx_i = i;
			cells[i][j].idx_j = j;
			//cout<<"end execute"<<endl;
		}
	}
}

void InitializeIds::toString(){
	cout<<"execute task InitializeIds..."<<endl;
}

