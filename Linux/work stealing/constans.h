#ifndef CONSTANS_H_
#define CONSTANS_H_

#define HEIGHT 1000
#define WIDTH 1000
#define NUMBER_OF_IDS 900
#define NUMBER_OF_GRAINS 900
#define H 4
#define ENERGY_ON_THE_BOARD 2
#define ENERGY_ON_GRAIN 7
#define RECRYSTALIZATION_GRAINS 5
#define FLAG true
#define logg(a) if(FLAG == true)std::cout<<a<<std::endl;
#define loggErr(a,b) if(FLAG == true)std::cout<<a<<" error nr: "<<b<<std::endl;
#define loggTime(a,b) if(FLAG ==true)std::cout<<a<<" "<<b<<std::endl;
#define CORES boost::thread::hardware_concurrency()
#define TASKS 100; //number of tasks for one core to execution
typedef struct {
	int id;
	int idx_i;
	int idx_j;
	bool flag;
	int energy;
}cell;

typedef enum {
	INITIALIZE_IDS,
	CALCULATE_ENERGY,
	COPY_SPACES,
	EXECUTE_LIST,
	EXECUTE_REC,
	FILL_LIST,
	FILL_NO_RECT,
	INITIALIZE_ENERGY
}Tasks;

#endif
