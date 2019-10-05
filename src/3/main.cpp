#include <DC/utils/table.hpp>
#include <DC/macro/file.hpp>
#include <DC/defer.hpp>
#include <vector>
#include <iostream>

int main(){
	F_IO;
	std::vector<char>X,Y;
	int count = 0;
	auto * target = &X;
	while(true){
		char buf='E';
		in.get(buf);
		count++;
		std::cout<<count<<":"<<buf<<" ";
		if(in.eof())
			break;
		else if(buf=='\n'){
			target = &Y;
			continue;
		}
		(*target).push_back(buf);
	}
	std::cout<<"X:";
	for(auto i = X.cbegin();i!=X.cend();i++){
		std::cout<<*i<<" ";
	}
	std::cout<<std::endl;
	std::cout<<"Y:";
	for(auto i = Y.cbegin();i!=Y.cend();i++){
		std::cout<<*i<<" ";
	}
	std::cout<<std::endl;

}
