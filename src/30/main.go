package main

import (
	"fmt"
	"sort"
)
func threeSum(nums []int) [][]int {
	res := make([][]int,0)
	if len(nums)<3{
		return nil
	}
	sort.Ints(nums)
	if len(nums)==0||nums[0]>0||nums[len(nums)-1]<0 {
		return nil
	}
	for k:=0;k<len(nums)-2;k++{
		if nums[k]>0{
			break
		}
		target := 0-nums[k]
		if k>0&&nums[k]==nums[k-1]{
			continue
		}
		i,j:=k+1,len(nums)-1
		for i<j {
			if nums[i]+nums[j]==target{
				res = append(res,[]int{nums[k],nums[i],nums[j]})
				for i<j&&nums[i]==nums[i+1]{
					i++
				}
				for i<j&&nums[j]==nums[j-1]{
					j--
				}
				i++;j--
			}else if nums[i]+nums[j]<target{
				i++
			}else{
				j--
			}
		}
	}
	return res
}
func main(){
	fmt.Println(threeSum([]int{-1,0,1,2,-1,-4}))
}
