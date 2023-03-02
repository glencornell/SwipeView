#include <QFileInfo>
#include <QDebug>
#include "XdgDesktopFactory.hpp"
#include "XdgDesktopSettings.hpp"
#include "XdgApplicationEntry.hpp"
#include "XdgDirectoryEntry.hpp"
#include "XdgDesktopMenu.hpp"

XdgAbstractEntry *XdgDesktopFactory::create(const QString &fileName) {
  XdgAbstractEntry *rval = nullptr;
  QFileInfo fInfo(fileName);
  if (fInfo.exists() && fInfo.isFile() && fInfo.isReadable()) {
    if (fInfo.suffix() == "menu") {
      rval = XdgDesktopMenu::create(fileName);
    } else {
      QSettings ini(fileName,XdgDesktopSettingsFormat());
      ini.beginGroup("Desktop Entry");
      XdgAbstractEntry::type_t type = XdgAbstractEntry::cvt(ini.value("Type").toString());
      switch(type) {
      case XdgAbstractEntry::Application:
        rval = new XdgApplicationEntry;
        break;
      case XdgAbstractEntry::Directory:
        rval = new XdgDirectoryEntry;
        break;
      default:
        qWarning() << "Unable to create object of type " << XdgAbstractEntry::cvt(type);
        break;
      }
      if (rval) {
        rval->fileName = fileName;
        rval->read(ini);
      }
      ini.endGroup();
    }
  } else {
    qWarning() << "File doesn't exist or is not readable " << fileName;
  }
  return rval;
}

