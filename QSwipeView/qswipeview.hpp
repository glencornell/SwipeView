#pragma once

#include <QtWidgets>

class QSwipeView : public QStackedWidget
{
  Q_OBJECT
  Q_PROPERTY(int m_animationSpeed READ animationSpeed WRITE animationSpeed);
  Q_PROPERTY(int m_swipeVelocity READ swipeVelocity WRITE swipeVelocity);
  Q_PROPERTY(bool m_swipeVertical READ swipeVertical WRITE swipeVertical);

public:
  explicit QSwipeView(QWidget *parent = nullptr);
  ~QSwipeView();
  
  void animationSpeed(int animationSpeed_);
  int animationSpeed() const;
  void swipeVelocity(int swipeVelocity_);
  int swipeVelocity() const;
  void swipeVertical(bool swipeVertical_);
  bool swipeVertical() const;
  bool gotoPage(int index);
  bool gotoNextPage();
  bool gotoPrevPage();

signals:
  void animationFinished(void);

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

private:
  int minSwipeDistance() const;
  void onAnimationFinished();
  
  bool m_swipeVertical { false };
  QPoint pressPos { 0, 0 };
  int m_animationSpeed { 300 };
  int m_swipeVelocity { 100 };
  int goingToPage { -1 };
};

