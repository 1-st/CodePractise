# include <fstream>
# include <iostream>
// 矩阵链乘法
int main(){
	std::ifstream ifs("input.dat"); 
	std::ofstream ofs("output.dat");
	char str[256];
	while(ifs.good()){
		ifs.getline(str,256);
		ofs<<str<<std::endl;
	}
	ifs.close();
	ofs.close();
	return 0;
}
