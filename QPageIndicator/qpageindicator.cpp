#include "qpageindicator.hpp"

QPageIndicator::QPageIndicator(QWidget *parent) : QWidget(parent), currentPage(0)
{
  layout = new QHBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);
  // There must be at least one page:
  append();
  setCurrentPage(0);
}

QPageIndicator::QPageIndicator(int count, QWidget *parent) : QWidget(parent), currentPage(0)
{
  layout = new QHBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  if (count <= 0)
    count = 1;
  
  for (int i = 0; i < count; i++) {
    append();
  }

  setCurrentPage(0);
}

void QPageIndicator::append()
{
  QRadioButton *button = new QRadioButton(this);
  button->setStyleSheet
    ("QRadioButton::indicator:checked {"
     "  border: 1px solid #5d5b59;" // medium gray
     "  border-radius: 6px;"
     "  background-color: #5d5b59;"
     "}"
     "QRadioButton::indicator:unchecked {"
     "  border: 1px solid #aeadac;" // light gray
     "  border-radius: 6px;"
     "  background-color: #aeadac;"
     "}");
  pageButtons.append(button);
  pageCount = pageButtons.size();
  int i = pageButtons.size() - 1;
  layout->addWidget(button);
  connect(button, &QRadioButton::clicked, [this, i]() { setCurrentPage(i); });
}

void QPageIndicator::remove()
{
  if (pageButtons.size() > 1) {
    int nextPage = currentPage;
    if (nextPage == pageButtons.size()) {
      nextPage--;
    }
    QRadioButton *button = pageButtons.last();
    pageButtons.removeLast();
    delete button;
    pageCount = pageButtons.size();
    setCurrentPage(nextPage);
  }
}

void QPageIndicator::setCurrentPage(int page)
{
  if (page >= 0 && page < pageButtons.size()) {
    currentPage = page;
    for (int i = 0; i < pageButtons.size(); i++)
      pageButtons[i]->setChecked(i == currentPage);
    emit pageChanged(page);
  }
}

int QPageIndicator::getCurrentPage() const
{
  return currentPage;
}

void QPageIndicator::setInteractive(bool isInteractive)
{
  for (int i = 0; i < pageButtons.size(); i++)
    pageButtons[i]->setEnabled(isInteractive);
}

void QPageIndicator::setPageCount(int reqPageCount)
{
  const int pageCount = pageButtons.size();
  if (reqPageCount >= 0) {
    if (reqPageCount > pageCount) {
      for(int i = pageCount; i < reqPageCount; i++)
        append();
    } else if (reqPageCount < pageCount) {
      for(int i = pageCount; i < reqPageCount; i++)
        remove();
    }
  }
}

int QPageIndicator::getPageCount() const
{
  return pageButtons.size();
}
