
CLFAGS=-c -Wall

LIBS=-lboost_thread -lboost_system -lboost_system

BOOST=-L/usr/include

C++11=-std=c++0x

all: 
	g++ $(BOOST) $(C++11) BusyLeafs.cpp BusyLeafsManager.cpp CalculateEnergy.cpp CopyGrows.cpp CopySpaces.cpp ExecuteGrainGrow.cpp ExecuteList.cpp ExecuteRec.cpp FillList.cpp FillNoRecList.cpp GrainGrow.cpp InitializeEnergy.cpp InitializeIds.cpp InitializeSpace.cpp main.cpp MonteCarlo.cpp Recrystalization.cpp Task.cpp WorkStealing.cpp WorkStealingManager.cpp -o work_stealing $(LIBS)

#work_stealing: BusyLeafs.o main.o
#	g++ $(BOOST) $(C++11) BusyLeafs.o main.o -o work_stealing $(LIBS)

#main.o: main.cpp
#	g++ $(BOOST) $(C++11) -c main.cpp

#WorkStealing.o: WorkStealing.cpp
#	g++ $(BOOST) $(C++11) -c WorkStealing.cpp

#BusyLeafs.o: BusyLeafs.cpp 
#	g++ $(BOOST) $(C++11) -c  BusyLeafs.cpp

#Manager.o: Manager.cpp
#	g++ $(BOOST) $(C++11) -c Manager.cpp

#InitializeIds.o: InitializeIds.cpp
#	g++ $(C++11) -c InitializeIds.cpp

#CalculateEnergy.o: CalculateEnergy.cpp
#	g++ $(C++11) CalculateEnergy.cpp

#CopyGrows.o: CopyGrows.cpp
#	g++ $(C++11) -c CopyGrows.cpp


