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

    void testUTF8textContentIsUnmangledAfterSettingAndRetrieving()
    {
      QString testcontent = QString::fromUtf8("やる気");
      testEntry->setTextContent(testcontent.toStdString());
      TS_ASSERT(QString::fromUtf8(QByteArray::fromStdString(testEntry->textContent())) == "やる気");
    }

    void testMultimediaCanBeAdded()
    {
      testEntry->addBase64EncodedMultimediaPart("testFile", "it's multipart");
      std::map<std::string, std::string> mults = testEntry->base64EncodedMultimediaParts();
      TS_ASSERT(mults.at("testFile") == "it's multipart");
    }

    void testMultimediaCanBeRemoved()
    {
      testEntry->addBase64EncodedMultimediaPart("testFile", "it's multipart");
      testEntry->removeBase64EncodedMultimediaPart("testFile");
      std::map<std::string, std::string> mults = testEntry->base64EncodedMultimediaParts();
      TS_ASSERT(mults.find("testFile") == mults.end());
    }

    void testFormatIsProper()
    {
      unsigned long testId = testEntry->id();
      std::stringstream testFileContent;
      testFileContent << "From: \"Author Name\" <author@domain.com>" << std::endl
          <<"Date: 2000-10-10T10:00:00+02:00" << std::endl
          <<"Message-ID: <" << testId << "@<journal name>>" << std::endl
          <<"Subject: <entry title>" << std::endl
          <<"X-Engine-Version: " << DIARYENGINE_VERSION << std::endl
          <<"X-Entry-Keywords: again,me,test" << std::endl
          <<"Content-Type: multipart/mixed; boundary=\"bound-" << testId << "\"" << std::endl << std::endl
          <<"--bound-" << testId << std::endl
          <<"Content-Type: text/plain; charset=\"UTF-8\"" << std::endl << std::endl
          <<"this is text, äöly!" << std::endl<< std::endl
          <<"--bound-" << testId << "--" << std::endl;

      testEntry->setAuthor("Author Name");
      testEntry->setDate("2000-10-10T10:00:00+02:00");
      testEntry->setTitle("<entry title>");
      testEntry->setTextContent("this is text, äöly!");
      testEntry->setBelongsTo("<journal name>");

      testEntry->addKeyword("test");
      testEntry->addKeyword("me");
      testEntry->addKeyword("again");

      std::stringstream target;
      testEntry->asFileContentTo(target);

      TS_ASSERT_SAME_DATA(target.str().c_str(), testFileContent.str().c_str(), testFileContent.str().length());
    }

    void testNewEntriesAreMadeCorrectly()
    {
      auto newEntry = diaryengine::Entry::makeNew("Author Name", "<entry title>", "2000-10-10T10:00:00+02:00",
                                                  "this is text, äöly!", "<journal name>");

      unsigned long testId = newEntry->id();
      std::stringstream testFileContent;
      testFileContent << "From: \"Author Name\" <author@domain.com>" << std::endl
          <<"Date: 2000-10-10T10:00:00+02:00" << std::endl
          <<"Message-ID: <" << testId << "@<journal name>>" << std::endl
          <<"Subject: <entry title>" << std::endl
          <<"X-Engine-Version: " << DIARYENGINE_VERSION << std::endl
          <<"X-Entry-Keywords: " << std::endl
          <<"Content-Type: multipart/mixed; boundary=\"bound-" << testId << "\"" << std::endl << std::endl
          <<"--bound-" << testId << std::endl
          <<"Content-Type: text/plain; charset=\"UTF-8\"" << std::endl << std::endl
          <<"this is text, äöly!" << std::endl << std::endl
          <<"--bound-" << testId << "--" << std::endl;

      std::stringstream target;
      newEntry->asFileContentTo(target);

      TS_ASSERT_SAME_DATA(target.str().c_str(), testFileContent.str().c_str(), testFileContent.str().length());
    }

    diaryengine::Entry* testEntry;
};


#endif // ENTRYTESTSUITE

