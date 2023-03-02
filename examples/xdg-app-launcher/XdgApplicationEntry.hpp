#pragma once

#include <QProcess>
#include <optional>
#include "XdgAbstractEntry.hpp"

class XdgApplicationEntry : public XdgAbstractEntry {
public:
  XdgApplicationEntry();
  ~XdgApplicationEntry() = default;
  void write(const QString& filePath) const override;
  static XdgApplicationEntry *create(const QString &fileName);
  void read(QSettings &ini) override;

  QString exec;
  QString tryExec;
  QString path;
  std::optional<bool> terminal;
  
  QProcess *start(void);

protected:
  void write(QSettings &ini) const override;
};
