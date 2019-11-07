#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <ctime>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>


#include <DC/BitMap.hpp>
#include <DC/defer.hpp>
#include <DC/utils/Table.hpp>
#include <DC/utils/type.hpp>
#include <DC/utils/rand.hpp>


/*
 *
 *种群个体的抽象类
 *
 */
template <typename T>
class Individual
{
	public:
	/*
	 *
	 *个体的适应度
	 *
	 */
	T fitness;
	/*
	 *判断是否是最优解
	 *
	 */
	virtual bool isBest();
	/*
	 *
	 *得到个体的适应度,用于排序
	 *
	 */
	virtual void genFitness();
	/*
	 *交叉函数,产生子类
	 *
	 */
	virtual Individual xOverFNs(Individual &,int xOverRate);
	/*
	 *变异函数
	 */
	virtual void mutFNs();
	/*
	 *初始化个体
	 */
	virtual void init();
	/*
	 *打印个体值
	 *
	 */
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
	 *每次迭代存活的比例
	 *
	 */
	int SurviveRate = 100;
	/*
	 *初始种群
	 *
	 */
	std::unique_ptr<std::vector<Individual<T>>> pop = nullptr ;
	/*
	 *种群总大小
	 *
	 */
	int64 MaxSize = 0;
	/*
	 *
	 *种群适应度
	 *
	 */
	std::unique_ptr<std::vector<T>>  fitness = nullptr;
	/*
	 *构造函数,T是适应度的类型
	 *
	 */
	explicit Population<T>(int64 size,int64 surviveRate){
		SurviveRate = surviveRate;
		this->pop = new std::vector<Individual<T>>[size]{};
		MaxSize = size;
		for(int i =0;i<pop->size();i++){
				pop[i].init();
				pop[i].genFitness();
		}
	}
	/*
	 *迭代,返回迭代的次数
	 *
	 */
	int64 Iter(){
		int64 count = 0;
		while(true){
			if(checkBest()){
				break;
			}
			assert(pop->size()==MaxSize);
			select();
			assert(pop->size()<MaxSize);
			Repr();
			assert(pop->size()==MaxSize);
			count++;
		}
		return count;
	}
	/*
	 *检查种群中是否有满足要求的个体
	 *
	 */
	bool checkBest(){
		bool end = false;
		for(int i=0;i<MaxSize;i++){
			if(pop[i].isBest){
				end = true;
				break;
			}
		}
		return end;
	}
	/*
	 *产生新个体
	 *
	 */
	void Repr(){
		int createSum = MaxSize-pop->size();
		assert(createSum<MaxSize);
    unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
    std::shuffle (pop.begin (), pop.end (), std::default_random_engine (seed));
		int cur = 0;
		int curPlus1;
		int originSize = pop->size();
		for(int64 i = 0 ; i<createSum;i++){
			if(cur+1==originSize){
				curPlus1 = 0;
			}else{
				curPlus1 = cur;
			}
			pop->push_back(pop[cur].xoverFNs(pop[curPlus1]).mutFNs());
			if(cur>=originSize){
				cur=0;
			}else{
				cur++;
			}
		}
	}
	/*
	 *1~100
	 *
	 */
	void select(){
		int killNum = MaxSize*(100-SurviveRate)/100;
		auto sortFun = [](T a,T b){
			return a>b;//降序
		};
		std::sort(pop->begin(),pop->end(),sortFun);
		for(int i = 0;i < killNum;i++){
			pop->pop_back();
		}
		assert(pop->size()==MaxSize-killNum);
	}
	void PrintAll(){
		for(uint64 i=0;i<pop->size();i++){
			pop[i].print();
		}
	};
};
