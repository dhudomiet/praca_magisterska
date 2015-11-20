#include <iostream>
#include <vector>
#include "constans.h"
#include <boost/thread.hpp>
#include "MonteCarlo.h"
#include "Recrystalization.h"
#include "GrainGrow.h"
#include <thread>

using namespace std;


void doSomethink(/*int** tab, int beg1, int end1,int beg2,int end2*/) {
	/*for(int i=beg1;i<end1;i++){
		for(int j=beg2;j<end2;j++){
		tab[i][j] = 1;
		}
	}*/
	cout<<"hehe"<<endl;
		
	
}


int main(){
	/*vector<int> d1,d2;
	d1.push_back(2);
	d1.push_back(5);
	d2.push_back(3);
	d2.push_back(5);
	ehe watek1(2,d1);
	ehe watek2(0,d2);
	watek1.watki = &watek2;
	watek2.watki = &watek1;
	watek1.start();
	watek2.start();
	watek2.join();*/
	//MonteCarlo mc;
	/*int **tab = new int*[10];
	for(int i=0;i<10;i++){
		tab[i] = new int[10];
	}
	boost::thread_group group;
	group.add_thread(new boost::thread(doSomethink,tab,0,5,0,5));
	group.add_thread(new boost::thread(doSomethink,tab,0,5,5,10));
	group.add_thread(new boost::thread(doSomethink,tab,5,10,0,5));
	group.add_thread(new boost::thread(doSomethink,tab,5,10,5,10));
	group.join_all();
	cout<<"cipeczka"<<endl;
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			cout<<tab[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
	//boost::thread_group group;
	//thread th = thread(doSomethink);
	//group.add_thread(&th);
	//MonteCarlo mc;
	//mc.monte_carlo_algorithm();
	//mc.~MonteCarlo();
	Recrystalization rec;
	rec.recrystalization_algorithm();
	//Grain_grow g;
	//g.grain_grow_algorithm();
	return 0;



}

