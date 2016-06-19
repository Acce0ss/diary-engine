#ifndef BOOKTESTSUITE_H
#define BOOKTESTSUITE_H

#include <cxxtest/TestSuite.h>

#include <QDateTime>

#include <algorithm>
#include <list>

#include "../src/book.h"

class EntryTestSuite : public CxxTest::TestSuite
{
public:

    void setUp()
    {
      testBook = new diaryengine::Book();
    }

    void tearDown()
    {
      delete testBook;
    }

    void testTitleCanBeSetCorrectly(void)
    {
    }

    diaryengine::Book* testBook;
};


#endif // BOOKTESTSUITE_H
