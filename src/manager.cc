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

      std::list<std::shared_ptr<Book>> _books;
      std::string _rootpath;

      bool hasBook(std::shared_ptr<Book> book)
      {
        return (std::find(this->_books.begin(),
                          this->_books.end(), book)
                != this->_books.end());
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

  bool Manager::removeBook(std::shared_ptr<Book> bookToRemove)
  {
    if( ! this->_inside->hasBook(bookToRemove))
    {
      return false;
    }
    else
    {
      this->_inside->_books.remove(bookToRemove);
      return true;
    }
  }

  std::list<std::shared_ptr<Book> > Manager::books()
  {
    return this->_inside->_books;
  }

  std::list<std::shared_ptr<Book> > Manager::searchBooksByName(std::string name)
  {

  }

  bool Manager::saveAllBooksToDisk()
  {
    unsigned int diaryNumber = 1;

    for(auto book : this->_inside->_books)
    {
      std::stringstream ss;
      ss << this->_inside->_rootpath << "/" << diaryNumber << "/";
      std::string bookpath = ss.str();

      QDir bookDir(QString::fromStdString(bookpath));

      if(bookDir.exists()) bookDir.removeRecursively();

      if( ! QDir().mkpath(QString::fromStdString(bookpath)))
      {
        return false;
      }

      if( ! book->saveToDisk(bookpath) ) return false;
    }

    return true;
  }

} // namespace diaryengine


