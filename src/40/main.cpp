#include <iostream>
#include <vector>


using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int p_l = 0,p_r = 0;
        while(p_r<nums.size()){
            if(nums[p_r]!=val){
                nums[p_l++] = nums[p_r];
                p_r++;
            }else{
                p_r++;
            }
        }
        return p_l;
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
