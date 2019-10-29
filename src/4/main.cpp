#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <ctime>
#include <memory>
#include <vector>
#include <utility>

#include <DC/defer.hpp>
#include <DC/macro/file.hpp>
#include <DC/utils/Table.hpp>
#include <DC/utils/type.hpp>

//目标函数:简单的求平方和
//遗传算法求解,并把某些迭代的结果输出
#define ARG_COUNT 10
#define REPRODUCTION_COUNT 100
#define CROSS_RATE_PERCENT 50
#define TARGET 1.0e-6
struct Reproduction
{
	std::vector<double> *pop = nullptr ;
	uint64 size = 0;
	explicit Reproduction(uint64 size,std::vector<std::pair<double,double>> * bounds){
		this->pop = new std::vector<double>[size]{};
		this->size = size;
		init(bounds);
	}
	~Reproduction(){
		delete[] this->pop;
	}
	void Run(){
		std::unique_ptr<std::vector<double>> fitness(new std::vector<double>);

	}
	void Print(){
		for(uint64 i=0;i<this->size;i++){
			for(int j =0;j<ARG_COUNT;j++){
				printf("%lf ",this->pop[i][j]);
			}
			printf("\n");
		}
	};
	//getTheRandomDoubleFromRange
	double getRandDBFrRang(double min,double max){
		return ((rand()/double(RAND_MAX))*(max-min))+min;
	}
	void init(std::vector<std::pair<double,double>> * bounds){
			uint64 b_size = bounds->size();
			for(uint64 i = 0 ;i<this->size;i++){
				for(uint64 j =0;j<b_size;j++){
					this->pop[i].push_back(this->getRandDBFrRang((*bounds)[i].first,(*bounds)[i].second));
				}
			}
	}
};
int main(){
	F_IO;
	srand((unsigned)time(nullptr));
	std::vector<std::pair<double,double>> bounds{};
	for(int i=0;i<ARG_COUNT;i++){
		bounds.push_back(std::make_pair<double,double>(-1.0,1.0));
	}
	Reproduction r(REPRODUCTION_COUNT,&bounds);
	
	return 0;
}
