package main

import (
	"fmt"
	"math/rand"
)
//func majorityElement(nums []int) int {
//	var last, count int
//	for _, v := range nums {
//		if count == 0 {
//			last = v
//			count = 1
//			continue
//		}
//		if last == v {
//			count++
//		} else {
//			count--
//		}
//	}
//	return last
//}
func majorityElement(nums []int) int {
	length := len(nums)
	maxCount:= 1
	max := nums[0]
	if length <= 20{
		dist := make(map[int]int)
		for i:= 0;i<length;i++{
			if _,ok := dist[nums[i]];!ok{
				dist[nums[i]] = 1
			}else{
				dist[nums[i]]+=1
				if dist[nums[i]]>maxCount{
					maxCount = dist[nums[i]]
					if nums[i]!=max{
						max = nums[i]
					}
				}
			}
		}
		return max
	}

	for{
		sample := make(map[int]int)
		for i:=0;i<10;i++{
			index := rand.Intn(length)
			if _,ok:=sample[nums[index]];!ok{
				sample[nums[index]] = 1
			}else{
				sample[nums[index]] ++
			}
		}
		var max int
		var maxCount = 1
		for k,v:= range sample{
			if v >maxCount{
				maxCount = v
				max = k
			}
		}
		var count = 0
		for i:=0;i<length;i++{
			if nums[i] == max{
				count++
			}
		}
		if count > length/2{
			return max
		}
	}
}


func main(){
	fmt.Println(
		majorityElement([]int{1,2,3,4,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,1,2,3,}))
}
