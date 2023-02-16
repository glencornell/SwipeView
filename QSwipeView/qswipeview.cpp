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
  if (event->button() == Qt::LeftButton) {
    pressPos = event->pos();
    QWidget *w;
    if ((w = widget(currentIndex() - 1)) != nullptr) {
      w->setGeometry ( 0,  0, frameRect().width(), frameRect().height() );
      w->show();
      w->raise();
      w->move(QPoint {
          vertical ? 0 : currentWidget()->x() - frameRect().width(),
          vertical ? currentWidget()->y() - frameRect().height() : 0
        });
    }
    if ((w = currentWidget()) != nullptr) {
      gotoPage = 0;
    }
    if ((w = widget(currentIndex() + 1)) != nullptr) {
      w->setGeometry ( 0,  0, frameRect().width(), frameRect().height() );
      w->show();
      w->raise();
      w->move(QPoint {
          vertical ? 0 : currentWidget()->x() + frameRect().width(),
          vertical ? currentWidget()->y() + frameRect().height() : 0
        });
    }
  }
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
      QWidget *w;
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
      if ((w = widget(currentIndex() - 1)) != nullptr) {
        w->move(QPoint {
            vertical ? 0 : newPos.x() - frameRect().width(),
            vertical ? newPos.y() - frameRect().height() : 0
          });
      }
      if ((w = currentWidget()) != nullptr) {
        w->move(newPos);
      }
      if ((w = widget(currentIndex() + 1)) != nullptr) {
        w->move(QPoint {
            vertical ? 0 : newPos.x() + frameRect().width(),
            vertical ? newPos.y() + frameRect().height() : 0
          });
      }
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
  const int frameWidth = frameRect().width();
  const int frameHeight = frameRect().height();
  QWidget *w;
  QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
  QPropertyAnimation *anim;
  QPoint prevWidgetNewPos;
  QPoint currWidgetNewPos;
  QPoint nextWidgetNewPos;
  
  // TODO: account for velocity as well as position.  If the distance
  // traveled is more than the minimum distance threshold OR the
  // velocity is greater than TBD threshold, then go to the next page.
  if (count() >= 1) {
    if ((distance > minDistance) && (currentIndex() >= 1)) {
      // go to previous page
      prevWidgetNewPos = { 0, 0 };
      currWidgetNewPos = {
        vertical ? 0 : frameWidth,
        vertical ? frameHeight : 0
      };
      nextWidgetNewPos = {
        vertical ? 0 : (2 * frameWidth),
        vertical ? (2 * frameHeight) : 0
      };
      gotoPage = currentIndex() - 1;
    } else if ((distance < -minDistance) && (currentIndex() < (count() - 1))) {
      // go to next page
      prevWidgetNewPos = {
        vertical ? 0 : (-2 * frameWidth),
        vertical ? (-2 * frameHeight) : 0
      };
      currWidgetNewPos = {
        vertical ? 0 : -frameWidth,
        vertical ? -frameHeight : 0
      };
      nextWidgetNewPos = { 0, 0 };
      gotoPage = currentIndex() + 1;
    } else {
      // snap back to the beginning of the same page
      prevWidgetNewPos = {
        vertical ? 0 : -frameWidth,
        vertical ? -frameHeight : 0
      };
      currWidgetNewPos = { 0, 0 };
      nextWidgetNewPos = {
        vertical ? 0 : frameWidth,
        vertical ? frameHeight : 0
      };
      gotoPage = currentIndex();
    }

    if ((w = widget(currentIndex() - 1)) != nullptr) {
      anim = new QPropertyAnimation(w, "pos");
      anim->setDuration(animationSpeed_ms);
      anim->setEasingCurve(QEasingCurve::OutQuart);
      anim->setStartValue(w->pos());
      anim->setEndValue(prevWidgetNewPos);
      animgroup->addAnimation(anim);
    }
    if ((w = currentWidget()) != nullptr) {
      anim = new QPropertyAnimation(w, "pos");
      anim->setDuration(animationSpeed_ms);
      anim->setEasingCurve(QEasingCurve::OutQuart);
      anim->setStartValue(w->pos());
      anim->setEndValue(currWidgetNewPos);
      animgroup->addAnimation(anim);
    }
    if ((w = widget(currentIndex() + 1)) != nullptr) {
      anim = new QPropertyAnimation(w, "pos");
      anim->setDuration(animationSpeed_ms);
      anim->setEasingCurve(QEasingCurve::OutQuart);
      anim->setStartValue(w->pos());
      anim->setEndValue(nextWidgetNewPos);
      animgroup->addAnimation(anim);
    }
    QObject::connect(animgroup, &QParallelAnimationGroup::finished, this, &QSwipeView::onAnimationFinished);
    animgroup->start(QAbstractAnimation::DeleteWhenStopped);
  }
  QStackedWidget::mouseReleaseEvent(event);
}

void QSwipeView::onAnimationFinished() {
  QWidget *w;
  setCurrentIndex(gotoPage);
  if ((w = widget(currentIndex() - 1)) != nullptr) {
    w->hide();
  }
  if ((w = widget(currentIndex() + 1)) != nullptr) {
    w->hide();
  }
}
