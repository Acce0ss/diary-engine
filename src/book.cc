#include "book.h"

#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

#include <QUuid>
#include <QByteArray>

#include "entry.h"

namespace diaryengine {

  class Book::Implementation {
    public:
      Implementation() :
        _name(""),
        _description(""),
        _entries(),
        _id(0)
      {
      }

      std::string _name;
      std::string _description;
      std::map<unsigned long, std::shared_ptr<Entry>> _entries;
      unsigned long _id;

      bool hasEntry(unsigned long id)
      {
        return (_entries.find(id) != _entries.end());
      }
  };

  std::shared_ptr<Book> Book::makeNew(std::string name,
                                      std::string description)
  {
    std::shared_ptr<Book> created = std::make_shared<Book>();

    created->setName(name);
    created->setDescription(description);
    created->regenerateId();

    return created;
  }

  Book::Book() : _inside(new Book::Implementation())
  {

  }

  Book::~Book()
  {

  }

  unsigned long Book::id()
  {
    return this->_inside->_id;
  }

  void Book::regenerateId()
  {
    unsigned long temp = 0;
    memcpy(&temp, QUuid::createUuid().toRfc4122().left(8).data(), sizeof(unsigned long));

    this->_inside->_id = temp;
  }

  std::string Book::representation()
  {
    std::stringstream ss;
    ss << this->_inside->_id << "_"
       << this->_inside->_name;

    return ss.str();
  }

  void Book::setName(std::string name)
  {
    this->_inside->_name = name;
  }

  std::string Book::name()
  {
    return this->_inside->_name;
  }

  void Book::setDescription(std::string description)
  {
    this->_inside->_description = description;
  }

  std::string Book::description()
  {
    return this->_inside->_description;
  }

  bool Book::addEntry(std::shared_ptr<Entry> entry)
  {
    if(entry) // if entry isn't null
    {
      if(this->_inside->hasEntry(entry->id()))
      {
        //this id already exists, can't readd.
        return false;
      }
      else
      {
        //Change the belongsTo value to represent this book.
        entry->setBelongsTo(this->name());
        this->_inside->_entries.insert(std::make_pair(entry->id(), entry));
        return true;
      }
    }
  }

  bool Book::removeEntry(unsigned long id)
  {
    if(this->_inside->hasEntry(id))
    {
      this->_inside->_entries.erase(id);
      return true;
    }
    else
    {
      return false;
    }
  }

  std::shared_ptr<Entry> Book::entry(unsigned long id)
  {
    if(this->_inside->hasEntry(id))
    {
      return this->_inside->_entries.at(id);
    }
    else
    {
      return std::shared_ptr<Entry>(nullptr);
    }
  }

  const std::map<unsigned long, std::shared_ptr<Entry> >& Book::entries()
  {
    return this->_inside->_entries;
  }

  bool Book::addEntriesFrom(const std::list<std::shared_ptr<Entry> >& list)
  {

  }

  std::list<std::shared_ptr<Entry>> Book::searchEntriesByTitle(std::string searchWord)
  {

  }

  std::list<std::shared_ptr<Entry> > Book::searchEntriesByKeyword(std::string keyword)
  {
    std::list<std::string> keywords;
    keywords.push_back(keyword);
    return this->searchEntriesByKeywords(keywords);
  }

  std::list<std::shared_ptr<Entry>> Book::searchEntriesByKeywords(std::list<std::string> keywords)
  {
    std::list<std::shared_ptr<Entry>> matches;
    for(auto entry : this->_inside->_entries)
    {
      auto candidate = entry.second;
      auto candidateKeywords = candidate->keywords();

      bool hasAllKeywords = true;
      for(auto keyword : keywords)
      {
        if(std::find(candidateKeywords.begin(), candidateKeywords.end(), keyword)
           == candidateKeywords.end())
        {
          hasAllKeywords = false;
        }

      }

      if (hasAllKeywords) matches.push_back(candidate);
    }

    return matches;
  }

  std::list<std::shared_ptr<Entry>> Book::searchEntriesByFullText(std::string searchText)
  {

  }

  bool Book::saveToDisk(std::string bookpath)
  {
    std::ofstream bookDescFile(bookpath + "/" + "bookinfo.txt", std::ofstream::out);

    if(bookDescFile.is_open())
    {

      bookDescFile << "X-Book-Title: " << this->_inside->_name << std::endl;
      bookDescFile << "X-Book-Description: " << this->_inside->_description << std::endl;
      bookDescFile << "X-Book-Entries: " << this->_inside->_name << std::endl;

      for(auto mapping : this->_inside->_entries)
      {
        auto entry = mapping.second;
        bookDescFile << " " << entry->representation() << std::endl;

        std::ofstream entryFile(bookpath + "/" + entry->representation(), std::ofstream::out );

        if(entryFile.is_open())
        {
          entry->asFileContentTo(entryFile);
          entryFile.close();
        }
        else
        {
          return false;
        }
      }
    }
    else
    {
      return false;
    }

    bookDescFile.close();
    return true;
  }

} // namespace diaryengine

