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
//func mergeKLists(lists []*ListNode) *ListNode {
//	var res  *ListNode= nil
//	var q  = res
//	var listsNotNull []*ListNode
//	for k:= range lists{
//		if lists[k]!=nil{
//			listsNotNull = append(listsNotNull,lists[k])
//		}
//	}
//	lists = listsNotNull
//	for len(lists)>0{
//		var min = lists[0]
//		var minN = 0
//		for k := range lists{
//			if lists[k]!=min&&lists[k].Val<=min.Val{
//				min = lists[k]
//				minN = k
//			}
//		}
//		if res==nil{
//			res = min
//			q = res
//		}else{
//			q.Next = min
//			q = q.Next
//		}
//		lists[minN] = min.Next
//		if lists[minN]==nil{
//			lists = append(lists[:minN],lists[minN+1:]...)
//		}
//	}
//	return res
//}


//执行用时4ms
func mergeKLists(lists []*ListNode) *ListNode {
	length := len(lists)
	if length == 0 {
		return nil
	}
	if length == 1 {
		return lists[0]
	}
	return merge(lists, 0, length-1)
}

func merge(lists []*ListNode, left int, right int) *ListNode{
	if left == right {
		return lists[left]
	}
	mid := (left + right) / 2
	l1 := merge(lists, left, mid)
	l2 := merge(lists, mid+1, right)
	return mergeTwoLists(l1, l2)
}

func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode {
	var head *ListNode
	var p, q *ListNode
	if l1 == nil && l2 == nil {
		return nil
	}
	if l1 == nil {
		return l2
	}
	if l2 == nil {
		return l1
	}
	for {
		if l1 != nil && l2 != nil {
			if l1.Val < l2.Val {
				p = l1
				l1 = l1.Next
			} else {
				p = l2
				l2 = l2.Next
			}
			if q == nil {
				q = p
			} else {
				q.Next = p
				q = q.Next
			}
			if head == nil {
				head = p
			}
		} else if l1 != nil {
			p.Next = l1
			break
		} else if l2 != nil {
			p.Next = l2
			break
		} else {
			break
		}
	}
	return head
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