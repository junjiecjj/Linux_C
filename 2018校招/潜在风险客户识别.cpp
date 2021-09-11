/*************************************************************************
>> File Name: 潜在风险客户识别.cpp
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.06.11
************************************************************************/

#include "stdio.h"
    
int is_not_first = 0;
void dfs(int nl, int nr, char *result, int i){
    if(nl==0 && nr==0){
        result[i] = 0;
        if(is_not_first)
            printf(",%s",result);
        else{
            printf("%s", result);
            is_not_first = 1;
        }
        return;
    }
        
    if(nl>0){
        result[i] = '(';
        dfs(nl-1, nr, result, i+1);
    }
        
    if(nr>nl){
        result[i] = ')';
        dfs(nl,nr-1, result, i+1);
            
    }
}
    
int main(){
    int n;
    char buf[1024];
    while(scanf("%d", &n) != EOF){
        is_not_first = 0;
        dfs(n,n,buf,0);
        printf("\n");
    }
        
}
