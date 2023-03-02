#include <QAction>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include "XdgApplicationEntry.hpp"
#include "XdgDesktopEntryWidget.hpp"
#include "XdgDesktopMenu.hpp"
#include "XdgInfo.hpp"

XdgDesktopEntryWidget::XdgDesktopEntryWidget(XdgAbstractEntry *entry_, QWidget* parent)
  : QToolButton(parent), m_entry(entry_)
{
  Q_ASSERT(m_entry != nullptr);
  recalculateGeometry();
  this->setEnabled(true);
  switch (m_entry->type) {
  case XdgAbstractEntry::Application:
    // just for kicks until we are able to:
    //    1. parse the Exec, TryExec and Terminal desktop entries properly
    //    2. manage child processes
    //    3. 
    connect(this,&QToolButton::clicked,[this](){
      XdgApplicationEntry *appEntry = dynamic_cast<XdgApplicationEntry *>(m_entry);
      qDebug() << QString("Starting Process : %1").arg(appEntry->exec);
    });
    break;
  case XdgAbstractEntry::Menu:
    // just for kicks until we are able to:
    //    1. display submenus
    connect(this,&QToolButton::clicked,[this](){
      XdgDesktopMenu *menuEntry = dynamic_cast<XdgDesktopMenu *>(m_entry);
      qDebug() << QString("Navigating to Submenu : %1").arg(menuEntry->name);
    });
    break;
  default:
    // This shouldn't happen:
    connect(this,&QToolButton::clicked,[this](){
      qWarning() << QString("Unsupported action for entry : %1").arg(m_entry->name);
    });
    break;
  }
}

void XdgDesktopEntryWidget::recalculateGeometry()
{
  QString newIconName = m_entry->icon;
  QString backgroundImage = "";
  if (m_entry->type == XdgAbstractEntry::Menu) {
    XdgDesktopMenu *menuEntry = dynamic_cast<XdgDesktopMenu *>(m_entry);
    if (menuEntry->directoryEntry) {
      newIconName = menuEntry->directoryEntry->icon;
      backgroundImage = QString("background-image : url(%1); ")
        .arg(XdgInfo::getInstance().find(menuEntry->directoryEntry->backgroundImage, "pixmaps", ".png"));
    }
  }
  QString iconFileName = XdgInfo::getInstance().find(newIconName, "icons", ".png");
  if (iconFileName.isEmpty()) {
    qDebug() << "No Icon found. Using default";
    iconFileName = XdgInfo::getInstance().find("penguin", "pixmaps/faces", ".jpg");
    Q_ASSERT(!iconFileName.isEmpty());
    setIcon(QIcon(iconFileName));
  } else {
    setIcon(QIcon(iconFileName));
  }
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  setIconSize(m_iconSize);
  setText(m_entry->name);
  setObjectName(m_entry->name);
  setFixedSize(m_widgetSize);
  QString styleSheet = QString("QToolButton%1 { border : none; font-size : %2pt; margin: 0px; padding: 0px; %3}")
    .arg(m_entry->name.isEmpty() ? "" : QString("#" + m_entry->name))
    .arg(m_fontSize)
    .arg(backgroundImage);
  setStyleSheet(styleSheet);
}

void XdgDesktopEntryWidget::entry(XdgAbstractEntry *e) {
  m_entry = e;
  recalculateGeometry();
}

void XdgDesktopEntryWidget::fontSize(int size) {
  m_fontSize = size;
  recalculateGeometry();
  emit fontSizeChanged(m_fontSize);
}

void XdgDesktopEntryWidget::iconSize(QSize size) {
  m_iconSize = size;
  recalculateGeometry();
  emit iconSizeChanged(m_iconSize);
}

void XdgDesktopEntryWidget::widgetSize(QSize size) {
  m_widgetSize = size;
  recalculateGeometry();
  emit widgetSizeChanged(m_widgetSize);
}

XdgAbstractEntry *XdgDesktopEntryWidget::entry() const {
  return m_entry;
}

int XdgDesktopEntryWidget::fontSize() const {
  return m_fontSize;
}

QSize XdgDesktopEntryWidget::iconSize() const {
  return m_iconSize;
}

QSize XdgDesktopEntryWidget::widgetSize() const {
  return m_widgetSize;
}
