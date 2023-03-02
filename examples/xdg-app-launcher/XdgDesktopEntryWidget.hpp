#pragma once

#include <QToolButton>
#include "XdgAbstractEntry.hpp"

class XdgDesktopEntryWidget : public QToolButton {
  Q_OBJECT
public:
  XdgDesktopEntryWidget(XdgAbstractEntry *entry, QWidget* parent = nullptr);
  virtual ~XdgDesktopEntryWidget() = default;
  
  XdgAbstractEntry *entry { nullptr };

  // TODO: these should be properties of a parent widget so they all
  // share the same size.
  int fontSizePt { 8 };
  QSize iconSize { 48, 48 };
  QSize fixedSize { 64, 80 };
};
