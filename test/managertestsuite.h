#ifndef MANAGERTESTSUITE_H
#define MANAGERTESTSUITE_H

#include <cxxtest/TestSuite.h>

#include "manager.h"

//The root path related tests should be moved to integration tests,
//since they depend on the filesystem having writable space at /tmp/
class ManagerTestSuite : public CxxTest::TestSuite
{
public:

    void setUp()
    {
      testManager = diaryengine::Manager::makeNew(testPath);
    }

    void tearDown()
    {
      std::string removeCommand = "rm -r " + testPath;
      system(removeCommand.c_str());
    }

    void testRootpathIsSetCorrectlyAfterConstructingObject(void)
    {
      TS_ASSERT(testManager->rootPath() == testPath)
    }

    const std::string testPath = "/tmp/files/";
    std::shared_ptr<diaryengine::Manager> testManager;
};

#endif // MANAGERTESTSUITE_H
