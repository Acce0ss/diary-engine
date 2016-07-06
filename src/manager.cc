#include "manager.h"

#include "book.h"
#include "entry.h"

namespace diaryengine {

  class Implementation {
    public:
      Implementation()
        :
      {
      }

      std::list<Book> _books;
      std::string _rootpath;
  };

  Manager::Manager()
    :
      _inside(new Implementation())
  {

  }

  Manager::~Manager()
  {

  }

  bool Manager::saveBookToDisk(Book toBeSaved)
  {

  }

} // namespace diaryengine


