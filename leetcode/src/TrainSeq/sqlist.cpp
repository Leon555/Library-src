/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : 
  Version       : 
  Author        : 
  Created       : 2013/08/10
  Last Modified :
  Description   : 
  Function List :
              
  History       :
  1.Date        : 2013/08/10
    Author      : 
    Modification: Created file

******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
详细描述：   
int JudgeTrainSequence (int maxNum, char *pOutSeq);
输入参数：
	 	int maxNum：进站的火车最大编号
	 	char* pOutSeq：使用字符串表示火车出站序列
输出参数（指针指向的内存区域保证有效）：
	 	无。
返回值：
		Int: 根据输入的进站序列判断，如果输入的出战序列是可能的，返回1，否则返回0；

*/

int JudgeTrainSequence (int maxNum, char *pOutSeq)
{
    int inPos = 0; // in seq: "123456..."
    int outPos = 0; // out seq: pOutSeq
    int top = -1; // top of the stack
    int remains = 0;
    
    char *stack = (char *) malloc (maxNum * sizeof(char) );
    if(stack == NULL)
        return 0; // error handling
    
    while(inPos < maxNum){
        if(top >= 0 && stack[top] == pOutSeq[outPos]) {
                --top;
                ++outPos;
        }
		else {
			stack[++top] = inPos + '1';
			++inPos;
		}
    }
    
    remains = top + 1;
    
    while(remains > 0) {
    	if(top >= 0 && stack[top] == pOutSeq[outPos]) {
            --top;
            ++outPos;
        }
        --remains;
    }
    
    free(stack);
    stack = NULL;
    
    if(top >= 0)
        return 0;
        
    return 1;
}


