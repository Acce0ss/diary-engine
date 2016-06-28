#ifndef BOOKTESTSUITE_H
#define BOOKTESTSUITE_H

#include <cxxtest/TestSuite.h>

#include <QDateTime>

#include <algorithm>
#include <list>

#include "../src/book.h"
#include "../src/entry.h"

class BookTestSuite : public CxxTest::TestSuite
{
public:

    void setUp()
    {
      testBook = new diaryengine::Book("test");
    }

    void tearDown()
    {
      delete testBook;
    }

    std::shared_ptr<diaryengine::Entry> createTestEntry()
    {
      return diaryengine::Entry::makeNew("\"al\" <al@lo.co>",
                                         "test", "2000-10-10T10:00:00+02:00","test","test");
    }

    void testNameIsSetCorrectlyByConstructor(void)
    {
      TS_ASSERT(testBook->name() == "test")
    }

    void testNameCanBeSetAndRetrievedCorrectly()
    {
      testBook->setName("testus");
      TS_ASSERT(testBook->name() == "testus")
    }

    void testDescriptionCanBeSetAndRetrievedCorrectly()
    {
      testBook->setDescription("testus");
      TS_ASSERT(testBook->description() == "testus")
    }

    void testAddingEntriesReturnsTrueWhenIdIsUnique()
    {
      auto testEntry = createTestEntry();
      TS_ASSERT(testBook->addEntry(testEntry));
    }

    void testNonExistingEntryIdReturnsNullPtr()
    {
      TS_ASSERT_EQUALS((bool)testBook->entry(10), false);
    }

    void testExistingEntryIdReturnsPointerToCorrectLocation()
    {
      auto testEntry = createTestEntry();
      testBook->addEntry(testEntry);
      TS_ASSERT_EQUALS(testBook->entry(testEntry->id()), testEntry);
    }

    diaryengine::Book* testBook;
};


#endif // BOOKTESTSUITE_H
