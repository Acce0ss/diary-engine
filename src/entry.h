#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <memory>

namespace diaryengine {
  class Entry
  {
    public:
      Entry();
      ~Entry();

      void setTitle(std::string title);
      std::string title();

    private:
      struct Implementation;
      std::unique_ptr<Implementation> inside_;
  };

}
#endif // ENTRY_H
