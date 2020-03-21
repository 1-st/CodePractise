package main

import "fmt"
// 动态规划 ,另有有限状态机//failed
func isMatch(s string, p string) bool {
	dp := make([][]int, len(s)+1)
	for i := 0; i <= len(s); i++ {
		dp[i] = make([]int, len(p)+1)
	}
	return isMatchCore(s, p, 0, 0, dp)
}
func isMatchCore(s, p string, i, j int, dp [][]int) bool {
	if dp[i][j] == 1 {
		return true
	} else if dp[i][j] == -1 {
		return false
	}
	flag := false
	if j == len(p) {
		if i == len(s) {
			flag = true
		} else {
			flag = false
		}

	}
	if j == len(p)-1 {
		if i == len(s) {
			flag = false
		} else if s[i] == p[j] || p[j] == '.' {
			flag = isMatchCore(s, p, i+1, j+1, dp)
		} else {
			flag = false
		}
	}
	if j < len(p)-1 {
		if p[j+1] == '*' {
			if i <= len(s)-1 && (s[i] == p[j] || p[j] == '.') {
				flag = isMatchCore(s, p, i+1, j+2, dp) || isMatchCore(s, p, i+1, j, dp) || isMatchCore(s, p, i, j+2, dp)
			} else {
				flag = isMatchCore(s, p, i, j+2, dp)
			}

		} else if i <= len(s)-1 && (s[i] == p[j] || p[j] == '.') {
			flag = isMatchCore(s, p, i+1, j+1, dp)
		}

	}
	if flag == true {
		dp[i][j] = 1
	} else {
		dp[i][j] = -1

	}
	return flag

}

func main(){
	fmt.Println(isMatch("a",""))
}
