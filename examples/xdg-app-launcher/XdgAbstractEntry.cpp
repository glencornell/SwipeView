#include <QDebug>
#include "XdgAbstractEntry.hpp"

XdgAbstractEntry::XdgAbstractEntry(type_t t)
  : type(t)
{
}

XdgAbstractEntry::type_t XdgAbstractEntry::cvt(QString const &str)
{
  type_t rval = Unknown;
  if (str == "Application")
    rval = Application;
  else if (str == "Link")
    rval = Link;
  else if (str == "Directory")
    rval = Directory;
  else if (str == "Menu")
    rval = Menu;
  return rval;
}

QString XdgAbstractEntry::cvt(XdgAbstractEntry::type_t value)
{
  switch(value)
    {
    case Application:
      return "Application";
    case Link:
      return "Link";
    case Directory:
      return "Directory";
    case Menu:
      return "Menu";
    default:
      return "Unknown";
    }
}

void XdgAbstractEntry::write(QSettings &ini) const {
  ini.setValue("Type", cvt(type));
  ini.setValue("Name", name);
  if (!comment.isEmpty())
    ini.setValue("Comment", comment);
  if (!icon.isEmpty())
    ini.setValue("Icon", icon);
  if (!keywords.isEmpty())
    ini.setValue("Keywords", keywords.join(';'));
  if (!categories.isEmpty())
    ini.setValue("Categories", categories.join(';'));
}

void XdgAbstractEntry::read(QSettings &ini) {
  type = cvt(ini.value("Type","Unknown").toString());
  name = ini.value("Name","").toString();
  comment = ini.value("Comment","").toString();
  icon = ini.value("Icon","").toString();
  keywords = ini.value("Keywords", QStringList{}).toStringList();
  categories = ini.value("Categories", QStringList{}).toStringList();
}
