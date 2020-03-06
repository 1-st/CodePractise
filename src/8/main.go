package main

import (
	"fmt"
	"sort"
	)
type intSlice []int
func (c intSlice) Len() int {
	return len(c)
}
func (c intSlice) Swap(i, j int) {
	c[i], c[j] = c[j], c[i]
}
func (c intSlice) Less(i, j int) bool {
	return c[i] <c[j]
}

func twoSum(nums []int, target int) []int {
	lgh := len(nums)
	sortedNums := make([]int,lgh)
	copy(sortedNums,nums)
	sort.Sort(intSlice(sortedNums))
	l := 0
	r := lgh-1
	for r>0{
		x:=target-sortedNums[r]
		index := sort.SearchInts(sortedNums[:r],x)
		if sortedNums[index]==x{
			l = index
			break
		}
		r--
	}
	var res  = make([]int,2)
	res[0]=-1
	res[1]=-1
	for i:=0;i<lgh;i++{
		if nums[i] == sortedNums[l]&&res[0]==-1{
			res[0] = i
		}else if nums[i] == sortedNums[r]&&res[1]==-1{
			res[1] = i
		}
	}
	if res[0] >res[1]{
		res[0],res[1] = res[1],res[0]
	}
	return res
}

func main(){
	fmt.Println(twoSum([]int{2,5,5,11},10))
}
