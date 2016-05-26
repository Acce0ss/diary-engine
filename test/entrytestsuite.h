#ifndef ENTRYTESTSUITE
#define ENTRYTESTSUITE

#include <cxxtest/TestSuite.h>

#include <QDateTime>

#include <algorithm>
#include <list>

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

    void testKeywordsAreAdded()
    {
      testEntry->addKeyword("Test");
      testEntry->addKeyword("Test2");
      std::list<std::string> words = testEntry->keywords();
      TS_ASSERT(std::find(words.begin(), words.end(), "Test") != words.end());
      TS_ASSERT(std::find(words.begin(), words.end(), "Test2") != words.end());
    }

    void testKeywordAdditionReturnsTrueIfAdded()
    {
      bool success = testEntry->addKeyword("Test");
      TS_ASSERT(success);
    }

    void testKeywordAdditionReturnsFalseIfKeywordAlreadyExists()
    {
      testEntry->addKeyword("Test");
      bool failed = ! testEntry->addKeyword("Test");
      TS_ASSERT(failed);
    }

    void testKeywordIsRemoved()
    {
      testEntry->addKeyword("Test");
      testEntry->removeKeyword("Test");
      std::list<std::string> words = testEntry->keywords();
      TS_ASSERT(std::find(words.begin(), words.end(), "Test") == words.end());
    }

    void testKeywordRemovalReturnsTrueIfRemoved()
    {
      testEntry->addKeyword("Test");
      bool success = testEntry->removeKeyword("Test");
      TS_ASSERT(success);
    }

    void testKeywordAdditionReturnsFalseIfKeywordDoesNotExists()
    {
      bool failed = ! testEntry->removeKeyword("Test");
      TS_ASSERT(failed);
    }

    diaryengine::Entry* testEntry;
};


#endif // ENTRYTESTSUITE

