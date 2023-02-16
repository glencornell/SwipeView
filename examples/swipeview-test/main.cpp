#include <QApplication>
#include <QSwipeView>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QSwipeView swipeView;

  QLabel *page1 = new QLabel("Page 1");
  QLabel *page2 = new QLabel("Page 2");
  QLabel *page3 = new QLabel("Page 3");

  swipeView.addWidget(page1);
  swipeView.addWidget(page2);
  swipeView.addWidget(page3);

  swipeView.show();

  return app.exec();
}
