package main
func  partition(arr *[]int,l int,r int) int{
	var temp=(*arr)[l]
	for l<r{
		for l<r &&(*arr)[r]>=temp{
			r--
		}
		(*arr)[l]=(*arr)[r];
		for l<r && (*arr)[l]<=temp{
			l++
		}
		(*arr)[r]=(*arr)[l]
	}
	(*arr)[l]=temp
	return l
}
func getLeastNumbers(arr []int, k int) []int {
	var n=len(arr)
	if n==k {
		return arr
	}
	if n<k || k<=0 || n==0{
		return nil
	}
	var l,r=0,n-1;
	var index=partition(&arr,l,r);
	for index!=k-1 {
		if index>k-1 {
			r=index-1
		} else{
			l=index+1
		}
		index=partition(&arr,l,r);
	}
	return arr[0:k]
}


func main(){

}
