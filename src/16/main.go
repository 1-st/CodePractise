package main

import (
	"fmt"
)

func reverse(x int) int {
	var max = 1<<31-1
	var min = -(1<<31)
	y := 0
	for x!=0 {
		y = y*10 + x%10
		if !( min <= y && y <= max) {
			return 0
		}
		x /= 10
	}
	return y
}

func main(){
	fmt.Println(reverse(123))
}
