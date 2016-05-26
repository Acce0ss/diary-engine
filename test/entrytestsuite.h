#ifndef ENTRYTESTSUITE
#define ENTRYTESTSUITE

#include <cxxtest/TestSuite.h>

#include <QDateTime>

#include "../src/entry.h"

class EntryTestSuite : public CxxTest::TestSuite
{
public:

    void setUp()
    {
      testEntry = new diaryengine::Entry();
    }

    void tearDown()
    {
      delete testEntry;
    }

    void testTitleCanBeSetCorrectly(void)
    {
      testEntry->setTitle("testTitle");
      TS_ASSERT_SAME_DATA(testEntry->title().c_str(), "testTitle", 9);
    }

    void testDateCanBeSetCorrectlyWithISOString(void)
    {
      testEntry->setDate("2007-03-01T13:00:00Z");
      TS_ASSERT(testEntry->date() == "2007-03-01T13:00:00Z");
    }

    void testDateUnderstandsTimeZone(void)
    {
      testEntry->setDate("2007-03-01T13:00:00+02:00");
      TS_ASSERT(testEntry->date() == "2007-03-01T13:00:00+02:00");
    }

    void testIdRegenerationGeneratesDifferentUUID()
    {
      testEntry->regenerateId();
      long id = testEntry->id();
      testEntry->regenerateId();
      TS_ASSERT_DIFFERS(testEntry->id(), id);
    }

    diaryengine::Entry* testEntry;
};


#endif // ENTRYTESTSUITE

