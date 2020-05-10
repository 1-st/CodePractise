#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int max = nums[0];
        int cur = nums[0];
        for(int i=1;i < n;i++){
            if(nums[i]+cur<nums[i]){
                cur = nums[i];
            }else{
                cur = nums[i]+cur;
            }
            if(cur>max){
                max = cur;
            }
        }
        return max;
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
