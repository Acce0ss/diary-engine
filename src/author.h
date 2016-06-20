#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

namespace diaryengine {

  struct Author {
      std::string _firstName;
      std::string _lastName;
      std::string _emailAddress;
      std::string _domainName;
  };
}

#endif // AUTHOR_H
