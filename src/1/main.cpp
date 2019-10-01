# include <fstream>
# include <iostream>
# include <defer/defer.hpp>
# include <utils/macro.hpp>
// 矩阵链乘法
int main(){
  F_IO
	char bufc;
	while(true){
		bufc = in.get();
		if(in.eof())
			break;
		out<<bufc;
	}
	return 0;
}
