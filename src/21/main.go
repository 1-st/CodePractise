package main

import (
	"container/list"
	"fmt"
)

func isPalindrome(x int) bool {
	if x<0 {
		return false
	}
	var deq = list.New()
	for x>=10 {
		i:= x%10
		deq.PushBack(i)
		x/=10
	}
	deq.PushBack(x)
	for deq.Len()>1 {
		var front = *deq.Front()
		var back = *deq.Back()
		if front.Value!=back.Value{
			return false
		}
		deq.Remove(deq.Front())
		deq.Remove(deq.Back())
	}
	return true
}

func main(){
	fmt.Println(isPalindrome(1221))
}
