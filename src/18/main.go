package main

import (
	"bytes"
	"fmt"
	"strconv"
)

func compressString(S string) string {
	var buf bytes.Buffer
	for i:=0;i<len(S);{
		var count = 1
		var prev = S[i]
		buf.WriteByte(prev)
		var j = i+1
		for j<len(S)&&S[j]==prev{
			count++
			j++
		}
		i = j
		buf.WriteString(strconv.Itoa(count))
	}
	var res = buf.String()
	if len(res)>=len(S){
		return S
	}else{
		return res
	}
}

func main(){
	fmt.Println(compressString("aaafheuuuu"))
}
