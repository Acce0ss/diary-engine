#ifndef DIARYENGINE_MANAGER_H
#define DIARYENGINE_MANAGER_H

#include <memory>
#include <list>

namespace diaryengine {

  class Entry;
  class Book;

  class Manager
  {
    public:
      Manager();
      ~Manager();

      void setRootpath(std::string path);
      std::string rootPath();

      bool addBook(Book newBook);
      std::list<Book> books();

      bool saveBookToDisk(Book toBeSaved);

      std::list<std::shared_ptr<Book>> books();

    private:
      struct Implementation;
      std::unique_ptr<Implementation> _inside;

  };

} // namespace diaryengine

#endif // DIARYENGINE_MANAGER_H
