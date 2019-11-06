#ifndef _RAND_H_
#define _RAND_H_
/*
 *从一个范围中得到随机双精度浮点数
 *
 */
#include <stdlib.h>

double RandDouble(double min,double max){
	return ((rand()/double(RAND_MAX))*(max-min))+min;
}


#define ReSetRandomSeed do{srand((unsigned)time(nullptr));}while(0)

#endif
