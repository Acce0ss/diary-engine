#include "book.h"

#include <string>
#include <map>

#include "entry.h"

namespace diaryengine {

  class Book::Implementation {
    public:
      Implementation(std::string name) :
        _name(name), _description(""),
        _entries()
      {

      }

      std::string _name;
      std::string _description;
      std::map<unsigned long, std::shared_ptr<Entry>> _entries;
  };

  Book::Book(std::string name) : _inside(new Book::Implementation(name))
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
    if(this->_inside->_entries.find(entry->id()) != this->_inside->_entries.end())
    {
      //entry with this id already exists.
      return false;
    }
    else
    {
      this->_inside->_entries.insert(std::make_pair(entry->id(), entry));
      return true;
    }
  }

  bool Book::removeEntry(long id)
  {

  }

  unsigned long Book::searchEntryByTitle(std::__cxx11::string searchWord)
  {

  }

  unsigned long Book::searchEntryByKeywords(std::list<std::__cxx11::string> keywords)
  {

  }

  unsigned long Book::searchEntryByFullText(std::__cxx11::string searchText)
  {

  }

} // namespace diaryengine

