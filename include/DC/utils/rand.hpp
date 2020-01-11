#ifndef _RAND_H_
#define _RAND_H_
#include <cstdlib>
#include <random>
#include <chrono>

double RandDouble(double min,double max){
	return ((rand()/double(RAND_MAX))*(max-min))+min;
}



void getRandomListOfInt(int bottom,int top,int k,int *arr){
    int arrLen = top-bottom+1;
    int * arrTemp = new int[arrLen]{};
    for(int i=0;i<arrLen;i++){
        arrTemp[i] = i+bottom;
    }
    for(int i=0;i<k;i++){
        int tempIndex = rand()%(arrLen-i)+i;
        arr[i] = arrTemp[tempIndex];

        int swap = arrTemp[tempIndex];
        arrTemp[tempIndex] = arrTemp[i];
        arrTemp[i] = swap;

    }
    delete[] arrTemp;
}


#define ReSetRandomSeed do{srand((unsigned)time(nullptr));}while(0)

#endif
