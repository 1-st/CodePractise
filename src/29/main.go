package main

import (
	"bytes"
)

func longestCommonPrefix(strs []string) string {
	if len(strs)==0{
		return ""
	}
	var buf  bytes.Buffer
	var i = 0
	for {
		if strs[0]==""{
			return ""
		}
		if i == len(strs[0]){
			return buf.String()
		}
		var currentByte = strs[0][i]
		for j:=0;j<len(strs);j++{
			if i==len(strs[j])||strs[j][i]!=currentByte{
				return buf.String()
			}
		}
		buf.WriteByte(currentByte)
		i++
	}
}



func main(){

}
