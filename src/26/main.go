package main

func maxArea(height []int) int {
	var l = 0
	var r = len(height)-1
	var max = 0
	for l!=r{
		var shortOne int
		if height[l]<height[r]{
			shortOne = height[l]
		}else {
			shortOne = height[r]
		}
		if shortOne*(r-l)>max{
			max = shortOne*(r-l)
		}
		if shortOne == height[l]{
			l++
		}else{
			r--
		}
	}
	return max
}

func main(){

}
