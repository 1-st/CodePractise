#ifndef _RAND_H_
#define _RAND_H_
#include <stdlib.h>
#include <random>
#include <chrono>

double RandDouble(double min,double max){
	return ((rand()/double(RAND_MAX))*(max-min))+min;
}


#define ReSetRandomSeed do{srand((unsigned)time(nullptr));}while(0)

#endif
