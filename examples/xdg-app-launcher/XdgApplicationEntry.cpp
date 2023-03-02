#include <QFileInfo>
#include <QDir>
#include "XdgApplicationEntry.hpp"
#include "XdgDesktopSettings.hpp"

XdgApplicationEntry::XdgApplicationEntry() : XdgAbstractEntry(Application) {
}

void XdgApplicationEntry::write(const QString& fileName) const {
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

void XdgApplicationEntry::write(QSettings &ini) const {
  XdgAbstractEntry::write(ini);
  ini.setValue("Exec", exec);
  if (!tryExec.isEmpty())
    ini.setValue("TryExec", tryExec);
  if (!path.isEmpty())
    ini.setValue("Path", path);
  if (terminal.has_value())
    ini.setValue("Terminal", terminal.value() ? "true" : "false");
}

XdgApplicationEntry *XdgApplicationEntry::create(const QString &fileName) {
  XdgApplicationEntry *rval = new XdgApplicationEntry;
  QFileInfo fInfo(fileName);
  if (fInfo.exists() && fInfo.isFile() && fInfo.isReadable()) {
    QSettings ini(fileName,XdgDesktopSettingsFormat());
    ini.beginGroup("Desktop Entry");
    rval->read(ini);
    ini.endGroup();
  }
  return rval;
}

void XdgApplicationEntry::read(QSettings &ini) {
  XdgAbstractEntry::read(ini);
  exec = ini.value("Exec", "").toString();
  tryExec = ini.value("TryExec", "").toString();
  path = ini.value("Path", "").toString();
  {
    auto val = ini.value("Terminal");
    if (!val.isNull())
      terminal = val.toBool();
  }
}
