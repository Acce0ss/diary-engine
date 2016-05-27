#include "entry.h"

#include <string>

#include <QDateTime>
#include <QString>
#include <QUuid>
#include <QByteArray>
#include <QList>

#include <QDebug>

namespace diaryengine {

  struct Entry::Implementation {

      Implementation(unsigned long id=0, std::string title="", std::string date="0000-00-00T00:00:00Z")
        :
          _id(id), _title(title),
          _textContent(""),
          _multimedia(),
          _date(),
          _keywords()
      {
        _date = QDateTime::fromString(QString::fromStdString(date), Qt::DateFormat::ISODate);
      }

      unsigned long _id;
      std::string _title;

      std::string _textContent;

      QList<Entry::NameMediaPair> _multimedia;

      QDateTime _date;
      QList<std::string> _keywords;

  };

  Entry::Entry() : _inside(new Implementation())
  {
  }

  Entry::~Entry()
  {
  }

  unsigned long Entry::id()
  {
    return this->_inside->_id;
  }

  void Entry::regenerateId()
  {
    unsigned long temp = 0;
    memcpy(&temp, QUuid::createUuid().toRfc4122().left(8).data(), sizeof(unsigned long));

    this->_inside->_id = temp;
  }

  void Entry::setTitle(std::__cxx11::string title)
  {
    this->_inside->_title = title;
  }

  std::__cxx11::string Entry::title()
  {
    return this->_inside->_title;
  }

  void Entry::setDate(std::__cxx11::string ISOString)
  {
    this->_inside->_date = QDateTime::fromString(QString::fromStdString(ISOString),Qt::DateFormat::ISODate);
  }

  std::__cxx11::string Entry::date()
  {
      return this->_inside->_date.toString(Qt::DateFormat::ISODate).toStdString();
  }

  void Entry::setTextContent(std::__cxx11::string content)
  {
    this->_inside->_textContent = content;
  }

  std::__cxx11::string Entry::textContent()
  {
    return this->_inside->_textContent;
  }

  bool Entry::addKeyword(std::__cxx11::string keyword)
  {
    if(this->_inside->_keywords.contains(keyword))
    {
      return false; //already exists
    }
    else
    {
      this->_inside->_keywords.append(keyword);
      return true; //successfully added
    }
  }

  bool Entry::removeKeyword(std::__cxx11::string keyword)
  {
    if(this->_inside->_keywords.contains(keyword))
    {
      this->_inside->_keywords.removeAll(keyword);
      return true; //removed
    }
    else
    {
      return false; //can't delete non-existent keyword
    }
  }

  std::list<std::__cxx11::string> Entry::keywords()
  {
    return this->_inside->_keywords.toStdList();
  }
}

