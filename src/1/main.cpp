# include <fstream>
# include <iostream>
# include <defer/defer.hpp>
# include <utils/macro.hpp>
// 矩阵链乘法
int main(){
  F_IO
	char bufc;
	while(true){
		bufc = input.get();
		if(input.eof())
			break;
		output<<bufc;
	}
	return 0;
}
