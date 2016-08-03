#include "entry.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <QDateTime>
#include <QString>
#include <QUuid>
#include <QByteArray>
#include <QList>
#include <QMap>

#include <QDebug>

namespace diaryengine {

  class Entry::Implementation {
    public:

      Implementation()
        :
          _id(0), _title(""), _author(""), _belongsTo(""),
          _textContent(""),
          _multimedia(),
          _date(),
          _keywords()
      {
        _date = QDateTime::fromString(QString::fromStdString("0000-00-00T00:00:00Z"),
                                      Qt::DateFormat::ISODate);
      }

      unsigned long _id;

      std::string _title;
      std::string _author;
      std::string _belongsTo;

      std::string _textContent;

      QMap<std::string,std::string> _multimedia;

      QDateTime _date;
      QList<std::string> _keywords;

      std::string boundaryString()
      {
        std::stringstream ss;

        ss << "bound-" << this->_id;

        return ss.str();
      }

      std::string boundaryLine()
      {
        std::stringstream ss;
        ss << "--" << boundaryString() << std::endl;
        return ss.str();
      }

      std::string joinedKeywords()
      {
        std::stringstream ss;
        auto keywords =  this->_keywords.toStdList();
        keywords.sort();

        if( ! keywords.empty() )
        {
          for(auto it = keywords.begin(); it != keywords.end(); ++it)
          {
            ss << (*it) << (it != --keywords.end() ? "," : "");
          }
        }

        return ss.str();
      }
  };

  Entry::Entry() : _inside(new Implementation())
  {
  }

  Entry::~Entry()
  {
  }

  std::shared_ptr<Entry> Entry::makeNew(std::string author,
                                        std::string title,
                                        std::string date,
                                        std::string textContent,
                                        std::string belongsTo)
  {
    std::shared_ptr<Entry> created = std::make_shared<Entry>();

    created->setAuthor(author);
    created->setTitle(title);
    created->setDate(date);
    created->setBelongsTo(belongsTo);
    created->setTextContent(textContent);
    created->regenerateId(); // generate a random id for this instance, as it is a new
                             // entry

    return created;
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

  std::string Entry::representation()
  {
    std::stringstream ss;
    ss << this->_inside->_id << "_"
       << this->_inside->_date.toString("YYYYMMdd").toStdString() << "_";

    return ss.str();
  }

  void Entry::setBelongsTo(std::__cxx11::string journalName)
  {
    this->_inside->_belongsTo = journalName;
  }

  void Entry::setTitle(std::__cxx11::string title)
  {
    this->_inside->_title = title;
  }

  std::__cxx11::string Entry::title()
  {
    return this->_inside->_title;
  }

  void Entry::setAuthor(std::__cxx11::string author)
  {
    this->_inside->_author = author;
  }

  std::__cxx11::string Entry::author()
  {
    return this->_inside->_author;
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

  const std::string& Entry::textContent()
  {
    return this->_inside->_textContent;
  }

  bool Entry::addBase64EncodedMultimediaPart(std::__cxx11::string name, std::__cxx11::string media)
  {
    if(this->_inside->_multimedia.contains(name))
    {
      return false;
    }
    else
    {
      this->_inside->_multimedia.insert(name, media);
      return true;
    }
  }

  bool Entry::removeBase64EncodedMultimediaPart(std::string name)
  {
    if(this->_inside->_multimedia.contains(name))
    {
      this->_inside->_multimedia.remove(name);
      return true;
    }
    else
    {
      return false;
    }
  }

  std::map<std::__cxx11::string, std::__cxx11::string> Entry::base64EncodedMultimediaParts()
  {
    return this->_inside->_multimedia.toStdMap();
  }

  bool Entry::addKeyword(std::string keyword)
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

  bool Entry::removeKeyword(std::string keyword)
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

  void Entry::asFileContentTo(std::ostream& target)
  {
    target << "From: \"" << this->author() << "\" <author@domain.com>" << std::endl;
    target << "Date: " << this->date() << std::endl;
    target << "Message-ID: <" << this->id() << "@" << this->_inside->_belongsTo << ">" << std::endl;
    target << "Subject: " << this->title() << std::endl;
    target << "X-Engine-Version: " << DIARYENGINE_VERSION << std::endl;
    target << "X-Entry-Keywords: " << this->_inside->joinedKeywords() << std::endl;
    target << "Content-Type: multipart/mixed; boundary=\"" << this->_inside->boundaryString() << "\"" << std::endl;

    target << std::endl;

    target << this->_inside->boundaryLine();
    target << "Content-Type: text/plain; charset=\"UTF-8\"" << std::endl << std::endl;
    target << this->textContent() << std::endl << std::endl;

    for(auto multimedia : this->base64EncodedMultimediaParts())
    {

    }

    target << "--" << this->_inside->boundaryString() << "--" << std::endl;

  }
}

