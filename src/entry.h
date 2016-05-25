#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <memory>
#include <list>

namespace diaryengine {
  class Entry
  {
    public:
      Entry();
      ~Entry();

      unsigned long id();
      void regenerateId();

      void setTitle(std::string title);
      std::string title();

      void setDate(std::string ISOString);
      std::string date();

      void setContent(std::string content);
      std::string content();

      bool addKeyword(std::string keyword);
      bool removeKeyword(std::string keyword);
      std::list<std::__cxx11::string> keywords();

    private:
      struct Implementation;
      std::unique_ptr<Implementation> _inside;
  };

}
#endif // ENTRY_H
