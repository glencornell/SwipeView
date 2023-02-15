#include "qswipeview.hpp"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

QSwipeView::QSwipeView(QWidget *parent) :
  QStackedWidget(parent)
{
}

int QSwipeView::minSwipeDistance() const
{
  // The minimum swipe distance required to move to the prev/next page
  return (vertical ?
          frameRect().height() :
          frameRect().width()) / 3;
}

void QSwipeView::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
    pressPos = event->pos();
  QStackedWidget::mousePressEvent(event);
}

void QSwipeView::mouseMoveEvent(QMouseEvent *event)
{
  if (event->buttons() & Qt::LeftButton) {
    movePos = event->pos();
    if (count() >= 1) {
      const int begin       = vertical ? pressPos.y() : pressPos.x();
      const int end         = vertical ? movePos.y()  : movePos.x();
      const int distance    = end - begin;
      const int minDistance = minSwipeDistance();
      QPoint newPos {
        vertical ? 0 : distance,
        vertical ? distance : 0
      };
      if ((distance > minDistance) && (currentIndex() == 0)) {
        newPos = QPoint {
          vertical ? 0 : minDistance,
          vertical ? minDistance : 0
        };
      } else if ((distance < -minDistance) && (currentIndex() == (count() - 1))) {
        newPos = QPoint {
          vertical ? 0 : - minDistance,
          vertical ? - minDistance : 0
        };
      }
      currentWidget()->move(newPos);
    }
  }
  QStackedWidget::mouseMoveEvent(event);
}

void QSwipeView::mouseReleaseEvent(QMouseEvent *event)
{
  const int begin        = vertical ? pressPos.y() : pressPos.x();
  const int end          = vertical ? movePos.y()  : movePos.x();
  const int distance     = end - begin;
  const int minDistance = minSwipeDistance();
  bool pageChanged = false;
  
  // TODO: account for velocity as well as position.  If the distance
  // traveled is more than the minimum distance threshold OR the
  // velocity is greater than TBD threshold, then go to the next page.
  if (distance > minDistance) {
    // go to previous page 
    QWidget *oldWidget = currentWidget();
    setCurrentIndex(currentIndex() - 1); // down the stack
    oldWidget->move(QPoint {0, 0});
    pageChanged = true;
  } else if (distance < -minDistance) {
    // go to next page
    QWidget *oldWidget = currentWidget();
    setCurrentIndex(currentIndex() + 1); // up the stack
    oldWidget->move(QPoint {0, 0});
    pageChanged = true;
  }

  if (!pageChanged) {
    // stay on the current page but move the top stacked widget back
    // to its origin
    QPropertyAnimation *slideCurrentPageHomeAnimation = new QPropertyAnimation(currentWidget(), "pos");
    slideCurrentPageHomeAnimation->setDuration(animationSpeed_ms);
    slideCurrentPageHomeAnimation->setEasingCurve(QEasingCurve::OutQuart);
    slideCurrentPageHomeAnimation->setStartValue(currentWidget()->pos());
    slideCurrentPageHomeAnimation->setEndValue(QPoint{0,0});
    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(slideCurrentPageHomeAnimation);
    animgroup->start(QAbstractAnimation::DeleteWhenStopped);
  }
  QStackedWidget::mouseReleaseEvent(event);
}
