#ifndef BOOKTESTSUITE_H
#define BOOKTESTSUITE_H

#include <cxxtest/TestSuite.h>

#include <QDateTime>
#include <QDir>

#include <algorithm>
#include <list>

#include "../src/book.h"
#include "../src/entry.h"

class BookTestSuite : public CxxTest::TestSuite
{
public:

    void setUp()
    {
      testBook = diaryengine::Book::makeNew("test");
    }

    void tearDown()
    {
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

    void testFindingSingleMatchFromSingleEntrySingleKeyword()
    {
      auto testEntry = createTestEntry();
      testEntry->addKeyword("test1");
      testBook->addEntry(testEntry);
      auto matches = testBook->searchEntriesByKeyword("test1");

      TS_ASSERT_EQUALS(matches.size(), 1);
      TS_ASSERT_EQUALS(testEntry, matches.front());
    }

    void testFindingSingleMatchFromMultipleEntriesSingleKeyword()
    {
      auto testEntry = createTestEntry();
      auto testEntry1 = createTestEntry();
      auto testEntry2 = createTestEntry();
      auto testEntry3 = createTestEntry();
      testEntry->addKeyword("test1");
      testEntry1->addKeyword("test2");
      testEntry2->addKeyword("test3");
      testEntry3->addKeyword("test4");
      testBook->addEntry(testEntry);
      testBook->addEntry(testEntry1);
      testBook->addEntry(testEntry2);
      testBook->addEntry(testEntry3);
      auto matches = testBook->searchEntriesByKeyword("test3");

      TS_ASSERT_EQUALS(matches.size(), 1);
      TS_ASSERT_EQUALS(testEntry2, matches.front());
    }

    void testFindingSingleMatchFromMultipleEntriesMultipleKeywords()
    {
      auto testEntry = createTestEntry();
      auto testEntry1 = createTestEntry();
      auto testEntry2 = createTestEntry();
      auto testEntry3 = createTestEntry();
      testEntry->addKeyword("test1");
      testEntry->addKeyword("tes1");
      testEntry->addKeyword("tst1");
      testEntry1->addKeyword("test2");
      testEntry1->addKeyword("tes2");
      testEntry1->addKeyword("tst2");
      testEntry2->addKeyword("test3");
      testEntry2->addKeyword("tes3");
      testEntry2->addKeyword("tst3");
      testEntry3->addKeyword("test4");
      testEntry3->addKeyword("tes4");
      testEntry3->addKeyword("tst4");
      testBook->addEntry(testEntry);
      testBook->addEntry(testEntry1);
      testBook->addEntry(testEntry2);
      testBook->addEntry(testEntry3);

      std::list<std::string> searchKeywords;
      searchKeywords.push_back("test3");
      searchKeywords.push_back("tes3");
      auto matches = testBook->searchEntriesByKeywords(searchKeywords);

      TS_ASSERT_EQUALS(matches.size(), 1);
      TS_ASSERT_EQUALS(testEntry2, matches.front());
    }

    void testFindingMultipleMatchesFromMultipleEntriesMultipleKeywords()
    {
      auto testEntry = createTestEntry();
      auto testEntry1 = createTestEntry();
      auto testEntry2 = createTestEntry();
      auto testEntry3 = createTestEntry();
      testEntry->addKeyword("test1");
      testEntry->addKeyword("tes");
      testEntry->addKeyword("tst");
      testEntry1->addKeyword("test2");
      testEntry1->addKeyword("tes");
      testEntry1->addKeyword("tst");
      testEntry2->addKeyword("test3");
      testEntry2->addKeyword("tes3");
      testEntry2->addKeyword("tst3");
      testEntry3->addKeyword("test4");
      testEntry3->addKeyword("tes4");
      testEntry3->addKeyword("tst4");
      testBook->addEntry(testEntry);
      testBook->addEntry(testEntry1);
      testBook->addEntry(testEntry2);
      testBook->addEntry(testEntry3);

      std::list<std::string> searchKeywords;
      searchKeywords.push_back("tes");
      searchKeywords.push_back("tst");
      auto matches = testBook->searchEntriesByKeywords(searchKeywords);

      TS_ASSERT_EQUALS(matches.size(), 2);
      TS_ASSERT_DIFFERS(std::find(matches.begin(), matches.end(), testEntry), matches.end());
      TS_ASSERT_DIFFERS(std::find(matches.begin(), matches.end(), testEntry1), matches.end());
    }

    void testWritingToDiskWorks()
    {
      auto testEntry = createTestEntry();
      auto testEntry1 = createTestEntry();
      auto testEntry2 = createTestEntry();
      auto testEntry3 = createTestEntry();
      testEntry->addKeyword("test1");
      testEntry->addKeyword("tes");
      testEntry->addKeyword("tst");
      testEntry1->addKeyword("test2");
      testEntry1->addKeyword("tes");
      testEntry1->addKeyword("tst");
      testEntry2->addKeyword("test3");
      testEntry2->addKeyword("tes3");
      testEntry2->addKeyword("tst3");
      testEntry3->addKeyword("test4");
      testEntry3->addKeyword("tes4");
      testEntry3->addKeyword("tst4");
      testBook->addEntry(testEntry);
      testBook->addEntry(testEntry1);
      testBook->addEntry(testEntry2);
      testBook->addEntry(testEntry3);

      QDir dir;

      dir.mkpath("test/12/");
      TS_ASSERT(testBook->saveToDisk("test/12/"));
    }

    std::shared_ptr<diaryengine::Book> testBook;
};


#endif // BOOKTESTSUITE_H
