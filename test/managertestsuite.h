#ifndef MANAGERTESTSUITE_H
#define MANAGERTESTSUITE_H

#include <cxxtest/TestSuite.h>

#include "manager.h"

class ManagerTestSuite : public CxxTest::TestSuite
{
public:

    void setUp()
    {
      testManager = diaryengine::Manager::makeNew("t/test");
    }

    void tearDown()
    {
    }

    void testRootpathIsSetCorrectlyAfterConstructingObject(void)
    {
      TS_ASSERT(testManager->rootPath() == "t/test")
    }

    std::shared_ptr<diaryengine::Manager> testManager;
};

#endif // MANAGERTESTSUITE_H
