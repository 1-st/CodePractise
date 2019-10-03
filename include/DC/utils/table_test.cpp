#include <cstdio>
#include "table.hpp"
#include <iostream>
int main(){
	table<int> n(23,233);
	printf("%lu",n.X);
	printf("%lu",n.Y);
	printf("%d",n[n.X-1][n.Y-1]);
	for(unsigned long i=0;i<n.X;i++){
		for(unsigned long j=0;j<n.Y;j++){
			printf("%d",n[i][j]);
		}
	}


}
