#include "./GA.hpp"
#include <DC/utils/rand.hpp>
#include <DC/macro/file.hpp>
#include <cmath>
/*
 *种群个体数
 */
#define REPRODUCTION_COUNT 100
/*
 *交叉的百分比
 *
 */
#define CROSS_RATE_PERCENT 50
/*
 *
 *存活的百分比
 *
 */
#define SURVIVE_RATE 50
//TODO
/*
 *实现Individual抽象类
 *
 */
using geneCast = std::vector<double>*;

class param10x :public Individual<double>{
public:
	~param10x(){
		delete (geneCast)gene;
		gene = nullptr;
	}
	bool isBest(){
		return fitness>100;
	}
	void genFitness(){
		double sum = 0;
		for(int i=0;i<10;i++){
			sum+=pow((*(geneCast)gene)[i],2);
		}
		fitness = 1/sum;
	};
	Individual * xOverFNs(Individual & another,int xOverRate){
		auto newgene = new std::vector<double>{};
		for(int i =0;i<10;i++){
			newgene->push_back((*(geneCast)gene)[i]);
		}
		assert(newgene->size()==10);
		unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
		std::shuffle (
				((geneCast)newgene)->begin (),
				((geneCast)newgene)->begin (), 
				std::default_random_engine (seed)
		);
		int xOverCount = xOverRate/100*10;
		for(int i=0;i<xOverCount;i++){
			(*(geneCast)newgene)[i] = (*(geneCast)another.gene)[i];
		}
		auto newParam10x = new param10x();
		newParam10x->gene = newgene;
		return newParam10x;
	};
	//TODO
	// Individual * mutFNs(){
	// };
	void init(){
		gene = (std::vector<double>*) new std::vector<double>{};
		for(int i = 0;i<10;i++){
			((std::vector<double>*)gene)->push_back(RandDouble(-100,100));
		}
	};
	void print(){
		std::cout<<"gene:";
		for(int i=0;i<10;i++){
			std::cout<<"-"<<(*((std::vector<double> * )gene))[i];
		}
		std::cout<<"\n";
	};

};
int main(){

	return 0;
}
