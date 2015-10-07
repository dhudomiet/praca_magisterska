#ifndef CONSTANS_H_
#define CONSTANS_H_

#define HEIGHT 100
#define WIDTH 100
#define NUMBER_OF_IDS 100
#define H 4
#define ENERGY_ON_THE_BOARD 10
#define ENERGY_ON_GRAIN 7
#define RECRYSTALIZATION_GRAINS 5
#define FLAG true
#define logg(a) if(FLAG == true)std::cout<<a<<std::endl;
#define loggErr(a,b) if(FLAG == true)std::cout<<a<<" error nr: "<<b<<std::endl;
#define loggTime(a,b) if(FLAG ==true)std::cout<<a<<" "<<b<<std::endl;
#define CORES boost::thread::hardware_concurrency()
typedef struct {
	int id;
	int idx_i;
	int idx_j;
	bool flag;
	int energy;
}cell;

#endif