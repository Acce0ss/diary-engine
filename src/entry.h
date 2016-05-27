#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <memory>
#include <list>
#include <tuple>

namespace diaryengine {
  class Entry
  {
    public:
      Entry();
      ~Entry();

      typedef std::tuple<std::string, std::string> NameMediaPair;

      unsigned long id();
      void regenerateId();

      void setTitle(std::string title);
      std::string title();

      void setDate(std::string ISOString);
      std::string date();

      //Assumes all text is UTF-8 encoded. The std::string only works as
      //convenient container and common way to pass the data.
      void setTextContent(std::string content);
      std::string textContent();

      void addBase64EncodedMultimedia(std::string name, std::string media);
      void removeBase64EncodedMultimedia(std::string name);
      std::list<NameMediaPair> base64EncodedMultimedia();

      bool addKeyword(std::string keyword);
      bool removeKeyword(std::string keyword);
      std::list<std::__cxx11::string> keywords();

    private:
      struct Implementation;
      std::unique_ptr<Implementation> _inside;
  };

}
#endif // ENTRY_H
