package main

import "fmt"

func distributeCandies(candies int, num_people int) []int {
	var p =num_people
	var res = make([]int,num_people)
	var n int
	var sum int
	for n=1;;n++ {
		sumNext :=p*(p+1)/2*n+p*p*(n-1)*n/2
		if sumNext<candies{
			sum = sumNext
		}else{
			n--
			break
		}
	}
	candies-=sum
	var a1 = n + n*(n-1)/2*p
	if a1!=0{
		for i:=0;i<p;i++{
			res[i] = a1+i*n
		}
	}
	var i = n*p+1
	for j:=0;j<p;j++{
		if candies-(i+j)>=0{
			res[j]+=i+j
			candies-= i+j
		}else{
			res[j]+=candies
			break
		}
	}
	return res
}
func main(){
	fmt.Println(distributeCandies(999,2))
}
