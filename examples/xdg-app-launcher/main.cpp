#include <QApplication>
#include <QGridLayout>
#include <QTextStream>
#include <QString>
#include <QFile>
#include <QXmlStreamWriter>
#include "XdgApplicationEntry.hpp"
#include "XdgDesktopEntryWidget.hpp"
#include "XdgInfo.hpp"
#include "XdgDesktopMenu.hpp"
#include "XdgDesktopFactory.hpp"
#include <QSwipeView>
#include <QCompositeSwipeView>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  XdgDesktopMenu *homeMenu = XdgDesktopMenu::create
    (XdgInfo::getInstance().find("home", "menus", "menu"));
  if (homeMenu) {
    homeMenu->write("test.menu");
  } else {
    qDebug() << "ERROR: home menu not loaded";
  }
  
#if 1

#if 0
  QCompositeSwipeView *swipeView = new QCompositeSwipeView;
#else
  QSwipeView *swipeView = new QSwipeView;
#endif
  
  const int rowsPerPage = 2;
  const int columnsPerPage = 2;
  const int iconsPerPage = columnsPerPage * rowsPerPage;
  const int iconCount = homeMenu->entries.count();
  const int maxPages = (iconCount + iconsPerPage) / iconsPerPage;
  int index = 0;
  
  for (int currentPage = 0; currentPage < maxPages; currentPage++) {
    // Create a new page in the swipeview:
    QWidget* page = new QWidget();
    
    // Add widgets to grid layout
    QGridLayout* layout = new QGridLayout();
    for (int rowIndex = 0; rowIndex < rowsPerPage && index < iconCount; rowIndex++) {
      for (int columnIndex = 0; columnIndex < columnsPerPage && index < iconCount; columnIndex++) {
        XdgDesktopEntryWidget *xdgEntryWidget = new XdgDesktopEntryWidget(homeMenu->entries[index]);
        layout->addWidget(xdgEntryWidget, rowIndex, columnIndex);
        index++;
      }
    }
    page->setLayout(layout);
    swipeView->addWidget(page);
  }
  swipeView->setObjectName(homeMenu->name);
  QString styleSheet = QString("QWidget#%1 { background-image : url(%2); }")
    .arg(homeMenu->name)
    .arg(XdgInfo::getInstance().find(homeMenu->directoryEntry->backgroundImage, "pixmaps", "png"));
  swipeView->setStyleSheet(styleSheet);
  swipeView->show();

#else
  
  // Create XdgDesktopEntry objects
  XdgApplicationEntry *entry1 = XdgApplicationEntry::create
    (XdgInfo::getInstance().find("calculator", "applications", "desktop"));
  XdgApplicationEntry *entry2 = XdgApplicationEntry::create
    (XdgInfo::getInstance().find("clock", "applications", "desktop"));
  XdgApplicationEntry *entry3 = XdgApplicationEntry::create
    (XdgInfo::getInstance().find("slack", "applications", "desktop"));
  XdgApplicationEntry *entry4 = XdgApplicationEntry::create
    (XdgInfo::getInstance().find("htop", "applications", "desktop"));
  XdgApplicationEntry *entry5 = XdgApplicationEntry::create
    (XdgInfo::getInstance().find("signal-desktop", "applications", "desktop"));

  // Create XdgDesktopEntryWidgets
  XdgDesktopEntryWidget* widget1 = new XdgDesktopEntryWidget(entry1);
  XdgDesktopEntryWidget* widget2 = new XdgDesktopEntryWidget(entry2);
  XdgDesktopEntryWidget* widget3 = new XdgDesktopEntryWidget(entry3);
  XdgDesktopEntryWidget* widget4 = new XdgDesktopEntryWidget(entry4);
  XdgDesktopEntryWidget* widget5 = new XdgDesktopEntryWidget(entry5);

  QGridLayout* layout = new QGridLayout();

  // Add widgets to grid layout
  layout->addWidget(widget1, 0, 0);
  layout->addWidget(widget2, 0, 1);
  layout->addWidget(widget3, 0, 3);
  layout->addWidget(widget4, 1, 0);
  layout->addWidget(widget5, 2, 0);
  
  // Set main window
  QWidget* window = new QWidget();
  window->setObjectName("home");
  window->setStyleSheet("QWidget#home { background-image : url(etc/pixmaps/wp.png); }");
  window->setLayout(layout);
  window->show();

#endif
  
  return a.exec();
}
