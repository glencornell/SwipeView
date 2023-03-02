#pragma once
#include <QList>
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "XdgAbstractEntry.hpp"
#include "XdgDirectoryEntry.hpp"

// Represents an XDG Desktop Menu
class XdgDesktopMenu : public XdgAbstractEntry {
public:
  XdgDesktopMenu();
  ~XdgDesktopMenu() = default;
  void write(const QString &fileName) const override;
  
  // recurse through all referenced files to build a tree of menu,
  // desktop, and directory entries. fileName is stored as the
  // menuFileName if we want to overwrite the file later.
  static XdgDesktopMenu* create(const QString& fileName);
  
  void read(QSettings &ini) override;

  QString menuFileName; // the XDG menu filename (XML)
  QString mergeFileName; // the XDG menu file name (XML) that is imported into this menu
  XdgDirectoryEntry *directoryEntry { nullptr }; // If there is a directory file for this menu.
  
  QList<XdgAbstractEntry*> entries;
protected:
  void write(QXmlStreamWriter &xml, bool top) const;
  void write(QSettings &ini) const override;
  static XdgDesktopMenu* create(QXmlStreamReader &xml);
  void processNameElement(QXmlStreamReader &xml);
  void processDirectoryElement(QXmlStreamReader &xml);
  void processFilenameElement(QXmlStreamReader &xml);
  void processIncludeElement(QXmlStreamReader &xml);
  void processMergefileElement(QXmlStreamReader &xml);
  void processMenuElement(QXmlStreamReader &xml);
};
