# include <fstream>
# include <iostream>
# include "../include/defer.hpp"
// 矩阵链乘法
int main(){
	std::ifstream ifs("input.dat"); 
	std::ofstream ofs("output.dat");
	defer [&ofs,&ifs](){
		std::cout<<"one";
		ofs.close();
		ifs.close();
	};

	char bufc;
	while(true){
		bufc = ifs.get();
		if(ifs.eof())
			break;
		ofs<<bufc;
	}
	return 0;
}
