# include "../include/defer.hpp"
int main(){
	int a= 2;

	defer [&a](){
		a=3;
	};

	return 0;
}
