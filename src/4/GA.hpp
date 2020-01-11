#include <iostream>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>


#include <DC/defer.hpp>
#include <DC/utils/Table.hpp>
#include <DC/utils/type.hpp>
#include <DC/utils/rand.hpp>

/*
 *
 *种群个体的抽象类
 *
 */
template <typename T,typename P>
class Individual
{
public:
	T fitness;

	virtual bool isBest() = 0;

	virtual void genFitness() = 0;

	/*交叉函数,产生子代*/
	virtual Individual* xOverFNs(Individual &,int xOverRate) = 0;

	/*变异函数*/
	virtual Individual* mutFNs() = 0;

	/*初始化个体*/
	virtual void init() = 0;

	/*打印个体值*/
	virtual void print() = 0;

	/*获取个体基因*/
	virtual std::vector<P>& getGene() = 0;
};


