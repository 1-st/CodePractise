package main

import "fmt"

func calcu(s string)int{
	switch s{
	case "CM":
		return 900
	case "DCCC":
		return 800
	case "DCC":
		return 700
	case "DC":
		return 600
	case "D":
		return 500
	case "CD":
		return 400
	case "CCC":
		return 300
	case "CC":
		return 200
	case "C":
		return 100
	}
	switch s{
	case "XC":
		return 90
	case "LXXX":
		return 80
	case "LXX":
		return 70
	case "LX":
		return 60
	case "L":
		return 50
	case "XL":
		return 40
	case "XXX":
		return 30
	case "XX":
		return 20
	case "X":
		return 10
	}
	switch s{
	case "IX":
		return 9
	case "VIII":
		return 8
	case "VII":
		return 7
	case "VI":
		return 6
	case "V":
		return 5
	case "IV":
		return 4
	case "III":
		return 3
	case "II":
		return 2
	case "I":
		return 1
	}
	return 0
}
func romanToInt(s string) int {
	res := 0
	i := 0
	for ;i<len(s);i++{
		if s[i]=='M'{
			res+=1000
		}else{
			break
		}
	}
	var temp = ""
	for i<len(s)&&s[i]!='X'&&s[i]!='L'&&s[i]!='I'&&s[i]!='V' {
		temp+=string(s[i])
		i++
	}
	res += calcu(temp)
	temp = ""

	for i<len(s)&&s[i]!='I'&&s[i]!='V'{
		temp+=string(s[i])
		i++
	}
	res += calcu(temp)
	temp = ""

	for i<len(s) {
		temp+=string(s[i])
		i++
	}
	res += calcu(temp)
	return res
}

func main(){
	fmt.Println(romanToInt("IX"))
}
