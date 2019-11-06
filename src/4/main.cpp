#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <ctime>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>


#include <DC/utils/rand.hpp>
#include <DC/BitMap.hpp>
#include <DC/defer.hpp>
#include <DC/macro/file.hpp>
#include <DC/utils/Table.hpp>
#include <DC/utils/type.hpp>

/*
 *1.随机产生种群
 *2.判断个体是否符合最优化结果,符合,结束
 *3.依照映射函数选择适应度,低的直接淘汰
 *4.交叉,变异等,复制数据
 *5.返回2
 */
#define ARG_COUNT 10
#define REPRODUCTION_COUNT 100
#define CROSS_RATE_PERCENT 50
#define TARGET 1.0e-6

/*
 *
 *种群个体的接口
 *
 */
template <typename T>
class Individual
{
	public:
	virtual T getFitness();
	virtual void cross(Individual &);
	virtual void varies();
	virtual void init();
	virtual void print();
};



/*
 *模拟一个种群,个体由外部传入
 *
 */
template <class T>
struct Population
{
	/*
	 *初始种群
	 *
	 */
	std::vector<Individual<T>> *pop = nullptr ;
	/*
	 *种群总大小
	 *
	 */
	int64 size = 0;
	/*
	 *当前大小
	 *
	 */
	int64 cur_size = 0;
	/*
	 *
	 *种群适应度
	 *
	 */
	std::unique_ptr<std::vector<T>>  fitness = nullptr;
	/*
	 *构造函数,T是适应度
	 *
	 */
	explicit Population<T>(int64 s){
		this->pop = new std::vector<Individual<T>>[size]{};
		size = s;
		initAll();
		cur_size = size;
	}
	void Run(){
		fitness = std::make_unique<std::vector<T>>(new std::vector<T>{});
		for(int64_t i = 0;i < size;i++){
			fitness.push_back(pop[i].getFitness);
		}
	}
	/*
	 *1~100
	 *
	 */
	void select(int killRate){
		int killNum = size*killRate/100;
		auto sortFun = [](T a,T b){
			return a>b;
		};
		for(int64_t i = 0;i<size;i++){
			std::sort(pop->begin(),pop->end(),sortFun);
		}
		cur_size-=killNum;
	}
	void PrintAll(){
		for(uint64 i=0;i<pop->size();i++){
			pop[i].print();
		}
	};

	void initAll(){
			for(int i =0;i<pop->size();i++){
				pop[i].init();
			}
	}
};
int main(){
	F_IO;
	ReSetRandomSeed;
	// std::vector<std::pair<double,double>> bounds{};
	// for(int i=0;i<ARG_COUNT;i++){
	// 	bounds.push_back(std::make_pair<double,double>(-1.0,1.0));
	// }
	Population<double> r(REPRODUCTION_COUNT);
	BitMap map;
	map.Default4x(400,400).PenSize(5).Line(Pos{20,20},Pos{40,40}).Save("./output.bmp");
	return 0;
}
