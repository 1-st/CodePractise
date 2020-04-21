#include <iostream>
#include <climits>


//两数相除
class Solution {
public:
    int divide(int dividend, int divisor) {
        bool neg = !((dividend >= 0 && divisor > 0) || (dividend <= 0 && divisor < 0));
        unsigned long D = abs(dividend), d = abs(divisor) , dSave = d;
        unsigned long res = 0, weight = 1;
        if(D < d) return 0;
        while((d << 1u) < D){
            d <<= 1u;
            weight <<= 1u;
        }
        while(D >= dSave){
            D -= d;
            res += weight;
            while(d > D){
                d >>= 1u;
                weight >>= 1u;
            }
        }
        if(neg){
            if(-res < INT_MIN) return INT_MAX;
            else return (int)-res;
        }else{
            if(res > INT_MAX) return INT_MAX;
            else return (int)res;
        }
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
