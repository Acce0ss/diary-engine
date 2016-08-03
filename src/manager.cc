#include "manager.h"

#include "book.h"
#include "entry.h"

#include <sstream>

#include <QDir>
#include <QString>

namespace diaryengine {

  class Manager::Implementation {
    public:
      Implementation()
        :
          _books(),
          _rootpath("")
      {
      }

      std::map<unsigned long, std::shared_ptr<Book>> _books;
      std::string _rootpath;

      bool hasBook(unsigned long id)
      {
        return (_books.find(id) != this->_books.end());
      }
  };

  Manager::Manager()
    :
      _inside(new Implementation())
  {

  }

  Manager::~Manager()
  {

  }

  std::shared_ptr<Manager> Manager::makeNew(std::string rootpath)
  {
    std::shared_ptr<Manager> created = std::make_shared<Manager>();

    if(created->setRootpath(rootpath))
    {
      return created;
    }
    else
    {
      return std::shared_ptr<Manager>(nullptr);
    }
  }

  bool Manager::setRootpath(std::string path)
  {
    QDir rootDir(QString::fromStdString(path));
    if( ! rootDir.exists())
    {
      if( ! rootDir.mkpath(QString::fromStdString(path)))
      {
        return false;
      }
    }
    this->_inside->_rootpath = path;
    return true;
  }

  std::string Manager::rootPath()
  {
    return this->_inside->_rootpath;
  }

  bool Manager::addBook(std::shared_ptr<Book> newBook)
  {
    if(this->_inside->hasBook(newBook))
    {
      return false;
    }
    else
    {
      this->_inside->_books.push_back(newBook);
      return true;
    }
  }

  bool Manager::removeBook(unsigned long id)
  {
    if( ! this->_inside->hasBook(id))
    {
      return false;
    }
    else
    {
      this->_inside->_books.erase(id);
      return true;
    }
  }

  const std::map<unsigned long, std::shared_ptr<Book> >& Manager::books()
  {
    return this->_inside->_books;
  }

  std::list<std::shared_ptr<Book>> Manager::searchBooksByName(std::string name)
  {
    //TODO: implement
    return std::list<std::shared_ptr<Book>>();
  }

  bool Manager::saveAllBooksToDisk()
  {

    //TODO: save the books into a temporary location first;
    //      then copy to real rootpath. This is to avoid dataloss
    //      in case of write failure.
    for(auto const& idBookPair : this->_inside->_books)
    {

      std::stringstream ss;
      ss << this->_inside->_rootpath << "/"
         << idBookPair.second->representation() << "/";
      std::string bookpath = ss.str();

      QDir bookDir(QString::fromStdString(bookpath));

      if(bookDir.exists()) bookDir.removeRecursively();

      if( ! QDir().mkpath(QString::fromStdString(bookpath)))
      {
        return false;
      }

      if( ! idBookPair.second->saveToDisk(bookpath) ) return false;
    }

    return true;
  }

} // namespace diaryengine


