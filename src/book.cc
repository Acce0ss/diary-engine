#include "book.h"

#include <string>
#include <map>
#include <algorithm>

#include "entry.h"

namespace diaryengine {

  class Book::Implementation {
    public:
      Implementation() :
        _name(""),
        _description(""),
        _entries()
      {

      }

      std::string _name;
      std::string _description;
      std::map<unsigned long, std::shared_ptr<Entry>> _entries;

      bool hasEntry(long id)
      {
        return (this->_entries.find(id) != this->_entries.end());
      }
  };

  std::shared_ptr<Book> Book::makeNew(std::string name,
                                      std::string description)
  {
    std::shared_ptr<Book> created = std::make_shared<Book>();

    created->setName(name);
    created->setDescription(description);

    return created;
  }

  Book::Book() : _inside(new Book::Implementation())
  {

  }

  Book::~Book()
  {

  }

  void Book::setName(std::__cxx11::string name)
  {
    this->_inside->_name = name;
  }

  std::__cxx11::string Book::name()
  {
    return this->_inside->_name;
  }

  void Book::setDescription(std::__cxx11::string description)
  {
    this->_inside->_description = description;
  }

  std::__cxx11::string Book::description()
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

  bool Book::removeEntry(long id)
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

  std::shared_ptr<Entry> Book::entry(long id)
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

  bool Book::addEntriesFrom(std::list<std::shared_ptr<Entry> > list)
  {

  }

  std::list<std::shared_ptr<Entry>> Book::searchEntriesByTitle(std::__cxx11::string searchWord)
  {

  }

  std::list<std::shared_ptr<Entry> > Book::searchEntriesByKeyword(std::__cxx11::string keyword)
  {
    std::list<std::string> keywords;
    keywords.push_back(keyword);
    return this->searchEntriesByKeywords(keywords);
  }

  std::list<std::shared_ptr<Entry>> Book::searchEntriesByKeywords(std::list<std::__cxx11::string> keywords)
  {
    std::list<std::shared_ptr<Entry>> matches;
    for(auto entry : this->_inside->_entries)
    {
      auto candidate = this->_inside->_entries.at(entry.first);
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

  std::list<std::shared_ptr<Entry>> Book::searchEntriesByFullText(std::__cxx11::string searchText)
  {

  }

} // namespace diaryengine

