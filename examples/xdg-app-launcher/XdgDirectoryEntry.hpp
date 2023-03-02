#pragma once

#include "XdgAbstractEntry.hpp"

class XdgDirectoryEntry : public XdgAbstractEntry {
public:
  XdgDirectoryEntry();
  ~XdgDirectoryEntry() = default;
  void write(const QString& filePath) const override;
  static XdgDirectoryEntry *create(const QString &fileName);
  void read(QSettings &ini) override;

  QString backgroundImage;
protected:
  void write(QSettings &ini) const override;
};
