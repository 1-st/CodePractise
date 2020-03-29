package main

import "sort"

func absInt(x int)int{
	if x>0{
		return x
	}else{
		return -x
	}
}


func threeSumClosest(nums []int,target int)int{
	sort.Ints(nums)
	var closestSum = nums[0]+nums[1]+nums[2]
	for k:=0;k<len(nums)-2;k++{
		//if nums[k+1]==nums[k]{//此处不应该剪去
		//	continue
		//}
		i,j:=k+1,len(nums)-1
		for i<j {
			if nums[k]+nums[i]+nums[j]==target{
				return target
			}else if nums[k]+nums[i]+nums[j]<target{
				if absInt(nums[k]+nums[i]+nums[j]-target)<absInt(closestSum-target){
					closestSum = nums[k]+nums[i]+nums[j]
				}
				for i<len(nums)-2&&nums[i+1]==nums[i]{
					i++
				}
				i++
			}else{
				if absInt(nums[k]+nums[i]+nums[j]-target)<absInt(closestSum-target){
					closestSum = nums[k]+nums[i]+nums[j]
				}
				for j>1&&nums[j-1]==nums[j]{
					j--
				}
				j--
			}
		}
	}
	return closestSum
}


func main(){

}
