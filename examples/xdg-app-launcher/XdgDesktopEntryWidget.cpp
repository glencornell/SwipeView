#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include "XdgDesktopEntryWidget.hpp"
#include "XdgDesktopMenu.hpp"
#include "XdgInfo.hpp"

XdgDesktopEntryWidget::XdgDesktopEntryWidget(XdgAbstractEntry *entry_, QWidget* parent)
  : QToolButton(parent), entry(entry_)
{
  QString newIconName = entry->icon;
  QString backgroundImage = "";
  if (entry->type == XdgAbstractEntry::Menu) {
    XdgDesktopMenu *menuEntry = dynamic_cast<XdgDesktopMenu *>(entry);
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
  setIconSize(iconSize);
  setText(entry->name);
  setObjectName(entry->name);
  setFixedSize(fixedSize);
  QString styleSheet = QString("QToolButton%1 { border : none; font-size : %2pt; margin: 0px; padding: 0px; %3}")
    .arg(entry->name.isEmpty() ? "" : QString("#" + entry->name))
    .arg(fontSizePt)
    .arg(backgroundImage);
  setStyleSheet(styleSheet);
}
