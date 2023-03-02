#pragma once

#include <QToolButton>
#include "XdgAbstractEntry.hpp"

class XdgDesktopEntryWidget : public QToolButton {
  Q_OBJECT;
  Q_PROPERTY(int fontSize MEMBER m_fontSize READ fontSize WRITE fontSize NOTIFY fontSizeChanged);
  Q_PROPERTY(QSize iconSize MEMBER m_iconSize READ iconSize WRITE iconSize NOTIFY iconSizeChanged);
  Q_PROPERTY(QSize widgetSize MEMBER m_widgetSize READ widgetSize WRITE widgetSize NOTIFY widgetSizeChanged);
public:
  XdgDesktopEntryWidget(XdgAbstractEntry *entry, QWidget* parent = nullptr);
  virtual ~XdgDesktopEntryWidget() = default;
  
  XdgAbstractEntry *entry() const;
  int fontSize() const;
  QSize iconSize() const;
  QSize widgetSize() const;
                                     
public Q_SLOTS:
  void entry(XdgAbstractEntry *e);
  void fontSize(int size);
  void iconSize(QSize size);
  void widgetSize(QSize size);

Q_SIGNALS:
  void fontSizeChanged(int size);
  void iconSizeChanged(QSize size);
  void widgetSizeChanged(QSize size);
  
protected:
  void recalculateGeometry();
  
  // TODO: these should be properties of a parent widget so they all
  // share the same size.
  int m_fontSize { 8 }; // units: points
  QSize m_iconSize { 48, 48 }; // units: pixels
  QSize m_widgetSize { 64, 80 }; // units: pixels
  XdgAbstractEntry *m_entry { nullptr };
};
