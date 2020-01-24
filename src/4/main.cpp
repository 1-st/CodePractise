#include "./GA.hpp"
#include <code_practise/utils/rand.hpp>
#include <code_practise/macro/file.hpp>
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


using namespace std;

class param10x : public Individual<double, double> {
public:
    param10x() = default;

    vector<double> gene;

    param10x(param10x const &from) : Individual(from) {
      this->gene = from.gene;
    }

    explicit param10x(vector<double> &gene) {
      this->gene = gene;
    }

    ~param10x() override = default;

    bool isBest() override {
      return Individual::fitness < 10;
    }

    void genFitness() override {
      double sum = 0;
      for (int i = 0; i < 10; i++) {
        sum += pow((gene)[i], 2);
      }
      Individual::fitness = sum;
    };

    Individual *xOverFNs(Individual &another, int xOverRate) override {
      auto newGene = new std::vector<double>{};
      for (int i = 0; i < 10; i++) {
        newGene->push_back(gene[i]);
      }

      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::shuffle(newGene->begin(), newGene->end(), std::default_random_engine(seed));

      int xOverCount = xOverRate / 100 * 10;

      for (int i = 0; i < xOverCount; i++) {
        (*newGene)[i] = another.getGene()[i];
      }
      auto newParam10x = new param10x(*newGene);
      delete newGene;
      return newParam10x;
    };

    Individual *mutFNs() override {
      int mutCount = 2;
      int *arr = new int[mutCount]{};
      getRandomListOfInt(0, 9, 2, arr);
      for (int i = 0; i < mutCount; i++) {
        gene[arr[i]] = RandDouble(-100, 100);
      }
      delete[] arr;
      return this;
    };

    void init() override {
      for (int i = 0; i < 10; i++) {
        gene.push_back(RandDouble(-100, 100));
      }
    };

    void print() override {
      std::cout << "gene:";
      for (int i = 0; i < 10; i++) {
        std::cout << gene[i] << "  ";
      }
      std::cout << "\n";
    };

    std::vector<double> &getGene() override {
      return this->gene;
    }
};


template<typename T, typename P>
class Population {
public:

    /*每次迭代存活的比例*/
    int SurviveRate = 50;

    /*种群*/
    vector<param10x> pop{};

    /*种群最大大小*/
    int MaxSize = 0;

    /*构造函数,T是适应度的类型*/
    explicit Population<T, P>(int size, int surviveRate) {
      SurviveRate = surviveRate;
      MaxSize = size;
      pop.resize(MaxSize);
      for (int i = 0; i < pop.size(); i++) {
        pop[i].init();
        pop[i].genFitness();
      }
    }

    ~Population() = default;

    /*迭代,返回迭代的次数*/
    int Iter() {
      int count = 0;
      while (true) {
        for (int i = 0; i < pop.size(); i++) {
          pop[i].genFitness();
        }
        if (checkBest()) {
          break;
        }
        if (pop.size() != MaxSize) {
          cout << "迭代错误";
          exit(1);
        }
        select();
        if (pop.size() >= MaxSize) {
          cout << "迭代错误";
          exit(1);
        }
        repr();
        if (pop.size() != MaxSize) {
          cout << "迭代错误";
          exit(1);
        }
        count++;
      }
      return count;
    }

    void PrintAll() {
      for (uint64_t i = 0; i < pop.size(); i++) {
        pop[i].print();
      }
    };

private:
    /*检查种群中是否有满足要求的个体*/
    bool checkBest() {
      double biggest = -1;

      for (int i = 0; i < MaxSize; i++) {
        if (pop[i].fitness > biggest) {
          biggest = pop[i].fitness;
        }
        if (pop[i].isBest()) {
          cout << "最佳适应度:" << pop[i].fitness << endl;
          cout << "最佳个体:";
          pop[i].print();
          cout << endl;
          return true;
        }
      }
      cout << biggest << endl;
      return false;
    }

    /*产生新个体*/
    void repr() {
      int numToCreate = MaxSize - pop.size();
      if (numToCreate >= MaxSize) {
        cout << "error:Repr()";
        exit(1);
      }
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::shuffle(pop.begin(), pop.end(), std::default_random_engine(seed));

      int cur = 0;
      int curNext;
      int originSize = pop.size();
      for (int64_t i = 0; i < numToCreate; i++) {
        curNext = (cur + 1 == originSize) ? 0 : cur + 1;
        auto *newIndividual = (param10x *) ((pop[cur].xOverFNs(pop[curNext], CROSS_RATE_PERCENT))->mutFNs());
        pop.push_back(*newIndividual);
        delete newIndividual;
        cur = (cur + 1 == originSize) ? 0 : cur + 1;
      }
    }

    /*选择*/
    void select() {
      int killNum = MaxSize * (100 - SurviveRate) / 100;
      auto sortFun = [](const param10x &a, const param10x &b) {
          return a.fitness < b.fitness;
      };
      std::sort(pop.begin(), pop.end(), sortFun);
      for (int i = 0; i < killNum; i++) {
        pop.pop_back();
      }
    }

};


int main() {
  Population<double, double> p(100, 50);
  p.PrintAll();
  int count = p.Iter();
  cout << "==================================迭代次数:" << count << "===========================";
  cout << "求解方程:x1^2+x2^2+x3^2+x4^2+x5^2+x6^2+x7^2+x8^2+x9^2+x10^2=0" << endl;
  return 0;
}
