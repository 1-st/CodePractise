#include <DC/defer.hpp>
#include <DC/macro/file.hpp>
#include <cstdio>
#include <fstream>
#include <vector>
#include <memory>
#include <DC/utils/table.hpp>
#include <iostream>
// 矩阵链乘法
// 给定一个n个矩阵的阵列,求出最适合矩阵的一个括号化
// <A1,A2,A3,...,An>
// size of An:p[n-1]*p[n]
// c:cost
// d:division




//继承table,添加我们需要的方法
struct mytable :public table<int>{
	int * p;
	unsigned long p_size;
	//按p数组初始化
	mytable(std::vector<int>& v_p)
		:table(v_p.size()-1,v_p.size()-1),p_size(v_p.size())
	{
		this->p = new int[v_p.size()];
		for(unsigned long i =0;i<v_p.size();i++){
			p[i] = v_p[i];
		}

	}
	void calculate(void){
		for(unsigned long i = 0;i<this->X;i++){
			for(unsigned long j = 0;j<this->Y;j++){
				this->arr[i][j] = 23;
			}
		}
	}
	~mytable(){
		delete[] p;
	}
};

int main() {
  F_IO;
  std::vector<int> p{};
  int buf;
  while (true) {
    in >> buf;
    if (in.eof()) break;
    p.push_back(buf);
  }
	mytable m(p);
	m.calculate();
	for(size_t i=0;i<m.X;i++){
		for(size_t j=0;j<m.Y;j++){
			out<<m[i][j]<<" ";
		}
		out<<std::endl;
	}
  return 0;
}
