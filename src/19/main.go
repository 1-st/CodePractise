package main

import "fmt"

func countCharacters(words []string, chars string) int {
	var sum int
	var dist = make(map[byte]int,0)
	for i:= range chars{
		if _,ok:=dist[chars[i]];!ok{
			dist[chars[i]]=1
		}else{
			dist[chars[i]]+=1
		}
	}
	for _,v:= range words{
		var distCopy = make(map[byte]int,0)
		for k,v:= range dist{
			distCopy[k] = v
		}
		for i:= range v{
			if _,ok:=distCopy[v[i]];!ok||(ok&&distCopy[v[i]]==0){
				break
			}else{
				if i == len(v)-1{
					sum	+= len(v)
				}else{
					distCopy[v[i]]--
				}
			}
		}
	}
	return sum
}


func main(){
	fmt.Println(countCharacters([]string{"hello","world","leetcode"},"welldonehoneyr"))
}
