# include <fstream>
# include <iostream>
# include <defer/defer.hpp>
// 矩阵链乘法
int main(){
	std::ifstream input("input.dat"); 
	std::ofstream output("output.dat");
	defer [&output,&input](){
		output.close();
		input.close();
	};

	char bufc;
	while(true){
		bufc = input.get();
		if(input.eof())
			break;
		output<<bufc;
	}
	return 0;
}
