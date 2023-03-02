#include <QFileInfo>
#include <QDir>
#include "XdgDirectoryEntry.hpp"
#include "XdgDesktopSettings.hpp"

XdgDirectoryEntry::XdgDirectoryEntry() : XdgAbstractEntry(Directory) {
}

void XdgDirectoryEntry::write(const QString& fileName) const {
  QFileInfo fInfo(fileName);
  if (fInfo.dir().exists() && fInfo.dir().isReadable()) {
    QSettings ini(fileName,XdgDesktopSettingsFormat());
    ini.beginGroup("Desktop Entry");
    write(ini);
    ini.endGroup();
  } else {
    qWarning() << "directory not found or is not writable " << fInfo.dir();
  }
}

void XdgDirectoryEntry::write(QSettings &ini) const {
  XdgAbstractEntry::write(ini);
  if (!backgroundImage.isEmpty())
    ini.setValue("X-Background-Image", backgroundImage);
}

XdgDirectoryEntry *XdgDirectoryEntry::create(const QString &fileName) {
  XdgDirectoryEntry *rval = new XdgDirectoryEntry;
  QFileInfo fInfo(fileName);
  if (fInfo.exists() && fInfo.isFile() && fInfo.isReadable()) {
    QSettings ini(fileName,XdgDesktopSettingsFormat());
    ini.beginGroup("Desktop Entry");
    rval->read(ini);
    ini.endGroup();
  }
  return rval;
}

void XdgDirectoryEntry::read(QSettings &ini) {
  XdgAbstractEntry::read(ini);
  backgroundImage = ini.value("X-Background-Image","").toString();
}
