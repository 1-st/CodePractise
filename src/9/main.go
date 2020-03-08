package main

import (
	"fmt"
)


type Element struct {
	next, prev *Element
	list *List
	Value int
}
func (e *Element) Next() *Element {
	if p := e.next; e.list != nil && p != &e.list.root {
		return p
	}
	return nil
}
func (e *Element) Prev() *Element {
	if p := e.prev; e.list != nil && p != &e.list.root {
		return p
	}
	return nil
}
type List struct {
	root Element // sentinel list element, only &root, root.prev, and root.next are used
	len  int     // current list length excluding (this) sentinel element
}
func (l *List) Init() *List {
	l.root.next = &l.root
	l.root.prev = &l.root
	l.len = 0
	return l
}

func NewList() *List { return new(List).Init() }

func (l *List) Len() int { return l.len }

func (l *List) Front() *Element {
	if l.len == 0 {
		return nil
	}
	return l.root.next
}

func (l *List) Back() *Element {
	if l.len == 0 {
		return nil
	}
	return l.root.prev
}

func (l *List) lazyInit() {
	if l.root.next == nil {
		l.Init()
	}
}

func (l *List) insert(e, at *Element) *Element {
	n := at.next
	at.next = e
	e.prev = at
	e.next = n
	n.prev = e
	e.list = l
	l.len++
	return e
}

func (l *List) insertValue(v int, at *Element) *Element {
	return l.insert(&Element{Value: v}, at)
}

func (l *List) remove(e *Element) *Element {
	e.prev.next = e.next
	e.next.prev = e.prev
	e.next = nil // avoid memory leaks
	e.prev = nil // avoid memory leaks
	e.list = nil
	l.len--
	return e
}


func (l *List) Remove(e *Element) int {
	if e.list == l {
		l.remove(e)
	}
	return e.Value
}


// PushBack inserts a new element e with value v at the back of list l and returns e.
func (l *List) PushBack(v int) *Element {
	l.lazyInit()
	return l.insertValue(v, l.root.prev)
}


type MaxQueue struct {
	data *List
	max *List
}


func Constructor() MaxQueue {
	return MaxQueue{
		NewList(),
		NewList(),
	}
}


func (this *MaxQueue) Max_value() int {
	if this.max.Len()==0{
		return -1
	}
	return this.max.Front().Value
}


func (this *MaxQueue) Push_back(value int)  {
	for this.max.Len()!=0&&this.max.Back().Value<value {
		this.max.Remove(this.max.Back())
	}
	this.max.PushBack(value)
	this.data.PushBack(value)
}


func (this *MaxQueue) Pop_front() int {
	if this.max.Len()==0 {
		return -1
	}
	if this.max.Front().Value == this.data.Front().Value{
		this.max.Remove(this.max.Front())
	}
	return this.data.Remove(this.data.Front())
}

func main(){
	obj:= Constructor()
	obj.Push_back(1)
	obj.Push_back(2)
	fmt.Println(obj.Max_value())
	fmt.Println(obj.Pop_front())
	fmt.Println(obj.Max_value())
	//var l =  list.New()
	//l.PushBack(data{2,3})
	//fmt.Println(l.Back().Value)

}
