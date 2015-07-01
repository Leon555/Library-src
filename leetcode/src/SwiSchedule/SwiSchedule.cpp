/***************************************************************************

Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

***************************************************************************
File Name     :
Version       :
Author        :
Created       : 2010/3
Last Modified :
Description   :
Function List :

History       :
1.Date        : 2010/3
Author      :
Modification: Created file

****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct tagPriorityNode
{
	unsigned int prio;
	void (*proc) (void);
}PriorityNode;

PriorityNode *gPrioNodeList = (PriorityNode *)calloc(100, sizeof(PriorityNode) );

unsigned int gPrioArray[100];
unsigned int gCnt = 0;

/****************************************************************************
函数说明：创建软中断
输入参数：
      swiId： 创建软中断ID；
	  prio：  创建软中断优先级；
      proc：  创建软中断处理函数。
输出参数：无
返回值  ：成功返回0， 其它情况返回-1
******************************************************************************/
int SwiCreate(unsigned int swiId, unsigned int prio, void (* proc)(void))
{
	if ( proc == NULL )
		return -1;
	
	/* invalid priority or invalid swiId*/
	if ( prio > 31 || swiId > 99)
		return -1;
	
	if ( gPrioNodeList[swiId].proc )
		return -1;

	gPrioNodeList[swiId].prio = prio;
	gPrioNodeList[swiId].proc = proc;

	return 0;
}

/***************************************************************************
函数说明：软中断激活
输入参数：swiId： 待激活软中断ID
输出参数：无
返回值  ：成功返回0， 其它情况返回-1
****************************************************************************/
int SwiActivate(unsigned int swiId)
{	
	return 0;
}

/**************************************************************************
函数说明：清空所有的信息
输入参数：无
输出参数：无
返回值  ：无
*****************************************************************************/
void Clear(void)
{
	
}
