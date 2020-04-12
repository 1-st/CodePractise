#include <iostream>
#include <string>

using namespace std;



//class Solution {
//public:
//    int lengthOfLastWord(string s) {
//        istringstream ss(s);
//        bool flag=false;
//        while(ss>>s){
//            flag=true;
//        }
//        if(flag)
//            return s.size();
//        else
//            return 0;
//    }
//};


class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = (int)s.size()-1;
        while(n>0){
            if(s[n]!=' '){
                int nn = n;
                while(nn>=0){
                    if(nn==0&&n>0){
                        return n-nn;
                    }
                    if(s[nn]==' '&&nn<n-1) {
                        return n-nn-1;
                    }else{
                        nn--;
                    }
                }
            }
            n--;
        }
        return 0;
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
