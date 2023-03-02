#pragma once
#include <QString>
#include <QStringList>
#include <QSettings>

class XdgAbstractEntry {
public:
  // Note that "Menu" and "Unknown" are not valid values for the
  // "Type" field in the desktop entry specification.  Rather, they
  // are used as sentinels for XDG Desktop Menu objects and
  // uninitialized variables, respectively.
  enum type_t { Unknown, Application, Link, Directory, Menu };
  static type_t cvt(QString const &str);
  static QString cvt(type_t const t);

public:
  XdgAbstractEntry() = delete;
  virtual ~XdgAbstractEntry() = default;
  XdgAbstractEntry(type_t t);
  virtual void write(QString const &fileName) const = 0;
  virtual void read(QSettings &ini);

  QString fileName;
  type_t type;
  QString name;
  QString icon;
  QString comment;
  QStringList categories;
  QStringList keywords;

protected:
  virtual void write(QSettings &ini) const;
};
