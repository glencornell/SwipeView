#include "qcompositeswipeview_priv.hpp"

QCompositeSwipeView_Priv::QCompositeSwipeView_Priv(QWidget *parent) : QWidget(parent) {
  vbox = new QVBoxLayout(this);
  swipeView = new QSwipeView();
  hbox = new QHBoxLayout();
  pageIndicator = new QPageIndicator();

  vbox->addWidget(swipeView);
  vbox->addLayout(hbox);

  hbox->addStretch();
  hbox->addWidget(pageIndicator);
  hbox->addStretch();
}
