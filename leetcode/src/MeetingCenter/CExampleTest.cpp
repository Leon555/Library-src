/******************************************************************************

  Copyright (C), 2001-2012, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     :
  Version       :
  Author        :
  Created       : 2010/9/1
  Last Modified :
  Description   :
  Function List :

  History       :
  1.Date        : 2010/9/1
    Author      :
    Modification: Created file

******************************************************************************/

#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include <stdlib.h>
#include "OJ.h"

// 注册测试套到CppUnit
CPPUNIT_TEST_SUITE_REGISTRATION( CExampleTest );

// 测试用例实现示例

// SetUp: 在每个用例前执行一次
void CExampleTest::setUp()
{

}

// tearDown: 在每个用例后执行一次
void CExampleTest::tearDown()
{

}

void CExampleTest::TestCase01()
{
	//输入
	unsigned int nCompanyIn = 4;
	CompanyRequest req[] = {{4,9},
	{9,11},
	{13,19},
	{10,17}};

	//期望输出
	int nCompanyOutTest = 2;
	int ArrIndexTest[] = {1,3};

	//实际输出
	unsigned int nCompanyOut = 0;
	unsigned int ArrIndex[4]={0};

	
	int res = ConferenceArrangement(nCompanyIn, req, &nCompanyOut, ArrIndex);


	CPPUNIT_ASSERT(1 == res);
	CPPUNIT_ASSERT(nCompanyOutTest == nCompanyOut);
	for (int i = 0; i < nCompanyOutTest; i++)
	{
		CPPUNIT_ASSERT(ArrIndexTest[i] == ArrIndex[i]);
	}
	
    
}

void CExampleTest::TestCase02()
{
    
}

void CExampleTest::TestCase03()
{
   
}

// 在这里添加测试用例实现
// void CExampleTest::TestCasexx()
// {
//
// }
