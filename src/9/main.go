package main

import (
	"container/list"
	"fmt"
)
type data struct{
	index int
	value int
}

type MaxQueue struct {
	data *list.List
	max *list.List
	currentIndex int
}


func Constructor() MaxQueue {
	return MaxQueue{
		list.New(),
		list.New(),
		0,
	}
}


func (this *MaxQueue) Max_value() int {
	if this.max.Len()==0{
		return -1
	}
	return this.max.Back().Value.(data).value
}


func (this *MaxQueue) Push_back(value int)  {
	for this.max.Len()!=0&&this.max.Back().Value.(data).value<value {
		this.max.Remove(this.max.Back())
	}
	this.max.PushBack(data{this.currentIndex,value})
	this.data.PushBack(data{this.currentIndex,value})
	this.currentIndex++
}


func (this *MaxQueue) Pop_front() int {
	if this.max.Len()==0 {
		return -1
	}
	if this.max.Back().Value.(data).index == this.data.Back().Value.(data).index{
		this.max.Remove(this.max.Back())
	}
	return this.data.Remove(this.data.Back()).(data).value
}

func main(){
	obj:= Constructor()
	obj.Push_back(1)
	obj.Push_back(2)
	fmt.Println(obj.Max_value())
	//var l =  list.New()
	//l.PushBack(data{2,3})
	//fmt.Println(l.Back().Value)

}
