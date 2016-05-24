#ifndef ENTRYTESTSUITE
#define ENTRYTESTSUITE

#include <cxxtest/TestSuite.h>
#include "../src/entry.h"

class EntryTestSuite : public CxxTest::TestSuite
{
public:
    void testEntryHasGivenTitle(void)
    {
        testEntry.setTitle("testTitle");
        TS_ASSERT_SAME_DATA(testEntry.title().c_str(), "testTitle", 9);
    }

    diaryengine::Entry testEntry;
};


#endif // ENTRYTESTSUITE

