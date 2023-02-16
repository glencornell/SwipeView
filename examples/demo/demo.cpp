#include "demo.h"
#include "ui_demo.h"

demo::demo(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::demo)
{
  ui->setupUi(this);
  ui->stackedWidget->animationSpeed(650);
  connect(ui->prev,&QAbstractButton::clicked,[this]{
      if(ui->stackedWidget->gotoPrevPage()){
        ui->prev->setEnabled(false);
        ui->next->setEnabled(false);
      }
    });
  connect(ui->next,&QAbstractButton::clicked,[this]{
      if(ui->stackedWidget->gotoNextPage()){
        ui->prev->setEnabled(false);
        ui->next->setEnabled(false);
      }
    });
  connect(ui->stackedWidget,&QSwipeView::currentChanged,[this]{
      ui->pageIndicator->setCurrentPage(ui->stackedWidget->currentIndex());
    });
  connect(ui->stackedWidget,&QSwipeView::animationFinished,[this]{
      ui->prev->setEnabled(true);
      ui->next->setEnabled(true);
    });
  ui->pageIndicator->setEnabled(false);
}

demo::~demo()
{
  delete ui;
}
