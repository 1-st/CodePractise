package main

type TreeNode struct {
      Val int
      Left *TreeNode
      Right *TreeNode
 }
var sum = 0

func diameter(root *TreeNode) int {
	if root==nil {
		return 0
	}
	left :=diameter(root.Left)
	right :=diameter(root.Right)
	lrSum:= left+right
	if lrSum>sum{
		sum = lrSum
	}
	if left>right{
		return left+1
	}else{
		return right+1
	}
}

func diameterOfBinaryTree(root *TreeNode) int {
	//sum = 0
	diameter(root)
	return sum
}
func main(){
//leetcode bug,全局变量在执行时要初始化
}
