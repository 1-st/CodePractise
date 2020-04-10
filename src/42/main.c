#include <stdio.h>

int searchInsert(int* nums, int numsSize, int target){
    int p = 0;
    while(nums[p++]<target){
        if(p==numsSize){
            return p;
        }
    };
    return p-1;
}
int main() {
    printf("Hello, World!\n");
    return 0;
}
