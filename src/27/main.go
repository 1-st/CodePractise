package main

import "fmt"

func intToRoman(num int) string {
	var res string
	num1000 := num / 1000
	num100 := (num % 1000) / 100
	num10 := (num % 100) / 10
	num1 := num % 10
	if num1000 != 0 {
		for num1000 != 0 {
			num1000--
			res += "M"
		}
	}
	switch num100 {
	case 9:
		res += "CM"
	case 8:
		res += "DCCC"
	case 7:
		res += "DCC"
	case 6:
		res += "DC"
	case 5:
		res += "D"
	case 4:
		res += "CD"
	case 3:
		res += "CCC"
	case 2:
		res += "CC"
	case 1:
		res += "C"
	}

	switch num10 {
	case 9:
		res += "XC"
	case 8:
		res += "LXXX"
	case 7:
		res += "LXX"
	case 6:
		res += "LX"
	case 5:
		res += "L"
	case 4:
		res += "XL"
	case 3:
		res += "XXX"
	case 2:
		res += "XX"
	case 1:
		res += "X"
	}

	switch num1 {
	case 9:
		res += "IX"
	case 8:
		res += "VIII"
	case 7:
		res += "VII"
	case 6:
		res += "VI"
	case 5:
		res += "V"
	case 4:
		res += "IV"
	case 3:
		res += "III"
	case 2:
		res += "II"
	case 1:
		res += "I"
	}
	return res
}

func main(){
	fmt.Println(intToRoman(1994))
}