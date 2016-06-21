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
      Book(std::__cxx11::string name);
      ~Book();

      void setName(std::string name);
      std::string name();

      bool addEntry(std::shared_ptr<Entry> entry);
      bool removeEntry(long id);

      unsigned long searchEntryByTitle(std::string searchWord);
      unsigned long searchEntryByKeywords(std::list<std::string> keywords);
      unsigned long searchEntryByFullText(std::string searchText);

    private:
      struct Implementation;
      std::unique_ptr<Implementation> _inside;
  };

} // namespace diaryengine

#endif // DIARYENGINE_DIARY_H
