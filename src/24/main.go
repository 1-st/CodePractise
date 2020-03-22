package main

import (
	"container/list"
	"fmt"
)

func match(a byte,b byte)bool{
	if (a=='('&&b==')')||(a=='['&&b==']')||(a=='{'&&b=='}'){
		return true
	}
	return false
}

func isValid(s string) bool {
	var list  = list.New()
	for i:= range s{
		if list.Len()==0||!match(list.Back().Value.(byte),s[i]){
			list.PushBack(s[i])
		}else{
			list.Remove(list.Back())
		}
	}
	if list.Len()==0{
		return true
	}
	return false
}


func main(){
	fmt.Println(isValid("([])"))
}
