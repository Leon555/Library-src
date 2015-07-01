/******************************************************************************

  Copyright (C), 2001-2012, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : FindSimilarWord.cpp
  Version       :
  Author        :
  Created       : 2012/09
  Last Modified :
  Description   :
  Function List :

  History       :
  1.Date        : 2012/09
    Author      :
    Modification: Created file

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagWordNode
{
	char *word;
	struct tagWordNode *next;
}WordNode;

WordNode *gWordHead = NULL;
WordNode *gWordTail = NULL;
int gWordNum = 0;

/* is similar word: return 0
    OR return 1;
    ERROR return -1
*/
int isSimilarWord(const char *dst, const char *src)
{
	int lenSrc = strlen(src);
	int lenDst = strlen(dst);
	int i = 0;
	int j = 0;
	
	int *slots = NULL;
	
	if ( lenSrc != lenDst )
		return 1;
		
	if ( strcmp (src, dst) == 0 )
		return 1;
	
	slots = (int *) malloc ( sizeof(int) * lenSrc );
	
	if ( slots == NULL )
		return -1;
	
	for ( i = 0; i < lenSrc; i++ )
	{
		for	( j = 0; j < lenDst; j++ )
		{
			if ( src[i] == dst[j] && slots[j] == 0 )
			{
				slots[j] = 1;
				break;
			}
			
		}
		if ( j == lenDst )
			return 1;
	}

	return 0;
}

void sortWords()
{
	char *temp = NULL;
	WordNode *prev = NULL;
	WordNode *next = NULL;
	int i = 0;
	int j = 0;
	
	for ( i = 0; i < gWordNum-1; i++ )
	{
		prev = gWordHead;
		for ( j = 0; j < gWordNum-i-1; j++)
		{
			next = prev->next;
			if ( strcmp(prev->word, next->word) > 0 )
			{
				temp = prev->word;
				prev->word = next->word;
				next->word = temp;
			}
			prev = next;
		}
	}
}

/******************************************************************************
原    型：int AddOneWord (char* Word);
功    能：在字典中增加一个单词
输入参数： 
          Word 单词字符串，调用者保证Word指针不为空，指向的是合法单词
输出参数：
          无
返回值：
        -1 失败（单词在字典中已存在等情况）
        0  成功
********************************************************************************/
int AddOneWord (char* Word)
{
    WordNode *it = gWordHead;
    WordNode *newNode = NULL;
    unsigned int wordLen = strlen(Word);
    
    if ( Word == NULL )
    	return -1; 
    
    while ( it )
    {
    	if ( strcmp(it->word, Word) == 0 )
    		return -1;
    	it = it->next;
    }
    
    newNode = (WordNode *) malloc ( sizeof(WordNode) );
    newNode->word = (char *) malloc ( sizeof(char) * wordLen + 1 );
    
    if ( newNode == NULL || newNode->word == NULL )
    	return -1;
    
    strncpy( newNode->word, Word, wordLen );
    newNode->word[wordLen] = '\0';
    newNode->next = NULL;
    
    if ( gWordTail )
    {
    	gWordTail->next = newNode;
    	gWordTail 		= newNode;
    }
    else
    {
    	gWordHead       = newNode;
    	gWordTail       = newNode;
    }
    
    gWordNum++;
    
    sortWords();

    return 0;
}

/******************************************************************************
原    型：int FindSimilarWordNum (char* Word);
功    能：查找指定单词在字典中的兄弟单词个数
输入参数：
          Word 指定单词字符串，调用者保证Word指针不为空，指向的是合法单词
输出参数：
          无
返回值：
          返回指定单词在字典中的兄弟单词总个数。如果不存在兄弟单词，返回0
*******************************************************************************/
int FindSimilarWordNum (char* Word)
{
	WordNode *it = gWordHead;
    unsigned int wordNum = 0;
    
    if ( Word == NULL )
    	return 0; 
    
    while ( it )
    {
    	if ( isSimilarWord(it->word, Word) == 0 )
    		wordNum++;
    	it = it->next;
    }

    return wordNum;
}

/******************************************************************************
原    型：int FindOneSimilarWord (char* Word, int Seq, char* SimilarWord);
功    能：查找指定单词的指定序号的兄弟单词，指定序号指字典中兄弟单词按字典顺序
          排序后的序号（从1开始）
输入参数：
          Word 指定单词字符串，调用者保证Word指针不为空，指向的是合法单词
          Seq 指定序号（大于等于1）
输出参数：
          SimilarWord 返回兄弟单词字符串，指针不为空，指向的内存由调用者预先分配，
          占51个字节长度，输出的兄弟单词必须紧跟’\0’结束。如果不存在指定序号的
          兄弟单词，输出空串。
返回值：
          -1 失败（如果不存在指定序号的兄弟单词，返回失败）
          0  成功
*******************************************************************************/
int FindOneSimilarWord (char* Word, int Seq, char* SimilarWord)
{
    WordNode *it = gWordHead;
    unsigned int wordNum = 0;
    unsigned int wordLen = 0;
    
    if ( Word == NULL )
    	return 0; 
    
    while ( it && Seq > 0 )
    {
    	if ( isSimilarWord(it->word, Word) == 0 )
    		Seq--;
    	it = it->next;
    }

	if ( Seq == 0 )
	{
		wordLen = strlen(it->word);
		strncpy( SimilarWord, it->word, wordLen);
		SimilarWord[wordLen] = '\0';
		return 0;
	}

    return -1;
}

/******************************************************************************
原    型：void ClearAllWords(void);
功    能：清空字典中所有单词
输入参数： 
          无
输出参数：
          无
返回值：
          无

*******************************************************************************/
void ClearAllWords(void)
{
    /* 在这里实现功能 */
}
