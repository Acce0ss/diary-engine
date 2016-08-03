#ifndef DIARYENGINE_MANAGER_H
#define DIARYENGINE_MANAGER_H

#include <memory>
#include <list>
#include <map>

namespace diaryengine {

  class Entry;
  class Book;

  class Manager
  {
    public:
      Manager();
      ~Manager();

      static std::shared_ptr<Manager> makeNew(std::string rootpath);

      bool setRootpath(std::string path);
      std::string rootPath();

      bool addBook(std::shared_ptr<Book> newBook);
      bool removeBook(unsigned long id);
      std::shared_ptr<Book> book(unsigned long id);
      const std::map<unsigned long, std::shared_ptr<Book> >& books();

      std::list<std::shared_ptr<Book>> searchBooksByName(std::string name);

      bool saveAllBooksToDisk();

    private:
      struct Implementation;
      std::unique_ptr<Implementation> _inside;

  };

} // namespace diaryengine

#endif // DIARYENGINE_MANAGER_H
