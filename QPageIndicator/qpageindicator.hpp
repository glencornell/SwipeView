#pragma once

#include <QtWidgets>

class QPageIndicator : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(int currentPage READ getCurrentPage WRITE setCurrentPage NOTIFY pageChanged);
  Q_PROPERTY(int pageCount READ getPageCount WRITE setPageCount);
  
public:
  QPageIndicator(QWidget *parent = nullptr);
  QPageIndicator(int count, QWidget *parent = nullptr);

  // Add a new page to the end of the list
  void append();

  // Remove a page from the list of pages
  void remove();

  int getCurrentPage() const;
  void setInteractive(bool isInteractive);
  int getPageCount() const;

public slots:
  // move to the given page:
  void setCurrentPage(int page);
  void setPageCount(int page);

signals:
  void pageChanged(int currentPage);
  void pageCountChanged(int pageCount);
  
private:
  int currentPage { 0 };
  int pageCount { 0 };
  QHBoxLayout *layout { nullptr };
  QList<QRadioButton*> pageButtons { };
};
