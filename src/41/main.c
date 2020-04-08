//
// Created by admin on 2020/4/9.
//

#include "main.h"
#include "stdio.h"
#include "string.h"

int mystrcmp(const char * a,const char * b){
    while(*b!='\0'){
        if(*a++!=*b++){
            return -1;
        }
    }
    return 0;
}

int strStr(char * haystack, char * needle){
    if (strlen(needle)==0){
        return 0;
    }
    int ndLen = (int)strlen(needle);
    int hsLen = (int)strlen(haystack);
    int finalPos = hsLen -ndLen;
    char * h = haystack;
    while(h-haystack<=finalPos){
        if(mystrcmp(h,needle) == 0){
            return (int)(h-haystack);
        }
        h++;
    }
    return -1;
}

int main(){
    printf("%d",strStr("hello","ll"));
    return 0;
}