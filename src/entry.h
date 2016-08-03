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

      static std::shared_ptr<Entry> makeNew(std::string author,
                                            std::string title,
                                            std::string date,
                                            std::string textContent,
                                            std::string belongsTo="default");

      unsigned long id();
      void regenerateId();

      std::string representation();

      void setBelongsTo(std::string journalName);

      void setTitle(std::string title);
      std::string title();

      void setAuthor(std::string author);
      std::string author();

      void setDate(std::string ISOString);
      std::string date();

      //Assumes all text is UTF-8 encoded. The std::string only works as
      //convenient container and common way to pass the data.
      void setTextContent(std::string content);
      const std::string& textContent();

      bool addBase64EncodedMultimediaPart(std::string name, std::string media);
      bool removeBase64EncodedMultimediaPart(std::string name);
      std::map<std::string, std::string> base64EncodedMultimediaParts();

      bool addKeyword(std::string keyword);
      bool removeKeyword(std::string keyword);
      std::list<std::string> keywords();

      void asFileContentTo(std::ostream& target);

    private:
      struct Implementation;
      std::unique_ptr<Implementation> _inside;
  };

}
#endif // ENTRY_H
