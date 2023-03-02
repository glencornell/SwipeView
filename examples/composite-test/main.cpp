#include <QApplication>
#include <QCompositeSwipeView>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QCompositeSwipeView *swipeView = new QCompositeSwipeView;
  swipeView->resize(300,300);

  QLabel *page1 = new QLabel("Page 1");
  QLabel *page2 = new QLabel("Page 2");
  QLabel *page3 = new QLabel("Page 3");

  page1->setGeometry(QRect(0, 0, 171, 61));
  page1->setStyleSheet(QString::fromUtf8("font-size: 24px;\n"
                                         "font-weight: bold;"));
  page1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

  page2->setGeometry(0,0,300,300);
  page3->setGeometry(0,0,300,300);

  swipeView->addWidget(page1);
  swipeView->addWidget(page2);
  swipeView->addWidget(page3);

  swipeView->show();

  return app.exec();
}
