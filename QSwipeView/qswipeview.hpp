#pragma once

#include <QtWidgets>

class QSwipeView : public QStackedWidget
{
  Q_OBJECT
  Q_PROPERTY(int m_animationSpeed READ animationSpeed WRITE animationSpeed);
  Q_PROPERTY(int m_swipeVelocity READ swipeVelocity WRITE swipeVelocity);

public:
  QSwipeView(QWidget *parent = nullptr);
  void animationSpeed(int animationSpeed_);
  int animationSpeed() const;
  void swipeVelocity(int swipeVelocity_);
  int swipeVelocity() const;

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

private:
  int minSwipeDistance() const;
  void onAnimationFinished();
  
  bool vertical { false };
  QPoint pressPos { 0, 0 };
  int m_animationSpeed { 300 };
  int m_swipeVelocity { 100 };
  int gotoPage { -1 };
};

