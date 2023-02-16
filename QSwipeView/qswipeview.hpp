#pragma once

#include <QtWidgets>

class QSwipeView : public QStackedWidget
{
  Q_OBJECT

public:
  QSwipeView(QWidget *parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

private:
  int minSwipeDistance() const;
  void onAnimationFinished();
  
  bool vertical { false };
  QPoint pressPos { 0, 0 };
  QPoint movePos { 0, 0 };
  int animationSpeed_ms { 300 };
  int gotoPage { -1 };
};

