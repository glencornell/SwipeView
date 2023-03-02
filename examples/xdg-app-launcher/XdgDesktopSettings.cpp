#include <QIODevice>
#include "XdgDesktopSettings.hpp"

namespace {

  QSettings::Format xdgDesktopFormat = QSettings::InvalidFormat;
  bool readXdgDesktopFile(QIODevice &device, QSettings::SettingsMap &map);
  bool writeXdgDesktopFile(QIODevice &device, const QSettings::SettingsMap &map);
  
}

QSettings::Format XdgDesktopSettingsFormat(bool makeDefault) {
  if (xdgDesktopFormat == QSettings::InvalidFormat) {
    xdgDesktopFormat = QSettings::registerFormat(QStringLiteral("XdgDesktop"),
                                                 readXdgDesktopFile,
                                                 writeXdgDesktopFile,
                                                 Qt::CaseSensitive);
    if (makeDefault) {
      QSettings::setDefaultFormat(xdgDesktopFormat);
    }
  }

  return xdgDesktopFormat;
}

namespace {
  
  bool readXdgDesktopFile(QIODevice &device, QSettings::SettingsMap &map) {
    QString path;
    while (!device.atEnd())
      {
        QString line = device.readLine();
        QString nocomment = line.split("#")[0].trimmed();
        if (nocomment.contains('=')) {
          // its a name/value pair
          QStringList linelist = nocomment.split("=");
          QString name = linelist[0].trimmed();
          if (linelist[1].contains(';')) {
            QStringList stringList = linelist[1].trimmed().split(';');
            map.insert(path + name, QVariant{ stringList });
          } else 
            map.insert(path + name, QVariant{linelist[1].trimmed()});
        } else if (nocomment.contains('[')) {
          // its a group
          QString group = nocomment.remove('[').remove(']');
          path += group + "/";
        }
      }
    return true;
  }

  bool writeXdgDesktopFile(QIODevice &device, const QSettings::SettingsMap &map) {
    // The map.key() value is a string that represents the node's
    // position in the object hierarchy, similar to XML xpath.
    // Examples are "a/b/c", or "Desktop Entry/Name". Since the XDG
    // deskop entry files are only one level deep from the root node
    // and there is only one node at the root level, the code below
    // works.  If either of those two assumptions are incorrect,
    // you'll have to fix this.
    device.write("[Desktop Entry]\n");
    for(auto i = map.begin(); i != map.end() ; ++i) {
      QString path(i.key());
      QString name(path.split('/')[1]);
      QString out(name + "=");
      if (i.value().canConvert<QStringList>())
        out += i.value().toStringList().join(';');
      else
        out += i.value().toString();
      out += "\n";
      device.write(out.toUtf8());
    }
    return true;
  }

}
