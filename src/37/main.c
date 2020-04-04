#include <stdio.h>


int removeDuplicates(int* nums, int numsSize){
    if (numsSize==0){
        return 0;
    }
    int* p_r = nums;
    int* p_l = nums;
    int save = nums[0];
    while(p_r-nums<numsSize){
        if(*p_r!=save){
            save = *p_r;
            *++p_l = save;
        }
        p_r++;
    }
    return (int)(p_l-nums+1);
}


int main() {
    int A[0] = {};
    int size = removeDuplicates(A,0);
    for(int i=0;i<size;i++){
        printf("%d ",A[i]);
    }
    return 0;
}
