#include <iostream>
#include <vector>
#include "constans.h"
#include <boost\thread.hpp>
#include "MonteCarlo.h"
#include "Recrystalization.h"

using namespace std;
/*
class ehe {
public:
	ehe(int l, vector<int> d) : latecy(l), data(d){

	}
	void doSomethink() {
		for(int i=0;i<5;i++){
			cout<<"watek id: "<<boost::this_thread::get_id()<<" robi cos..."<<endl;
			mut.lock();
			cout<<"watek id: "<<boost::this_thread::get_id()<<" blokuje funkcje..."<<endl;
			boost::posix_time::seconds ms(latecy);
			boost::this_thread::sleep(ms);
			mut.unlock();
			stealData();
		}
	}
	void start(){
		th = boost::thread(&ehe::doSomethink,this);
	}
	void join(){
		th.join();
	}
	int getData(){
		mut.lock();
		cout<<"kradziez danych..."<<endl;
		int a = data.at(0);
		data.erase(data.begin());
		mut.unlock();
		return a;
	}
	void stealData(){
		//mut.lock();
		if(data.size() > 0){
			int a = watki->getData();
			data.push_back(a);
		}
		//mut.unlock();
	}
	vector<int> data;
	ehe* watki;
private:
	boost::thread th;
	boost::mutex mut;
	int latecy;
	
};*/

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
	//mc.monte_carlo_algorithm();
	Recrystalization rec;
	rec.recrystalization_algorithm();
	system("pause");
	return 0;



}

