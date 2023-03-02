#pragma once

#include <QString>
#include "XdgAbstractEntry.hpp"

class XdgDesktopFactory {
public:
  static XdgAbstractEntry *create(const QString &fileName);
private:
  XdgDesktopFactory() = delete;
};
