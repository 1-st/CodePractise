# include <fstream>
# include <iostream>
# include <DC/defer/defer.hpp>//mine
# include <DC/utils/macro.hpp>//mine
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
