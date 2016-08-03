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
      testBook = createTestBook();
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

    void testAddingUniqueBookReturnsTrue()
    {
      TS_ASSERT_EQUALS(testManager->addBook(testBook), true);
    }

    void testAddingSameBookTwiceReturnsFalse()
    {
      testManager->addBook(testBook);
      TS_ASSERT_EQUALS(testManager->addBook(testBook), false);
    }

    void testAfterAddingUniqueBookBooksReturnsSizeOneMap()
    {
      testManager->addBook(testBook);
      TS_ASSERT_EQUALS(testManager->books().size(), 1);
    }

    void testAfterAddingTwoUniqueBookBooksReturnsSizeTwoMap()
    {
      auto book2 = createTestBook();

      testManager->addBook(testBook);
      testManager->addBook(book2);

      TS_ASSERT_EQUALS(testManager->books().size(), 2);
    }

    void testAfterAddingBookHasCorrectIdInTheBooksMap()
    {
      testManager->addBook(testBook);
      TS_ASSERT_EQUALS(testManager->books().at(testBook->id()), testBook);
    }

    std::shared_ptr<diaryengine::Entry> createTestEntry()
    {
      return diaryengine::Entry::makeNew("\"al\" <al@lo.co>",
                                         "test", "2000-10-10T10:00:00+02:00","test","test");
    }

    std::shared_ptr<diaryengine::Book> createTestBook()
    {
      auto testBook = diaryengine::Book::makeNew("test");

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

      return testBook;
    }

    const std::string testPath = "/tmp/diaryengine_test/";
    std::shared_ptr<diaryengine::Manager> testManager;
    std::shared_ptr<diaryengine::Book> testBook;
};

#endif // MANAGERTESTSUITE_H
