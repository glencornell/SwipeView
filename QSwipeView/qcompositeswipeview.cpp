#include "qcompositeswipeview.hpp"
#include "qcompositeswipeview_priv.hpp"

QCompositeSwipeView::QCompositeSwipeView(QWidget *parent) : QWidget(parent) {
  ui = new QCompositeSwipeView_Priv(this);
  ui->pageIndicator->setEnabled(false);
  connect(ui->swipeView,&QSwipeView::currentChanged,[this]{
    ui->pageIndicator->setPageCount(ui->swipeView->count());
    ui->pageIndicator->setCurrentPage(ui->swipeView->currentIndex());
    emit currentChanged(ui->swipeView->currentIndex());
  });
  connect(ui->swipeView,&QSwipeView::widgetRemoved,[this](int index){
    ui->pageIndicator->setPageCount(ui->swipeView->count());
    ui->pageIndicator->setCurrentPage(ui->swipeView->currentIndex());
    emit widgetRemoved(index);
  });
}

QCompositeSwipeView::~QCompositeSwipeView() {
  delete ui;
}

int QCompositeSwipeView::addWidget(QWidget *child) {
  const int rval = ui->swipeView->addWidget(child);
  ui->pageIndicator->setPageCount(ui->swipeView->count());
  return rval;
}

int QCompositeSwipeView::insertWidget(int index, QWidget *w) {
  const int rval = ui->swipeView->insertWidget(index, w);
  ui->pageIndicator->setPageCount(ui->swipeView->count());
  return rval;
}

void QCompositeSwipeView::removeWidget(QWidget *w) {
  ui->swipeView->removeWidget(w);
  ui->pageIndicator->setPageCount(ui->swipeView->count());
}

QWidget *QCompositeSwipeView::currentWidget() const {
  return ui->swipeView->currentWidget();
}

int QCompositeSwipeView::currentIndex() const {
  return ui->swipeView->currentIndex();
}

int QCompositeSwipeView::indexOf(QWidget *w) const {
  return ui->swipeView->indexOf(w);
}

QWidget *QCompositeSwipeView::widget(int index) const {
  return ui->swipeView->widget(index);
}

int QCompositeSwipeView::count() const {
  return ui->swipeView->count();
}

void QCompositeSwipeView::setCurrentIndex(int index) {
  ui->swipeView->setCurrentIndex(index);
}

void QCompositeSwipeView::setCurrentWidget(QWidget *w) {
  ui->swipeView->setCurrentWidget(w);
}

int QCompositeSwipeView::animationSpeed() const {
  return ui->swipeView->animationSpeed();
}

void QCompositeSwipeView::animationSpeed(int animationSpeed_) {
  ui->swipeView->animationSpeed(animationSpeed_);
}

int QCompositeSwipeView::swipeVelocity() const {
  return ui->swipeView->swipeVelocity();
}

void QCompositeSwipeView::swipeVelocity(int swipeVelocity_) {
  ui->swipeView->swipeVelocity(swipeVelocity_);
}

bool QCompositeSwipeView::swipeVertical() const {
  return ui->swipeView->swipeVertical();
}

void QCompositeSwipeView::swipeVertical(bool swipeVertical_) {
  ui->swipeView->swipeVertical(swipeVertical_);
}
