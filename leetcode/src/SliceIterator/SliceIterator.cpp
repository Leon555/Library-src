
#include "SliceIterator.h"
#include <stdio.h>
#include <stdlib.h>

int getOffset(const SliceIterator *it);
int sliceValidation(const SliceDesc *slice_desc);

/******************************************************************************
功能：初始化一个切片迭代器，使其指向切片内的第一个元素
输入：
	  slice_desc    ： 切片描述符指针（合法性由考生检查）
	  slice_iterator： 切片迭代器指针
输出： 
	  slice_iterator： 初始化后的切片迭代器的指针
返回：
	  0：成功，-1：失败

说明： 
1）SliceIterator结构需要由考生自行设计和定义
2）迭代器内存由调用者申请，大小仅为sizeof(SliceIterator)，函数内部不得额外申请动态内存
3）用例保证其他接口的输入不会是未初始化过的迭代器指针	
******************************************************************************/
int SliceIteratorInit (const SliceDesc* slice_desc, SliceIterator* slice_iterator)
{
	/* 在这里实现功能 */
	unsigned int i = 0;

	// Parameter validation
	if(slice_desc == NULL)
		return -1;
		
	if(!sliceValidation(slice_desc))
		return -1;

	unsigned long coordNum = slice_desc->coord_num;
	
	for(i = 0 ; i < coordNum; i++)
	{
		slice_iterator->coord_cur[i] = slice_desc->coord_slice[i].start;
	}

	slice_iterator->pSliceDesc = (SliceDesc *)slice_desc;	
    
	return 0;
}

/******************************************************************************
功能：获取当前元素指针
输入：
	  slice_iterator：迭代器指针
输出：无
返回：指向当前元素的指针。若迭代结束，应返回空指针。
******************************************************************************/
int* SliceIteratorGetCurr(const SliceIterator* slice_iterator)
{
	/* 在这里实现功能 */
	if(SliceIteratorEnd(slice_iterator))
		return NULL;

	int offset = getOffset(slice_iterator);

	int *val = &slice_iterator->pSliceDesc->first_element_of_orignal_array[offset];

	return val;
}

/******************************************************************************
功能：移动到下一个元素
输入：
	  slice_iterator  迭代器指针
输出：
	  slice_iterator  更新后的迭代器
返回：无
******************************************************************************/
void SliceIteratorNext(SliceIterator* slice_iterator)
{
	/* 在这里实现功能 */
	CoordSlice *range = slice_iterator->pSliceDesc->coord_slice;
	unsigned long *curInx = slice_iterator->coord_cur;
	int coordNum = slice_iterator->pSliceDesc->coord_num;
	int i = coordNum-1;
	int carryFlag = 0;
	
	curInx[i]++;

	for(; i > 0; i--)
	{
		if(curInx[i] > range[i].end)
		{
			curInx[i] = range[i].start;
			curInx[i-1]++;
		}
	}

	return;
}

/******************************************************************************
功能：迭代是否结束
输入：
	  slice_iterator:   迭代器指针
输出：无
返回：1: 迭代已结束; 0:迭代未结束
******************************************************************************/
int SliceIteratorEnd(const SliceIterator* slice_iterator)
{
	/* 在这里实现功能 */
	if(slice_iterator->coord_cur[0] > slice_iterator->pSliceDesc->coord_slice[0].end)
		return 1;

	return 0;
}

/******************************************************************************
功能：创建一个数组切片的拷贝
输入：slice_desc:  切片描述符指针（合法性由考生检查）
输出：
	  first_element_of_slice_array:新的切片数组的第一个元素指针
	  slice_element_num:新的切片数组中元素个数
返回：0：成功，-1:失败

说明：first_element_of_slice_array内存在函数内申请，调用者释放
******************************************************************************/
int CopySlice(const SliceDesc* slice_desc,int** first_element_of_slice_array, unsigned long* slice_element_num)
{
	/* 在这里实现功能 */
	if(!sliceValidation(slice_desc))
		return -1;

	unsigned int i = 0;
	unsigned long coord_num = slice_desc->coord_num;
	*slice_element_num = 1;
	for(i = 0; i < coord_num; i++)
	{
		*slice_element_num *= (slice_desc->coord_slice[i].end - slice_desc->coord_slice[i].start + 1);
	}

	*first_element_of_slice_array = (int *) malloc ( *slice_element_num
		   	* sizeof(int) );
	if(*first_element_of_slice_array == NULL)
		return -1;

	SliceIterator slice_iterator;
	int *first = *first_element_of_slice_array;
	
	for(SliceIteratorInit(slice_desc,&slice_iterator);
			1!=SliceIteratorEnd(&slice_iterator);
			SliceIteratorNext(&slice_iterator) )
	{
		int val = *SliceIteratorGetCurr(&slice_iterator);
		*first++ = val;
	}

	return 0;
}

int sliceValidation(const SliceDesc *slice_desc)
{
	int i = 0;
	unsigned long coord_num = slice_desc->coord_num;
	
	if(coord_num == 0 || coord_num > 10)
		return 0;

	for(i = 0; i < coord_num; i++)
	{
		unsigned int max = slice_desc->coord_spec[i];
		const CoordSlice *range = &slice_desc->coord_slice[i];
		if( range->end < range->start || range->end > max )
			return 0;
	}

	return 1;
}

int getOffset(const SliceIterator *it)
{
	int i = 0;
	unsigned long coord_num = it->pSliceDesc->coord_num;
	unsigned long offset = it->coord_cur[coord_num-1];
	unsigned long product = 1;
	unsigned int len = 1;

	for(i = coord_num-1; i > 0 ; i--)
	{
		len = it->pSliceDesc->coord_spec[i]+1;
		product *= len;
		offset += (it->coord_cur[i-1] * product);
	}

	return offset;
}

