#include <iostream>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>


#include <code_practise/utils/defer.hpp>
#include <code_practise/utils/table.hpp>
#include <code_practise/utils/rand.hpp>

/*
 *
 *种群个体的抽象类
 *
 */
template<typename T, typename P>
class Individual {
public:
    T fitness;

    virtual bool isBest() = 0;

    virtual void genFitness() = 0;

    /*交叉函数,产生子代*/
    virtual Individual *xOverFNs(Individual &, int xOverRate) = 0;

    /*变异函数*/
    virtual Individual *mutFNs() = 0;

    /*初始化个体*/
    virtual void init() = 0;

    /*打印个体值*/
    virtual void print() = 0;

    /*获取个体基因*/
    virtual std::vector<P> &getGene() = 0;

    virtual ~Individual() = default;;
};


