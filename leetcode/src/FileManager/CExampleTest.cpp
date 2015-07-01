
#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include "FileManager.h"

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
    Clear();
}

void CExampleTest::TestCase01()
{
    CreateDir("root", "DirA");
    CreateFile("DirA", "File1");
    CreateFile("DirA", "File2");
    CPPUNIT_ASSERT(2 == GetFileNum("DirA"));
    CPPUNIT_ASSERT(3 == GetFileNum("root"));
}

void CExampleTest::TestCase02()
{
    CreateDir("root", "DirA");
    CreateDir("DirA", "DirAA");
    CreateFile("DirA", "FileAA");
    CreateDir("DirA", "DirAB");
    CreateDir("DirAA", "DirAAA");
    CreateFile("DirAAA", "File1");
    CreateFile("DirAAA", "File2");
    DeleteDir("DirA");
    CPPUNIT_ASSERT(0 == GetFileNum("root"));
}

void CExampleTest::TestCase03()
{
    CreateDir("root", "DirA");
    CreateDir("DirA", "DirAA");
    CreateDir("DirA", "DirAB");
    CreateDir("DirAA", "DirAAA");
    CreateFile("DirAAA", "File1");
    CreateFile("DirAAA", "File2");
    MoveDir("DirAA", "DirAB");
    CPPUNIT_ASSERT(4 == GetFileNum("DirAB"));
}

void CExampleTest::TestCase04()
{
    CreateDir("root", "DirA");
    CreateDir("DirA", "DirAA");
    CreateDir("DirA", "DirAB");
    CreateDir("DirAA", "DirAAA");
    CreateFile("DirAAA", "File1");
    CreateFile("DirAAA", "File2");
    MoveDir("DirAA", "root");
    CPPUNIT_ASSERT(1 == GetFileNum("DirA"));
}
