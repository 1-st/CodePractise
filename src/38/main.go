package main

import "fmt"

type ListNode struct {
	Val int
	Next *ListNode
}

func initList(l *[]*ListNode,ints [][]int){
	for _,i:= range ints{
		var newL = ListNode{}
		var p = &newL
		for k,j:= range i{
			if k!= len(i)-1{
				p.Val = j
				p.Next = &ListNode{}
				p = p.Next
			}else{
				p.Val = j
				p.Next = nil
			}
		}
		*l = append(*l,&newL)
	}
}

//执行用时500ms+,极其垃圾
func mergeKLists(lists []*ListNode) *ListNode {
	var res  *ListNode= nil
	var q  = res
	var listsNotNull []*ListNode
	for k:= range lists{
		if lists[k]!=nil{
			listsNotNull = append(listsNotNull,lists[k])
		}
	}
	lists = listsNotNull
	for len(lists)>0{
		var min = lists[0]
		var minN = 0
		for k := range lists{
			if lists[k]!=min&&lists[k].Val<=min.Val{
				min = lists[k]
				minN = k
			}
		}
		if res==nil{
			res = min
			q = res
		}else{
			q.Next = min
			q = q.Next
		}
		lists[minN] = min.Next
		if lists[minN]==nil{
			lists = append(lists[:minN],lists[minN+1:]...)
		}
	}
	return res
}


func main(){
	l := make([]*ListNode,0)
	initList(&l,[][]int{{1,4,5},{1,3,4},{2,6}})
	longL:= mergeKLists(l)
	var p = longL
	for p!=nil {
		fmt.Printf("%d ",p.Val)
		p = p.Next
	}
}