/*************************************************************************
>> File Name: 替换空格.cpp
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.03.19
************************************************************************/

#include<iostream>
using namespace std;
#include<string>

class Solution {
public:
	void replaceSpace(char *str,int length) {//length为str的最大容量
        if(str == NULL )
            return;
        int BlankCount = 0;
        int StringLength = 0;
        for(int i = 0; str[i] != '\0'; i++)
        {
            StringLength ++;
            if(str[i] == ' ')
            {
                ++BlankCount;
            }
        }
        int AutualLength = StringLength + 2*BlankCount;
        if(AutualLength+1 > length)
            return;
        char *pt1 = str + StringLength;  //包含结束符'\0'
        char *pt2 = str +AutualLength;
        while(pt1 < pt2)
        {
            if(*pt1 == ' ')
            {
                *pt2-- = '0';
                *pt2-- = '2';
                *pt2-- = '%';
            }
            else
            {
                *pt2-- = *pt1; 
            }
            --pt1;
        }
	}
};
