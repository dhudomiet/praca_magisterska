################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../BusyLeafs.o \
../main.o 

CPP_SRCS += \
../BusyLeafs.cpp \
../BusyLeafsManager.cpp \
../CalculateEnergy.cpp \
../Cell.cpp \
../CopyGrows.cpp \
../CopySpaces.cpp \
../ExecuteGrainGrow.cpp \
../ExecuteList.cpp \
../ExecuteRec.cpp \
../FillList.cpp \
../FillNoRecList.cpp \
../GrainGrow.cpp \
../InitializeEnergy.cpp \
../InitializeIds.cpp \
../InitializeSpace.cpp \
../Manager.cpp \
../MonteCarlo.cpp \
../Recrystalization.cpp \
../Task.cpp \
../WorkStealing.cpp \
../WorkStealingManager.cpp \
../main.cpp 

OBJS += \
./BusyLeafs.o \
./BusyLeafsManager.o \
./CalculateEnergy.o \
./Cell.o \
./CopyGrows.o \
./CopySpaces.o \
./ExecuteGrainGrow.o \
./ExecuteList.o \
./ExecuteRec.o \
./FillList.o \
./FillNoRecList.o \
./GrainGrow.o \
./InitializeEnergy.o \
./InitializeIds.o \
./InitializeSpace.o \
./Manager.o \
./MonteCarlo.o \
./Recrystalization.o \
./Task.o \
./WorkStealing.o \
./WorkStealingManager.o \
./main.o 

CPP_DEPS += \
./BusyLeafs.d \
./BusyLeafsManager.d \
./CalculateEnergy.d \
./Cell.d \
./CopyGrows.d \
./CopySpaces.d \
./ExecuteGrainGrow.d \
./ExecuteList.d \
./ExecuteRec.d \
./FillList.d \
./FillNoRecList.d \
./GrainGrow.d \
./InitializeEnergy.d \
./InitializeIds.d \
./InitializeSpace.d \
./Manager.d \
./MonteCarlo.d \
./Recrystalization.d \
./Task.d \
./WorkStealing.d \
./WorkStealingManager.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


