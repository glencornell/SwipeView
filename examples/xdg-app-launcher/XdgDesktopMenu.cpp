#include <QList>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include "XdgDesktopMenu.hpp"
#include "XdgDesktopFactory.hpp"
#include "XdgDesktopSettings.hpp"
#include "XdgInfo.hpp"

XdgDesktopMenu::XdgDesktopMenu() :
  XdgAbstractEntry(Menu)
{
}

void XdgDesktopMenu::write(const QString &fileName) const {
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "Could not open file for writing:" << fileName;
    return;
  }
  QXmlStreamWriter xml(&file);
  xml.setAutoFormatting(true);
  xml.writeStartDocument();
  xml.writeDTD("<!DOCTYPE Menu PUBLIC \"-//freedesktop//DTD Menu 1.0//EN\"\n"
               "  \"http://www.freedesktop.org/standards/menu-spec/menu-1.0.dtd\">");
  write(xml, true);
  xml.writeEndDocument();
}

void XdgDesktopMenu::write(QXmlStreamWriter &xml, bool isRootElement) const {
  xml.writeStartElement("Menu");
  if (isRootElement) {
    xml.writeAttribute("xmlns", "http://www.freedesktop.org/standards/menu-spec");
  }
  xml.writeTextElement("Name", name);
  if (this->directoryEntry && !this->directoryEntry->fileName.isEmpty())
    xml.writeTextElement("Directory", this->directoryEntry->fileName);
  if (!mergeFileName.isEmpty()) {
    // If it's a mergefile element, don't recurse
    xml.writeTextElement("Mergefile", mergeFileName);
  } else {
    type_t lastType = Unknown;
    for (XdgAbstractEntry *entry : entries) {
      switch(entry->type) {
      case Application:
        if (lastType != Application)
          xml.writeStartElement("Include");
        if (!entry->fileName.isEmpty())
          xml.writeTextElement("Filename", entry->fileName);
        break;
      case Menu:
        if (lastType == Application)
          xml.writeEndElement();
        {
          XdgDesktopMenu *submenu = reinterpret_cast<XdgDesktopMenu *>(entry);
          submenu->write(xml, false);
        }
        break;
      default:
        break;
      }
      lastType = entry->type;
    }
    xml.writeEndElement();
  }
  xml.writeEndElement();
}

XdgDesktopMenu* XdgDesktopMenu::create(const QString& desktopFileName) {
  XdgDesktopMenu* menu = nullptr;
  QFile file(desktopFileName);
  if (file.open(QFile::ReadOnly | QFile::Text)) {
    QXmlStreamReader xml(&file);
    if (xml.readNextStartElement()) {
      if (xml.name() == QLatin1String("Menu")) {
        menu = create(xml);
        menu->menuFileName = desktopFileName;
      } else {
        qDebug() << "Error: root element is not \"Menu\"";
      }
    }
  } else {
    qWarning() << "Error: cannot read file " << desktopFileName << ": " << file.errorString();
    return nullptr;
  }
  return menu;
}

XdgDesktopMenu* XdgDesktopMenu::create(QXmlStreamReader &xml) {
  XdgDesktopMenu* menu = new XdgDesktopMenu();
  menu->processMenuElement(xml);
  return menu;
}

void XdgDesktopMenu::read(QSettings &ini) {
  XdgAbstractEntry::read(ini);
}

void XdgDesktopMenu::write(QSettings &ini) const {
  XdgAbstractEntry::write(ini);
}

void XdgDesktopMenu::processNameElement(QXmlStreamReader &xml) {
  Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("Name"));
  
  name = xml.readElementText();
}

void XdgDesktopMenu::processFilenameElement(QXmlStreamReader &xml) {
  Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("Filename"));

  QString desktopFileName = xml.readElementText();
  QString canonicalFileName = XdgInfo::getInstance().find(desktopFileName, "applications", "desktop");
  XdgAbstractEntry* entry = XdgDesktopFactory::create(canonicalFileName);
  if (entry) {
    entry->fileName = desktopFileName;
    entries.append(entry);
  }
}

void XdgDesktopMenu::processDirectoryElement(QXmlStreamReader &xml) {
  Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("Directory"));

  // Update this menu's name, icon, etc.
  QString desktopFileName = xml.readElementText();
  QString canonicalFileName = XdgInfo::getInstance().find(desktopFileName, "directories", "directory");
#if 1
  directoryEntry = dynamic_cast<XdgDirectoryEntry *>(XdgDesktopFactory::create(canonicalFileName));
  if (directoryEntry) {
    directoryEntry->fileName = desktopFileName;
  }
#else
  QFileInfo fInfo(canonicalFileName);
  if (fInfo.exists() && fInfo.isFile() && fInfo.isReadable()) {
    QSettings ini(canonicalFileName,XdgDesktopSettingsFormat());
    ini.beginGroup("Desktop Entry");
    this->read(ini);
    this->fileName = desktopFileName;
    ini.endGroup();
  }
#endif
}

void XdgDesktopMenu::processIncludeElement(QXmlStreamReader &xml) {
  Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("Include"));
  
  while (xml.readNextStartElement()) {
    if(xml.name() == QLatin1String("Filename")) {
      processFilenameElement(xml);
    } else {
      qDebug() << "Include: Skipping Unknown Element : " << xml.name().toString();
      xml.skipCurrentElement();
    }
    if (xml.isEndElement() && xml.name() == QLatin1String("Include"))
      break;
  }
}

void XdgDesktopMenu::processMergefileElement(QXmlStreamReader &xml) {
  Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("Mergefile"));

  QString desktopFileName = xml.readElementText();
  QString canonicalFileName = XdgInfo::getInstance().find(desktopFileName, "menus", "menu");
  QFile file(canonicalFileName);
  if (file.open(QFile::ReadOnly | QFile::Text)) {
    QXmlStreamReader sub_xml(&file);
    if (sub_xml.readNextStartElement()) {
      if (sub_xml.name() == QLatin1String("Menu")) {
        this->processMenuElement(sub_xml);
      } else {
        qDebug() << "Error: root element is not \"Menu\"";
      }
    }
    this->mergeFileName = desktopFileName;
  } else {
    qWarning() << "Mergefile: cannot read file " << fileName << ": " << file.errorString();
  }
}

void XdgDesktopMenu::processMenuElement(QXmlStreamReader &xml) {
  Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("Menu"));
  
  while (xml.readNextStartElement()) {
    if (xml.name() == QLatin1String("Name")) {
      processNameElement(xml);
    } else if (xml.name() == QLatin1String("Directory")) {
      processDirectoryElement(xml);
    } else if (xml.name() == QLatin1String("Include")) {
      processIncludeElement(xml);
    } else if (xml.name() == QLatin1String("Mergefile")) {
      processMergefileElement(xml);
    } else if (xml.name() == QLatin1String("Menu")) {
      XdgDesktopMenu* submenu = XdgDesktopMenu::create(xml);
      if (submenu) {
        entries.append(submenu);
      } else {
        qDebug() << "Menu: Unable to create submenu";
      }
    } else {
      qDebug() << "Menu: Skipping Unknown Element : " << xml.name().toString();
      xml.skipCurrentElement();
    }
    if (xml.hasError()) {
      qWarning() << "Menu: Error parsing : " << xml.errorString();
      break;
    }
  }
}
