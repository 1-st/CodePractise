package main

import "fmt"

func massage(nums []int) int {
	if len(nums)==0{
		return 0
	}
	var record = make([][]int,len(nums))
	for i:=0;i<len(nums);i++{
		record[i] = make([]int,len(nums))
	}
	var sums = make([]int,len(nums))
	sums[0] = nums[0]
	record[0][0] = 1
	for i:=1;i<len(nums);i++{
		if record[i-1][i-1]==0{
			for j:= 0;j<i-1;j++{
				record[i][j] = record[i-1][j]
			}
			record[i][i] = 1
			sums[i] = sums[i-1]+nums[i]
		}else{
			sumA := sums[i-1]
			var sumB int
			if i==1{
				sumB = nums[1]
			}else{
				sumB = sums[i-2]+nums[i]
			}
			if sumA>sumB{
				for j:= 0;j<i-1;j++{
					record[i][j] = record[i-1][j]
				}
				record[i][i] = 0
				sums[i] = sums[i-1]
			}else{
				for j:= 0;j<i-2;j++{
					record[i][j] = record[i-2][j]
				}
				record[i][i] = 1
				record[i][i-1] = 0
				if i==1 {
					sums[i] = nums[i]
				}else{
					sums[i] = sums[i-2]+nums[i]
				}
			}
		}
	}
	return sums[len(nums)-1]
}

func main(){
	fmt.Println(massage([]int{1,2,3,1}))
}
