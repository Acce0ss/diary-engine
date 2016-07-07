#ifndef DIARYENGINE_DIARY_H
#define DIARYENGINE_DIARY_H

#include <memory>
#include <string>
#include <list>

namespace diaryengine {

  class Entry;

  class Book
  {
    public:
      Book();
      ~Book();

      void setName(std::string name);
      std::string name();

      void setDescription(std::string description);
      std::string description();

      bool addEntry(std::shared_ptr<Entry> entry);
      bool removeEntry(long id);
      std::shared_ptr<Entry> entry(long id);
      bool addEntriesFrom(std::list<std::shared_ptr<Entry>> list);

      std::list<std::shared_ptr<Entry>> searchEntriesByTitle(std::string searchWord);
      std::list<std::shared_ptr<Entry>> searchEntriesByKeyword(std::string keyword);
      std::list<std::shared_ptr<Entry>> searchEntriesByKeywords(std::list<std::string> keywords);
      std::list<std::shared_ptr<Entry>> searchEntriesByFullText(std::string searchText);

    private:
      struct Implementation;
      std::unique_ptr<Implementation> _inside;
  };

} // namespace diaryengine

#endif // DIARYENGINE_DIARY_H
