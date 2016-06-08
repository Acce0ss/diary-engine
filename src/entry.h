#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <memory>
#include <list>
#include <map>

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

      //Assumes all text is UTF-8 encoded. The std::string only works as
      //convenient container and common way to pass the data.
      void setTextContent(std::string content);
      const std::string& textContent();

      bool addBase64EncodedMultimediaPart(std::string name, std::string media);
      bool removeBase64EncodedMultimediaPart(std::string name);
      const std::map<std::__cxx11::string, std::__cxx11::string>& base64EncodedMultimediaParts();

      bool addKeyword(std::string keyword);
      bool removeKeyword(std::string keyword);
      const std::list<std::__cxx11::string>& keywords();

    private:
      struct Implementation;
      std::unique_ptr<Implementation> _inside;
  };

}
#endif // ENTRY_H
