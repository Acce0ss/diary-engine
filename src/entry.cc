#include "entry.h"

#include <string>

namespace diaryengine {

  struct Entry::Implementation {

      std::string title;
  };

  Entry::Entry() : inside_(new Implementation())
  {

  }

  Entry::~Entry()
  {

  }

  void Entry::setTitle(std::__cxx11::string title)
  {
    this->inside_->title = title;
  }

  std::__cxx11::string Entry::title()
  {
    return this->inside_->title;
  }
}

