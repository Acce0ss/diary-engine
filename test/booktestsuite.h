#ifndef BOOKTESTSUITE_H
#define BOOKTESTSUITE_H

#include <cxxtest/TestSuite.h>

#include <QDateTime>

#include <algorithm>
#include <list>

#include "../src/book.h"

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

    diaryengine::Book* testBook;
};


#endif // BOOKTESTSUITE_H
