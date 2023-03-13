#include "qswipeview.hpp"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

QSwipeView::QSwipeView(QWidget *parent) :
  QStackedWidget(parent)
{
}

QSwipeView::~QSwipeView()
{
}

int QSwipeView::minSwipeDistance() const
{
  // The minimum swipe distance required to move to the prev/next page
  return (m_swipeVertical ?
          frameRect().height() :
          frameRect().width()) / 3;
}

int QSwipeView::animationSpeed() const
{
  return m_animationSpeed;
}

void QSwipeView::animationSpeed(int animationSpeed_)
{
  m_animationSpeed = animationSpeed_;
}

int QSwipeView::swipeVelocity() const
{
  return m_swipeVelocity;
}

void QSwipeView::swipeVelocity(int swipeVelocity_)
{
  m_swipeVelocity = swipeVelocity_;
}

bool QSwipeView::swipeVertical() const
{
  return m_swipeVertical;
}

void QSwipeView::swipeVertical(bool swipeVertical_)
{
  m_swipeVertical = swipeVertical_;
}

void QSwipeView::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    pressPos = QCursor::pos();
  }
  QStackedWidget::mousePressEvent(event);
}

void QSwipeView::mouseMoveEvent(QMouseEvent *event)
{
  if (event->buttons() & Qt::LeftButton) {
    if (count() >= 1) {
      if ((pressPos.x() == -1) || (pressPos.y() == -1)) {
        // if the mouse button event was missed, we use the sentinel
        // value of (-1,-1) pressPos to set it to the current cursor
        // position.  The mouse button press event is missed if the
        // user presses a pushbutton widget in the hierarchy.  The
        // only way to get the mousePressEvent from the pushbutton
        // widget is to call installEventFilter() in notifyChild() for
        // each new widget that is added in the hierarchy.  Ive
        // decided not to implement this because it will add
        // significantly more code when in my use case (the child is a
        // grid layout with pushbuttons), the impact is minor (the
        // page doesn't start to swipe until after you traverse the
        // pushbutton).
        pressPos = QCursor::pos();
      }
      const QPoint movePos { QCursor::pos() };
      const int begin       = m_swipeVertical ? pressPos.y() : pressPos.x();
      const int end         = m_swipeVertical ? movePos.y()  : movePos.x();
      const int distance    = end - begin;
      const int minDistance = minSwipeDistance();
      const int frameWidth   = frameRect().width();
      const int frameHeight  = frameRect().height();

      QWidget *w;
      QPoint newPos {
        m_swipeVertical ? 0 : distance,
        m_swipeVertical ? distance : 0
      };
      if ((distance > minDistance) && (currentIndex() == 0)) {
        newPos = QPoint {
          m_swipeVertical ? 0 : minDistance,
          m_swipeVertical ? minDistance : 0
        };
      } else if ((distance < -minDistance) && (currentIndex() == (count() - 1))) {
        newPos = QPoint {
          m_swipeVertical ? 0 : - minDistance,
          m_swipeVertical ? - minDistance : 0
        };
      }
      if ((w = widget(currentIndex() - 1)) != nullptr) {
        if (!w->isVisible()) {
          w->setGeometry ( 0,  0, frameWidth, frameHeight );
          w->show();
        }
        w->move(QPoint {
            m_swipeVertical ? 0 : newPos.x() - frameWidth,
            m_swipeVertical ? newPos.y() - frameHeight : 0
          });
      }
      if ((w = currentWidget()) != nullptr) {
        if (!w->isVisible()) {
          w->setGeometry ( 0,  0, frameWidth, frameHeight );
          w->show();
        }
        w->move(newPos);
      }
      if ((w = widget(currentIndex() + 1)) != nullptr) {
        if (!w->isVisible()) {
          w->setGeometry ( 0,  0, frameWidth, frameHeight );
          w->show();
        }
        w->move(QPoint {
            m_swipeVertical ? 0 : newPos.x() + frameWidth,
            m_swipeVertical ? newPos.y() + frameHeight : 0
          });
      }
    }
  }
  QStackedWidget::mouseMoveEvent(event);
}

void QSwipeView::mouseReleaseEvent(QMouseEvent *event)
{
  if ((pressPos.x() == -1) || (pressPos.y() == -1)) {
    pressPos = QCursor::pos();
  }
  const QPoint movePos { QCursor::pos() };
  const int begin        = m_swipeVertical ? pressPos.y() : pressPos.x();
  const int end          = m_swipeVertical ? movePos.y()  : movePos.x();
  const int distance     = end - begin;
  const int minDistance  = minSwipeDistance();
  const int velocity     = m_swipeVertical ? event->point(event->pointCount() - 1).velocity().y() : event->point(event->pointCount() - 1).velocity().x();
  const int minVelocity  = swipeVelocity();
  const int frameWidth   = frameRect().width();
  const int frameHeight  = frameRect().height();

  QWidget *w;
  QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
  QPropertyAnimation *anim;
  QPoint prevWidgetNewPos;
  QPoint currWidgetNewPos;
  QPoint nextWidgetNewPos;

  // If the distance traveled is more than the minimum distance
  // threshold OR the velocity is greater than the velocity threshold,
  // then go to the next page.  Otherwise, bounce back to the origin.
  if (count() >= 1) {
    if (((distance > minDistance) || (velocity > minVelocity)) && (currentIndex() >= 1)) {
      // go to previous page
      prevWidgetNewPos = { 0, 0 };
      currWidgetNewPos = {
        m_swipeVertical ? 0 : frameWidth,
        m_swipeVertical ? frameHeight : 0
      };
      nextWidgetNewPos = {
        m_swipeVertical ? 0 : (2 * frameWidth),
        m_swipeVertical ? (2 * frameHeight) : 0
      };
      goingToPage = currentIndex() - 1;
    } else if ((((distance < -minDistance)) || (velocity < -minVelocity)) && (currentIndex() < (count() - 1))) {
      // go to next page
      prevWidgetNewPos = {
        m_swipeVertical ? 0 : (-2 * frameWidth),
        m_swipeVertical ? (-2 * frameHeight) : 0
      };
      currWidgetNewPos = {
        m_swipeVertical ? 0 : -frameWidth,
        m_swipeVertical ? -frameHeight : 0
      };
      nextWidgetNewPos = { 0, 0 };
      goingToPage = currentIndex() + 1;
    } else {
      // snap back to the beginning of the same page
      prevWidgetNewPos = {
        m_swipeVertical ? 0 : -frameWidth,
        m_swipeVertical ? -frameHeight : 0
      };
      currWidgetNewPos = { 0, 0 };
      nextWidgetNewPos = {
        m_swipeVertical ? 0 : frameWidth,
        m_swipeVertical ? frameHeight : 0
      };
      goingToPage = currentIndex();
    }

    if ((w = widget(currentIndex() - 1)) != nullptr) {
      anim = new QPropertyAnimation(w, "pos");
      anim->setDuration(m_animationSpeed);
      anim->setEasingCurve(QEasingCurve::OutQuart);
      anim->setStartValue(w->pos());
      anim->setEndValue(prevWidgetNewPos);
      animgroup->addAnimation(anim);
    }
    if ((w = currentWidget()) != nullptr) {
      anim = new QPropertyAnimation(w, "pos");
      anim->setDuration(m_animationSpeed);
      anim->setEasingCurve(QEasingCurve::OutQuart);
      anim->setStartValue(w->pos());
      anim->setEndValue(currWidgetNewPos);
      animgroup->addAnimation(anim);
    }
    if ((w = widget(currentIndex() + 1)) != nullptr) {
      anim = new QPropertyAnimation(w, "pos");
      anim->setDuration(m_animationSpeed);
      anim->setEasingCurve(QEasingCurve::OutQuart);
      anim->setStartValue(w->pos());
      anim->setEndValue(nextWidgetNewPos);
      animgroup->addAnimation(anim);
    }
    QObject::connect(animgroup, &QParallelAnimationGroup::finished, this, &QSwipeView::onAnimationFinished);
    animgroup->start(QAbstractAnimation::DeleteWhenStopped);
    pressPos = { -1, -1 };
  }
  QStackedWidget::mouseReleaseEvent(event);
}

void QSwipeView::onAnimationFinished() {
  QWidget *w;
  setCurrentIndex(goingToPage);
  if ((w = widget(currentIndex() - 1)) != nullptr) {
    w->hide();
  }
  if ((w = widget(currentIndex() + 1)) != nullptr) {
    w->hide();
  }
  emit animationFinished();
}

bool QSwipeView::gotoPage(int index) {
  bool rval = false;

  if (count() >= 1 && 0 <= index && index < count()) {
    const int frameWidth   = frameRect().width();
    const int frameHeight  = frameRect().height();

    QWidget *w;
    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    QPropertyAnimation *anim;
    QPoint prevWidgetNewPos;
    QPoint currWidgetNewPos;
    QPoint nextWidgetNewPos;

    rval = true;

    if (index < currentIndex()) {
      // go to a previous page
      prevWidgetNewPos = { 0, 0 };
      currWidgetNewPos = {
        m_swipeVertical ? 0 : frameWidth,
        m_swipeVertical ? frameHeight : 0
      };
      if ((w = widget(index)) != nullptr) {
        w->setGeometry ( 0,  0, frameWidth, frameHeight );
        w->show();
        w->raise();
        w->move(QPoint {
            m_swipeVertical ? 0 : - frameWidth,
            m_swipeVertical ? - frameHeight : 0
          });
        anim = new QPropertyAnimation(w, "pos");
        anim->setDuration(m_animationSpeed);
        anim->setEasingCurve(QEasingCurve::OutQuart);
        anim->setStartValue(w->pos());
        anim->setEndValue(prevWidgetNewPos);
        animgroup->addAnimation(anim);
      }
      if ((w = currentWidget()) != nullptr) {
        anim = new QPropertyAnimation(w, "pos");
        anim->setDuration(m_animationSpeed);
        anim->setEasingCurve(QEasingCurve::OutQuart);
        anim->setStartValue(w->pos());
        anim->setEndValue(currWidgetNewPos);
        animgroup->addAnimation(anim);
      }
      goingToPage = index;
    } else if (index > currentIndex()) {
      // go to a later page
      currWidgetNewPos = {
        m_swipeVertical ? 0 : -frameWidth,
        m_swipeVertical ? -frameHeight : 0
      };
      nextWidgetNewPos = { 0, 0 };
      if ((w = currentWidget()) != nullptr) {
        anim = new QPropertyAnimation(w, "pos");
        anim->setDuration(m_animationSpeed);
        anim->setEasingCurve(QEasingCurve::OutQuart);
        anim->setStartValue(w->pos());
        anim->setEndValue(currWidgetNewPos);
        animgroup->addAnimation(anim);
      }
      if ((w = widget(index)) != nullptr) {
        w->setGeometry ( 0,  0, frameWidth, frameHeight );
        w->show();
        w->raise();
        w->move(QPoint {
            m_swipeVertical ? 0 : frameWidth,
            m_swipeVertical ? frameHeight : 0
          });
        anim = new QPropertyAnimation(w, "pos");
        anim->setDuration(m_animationSpeed);
        anim->setEasingCurve(QEasingCurve::OutQuart);
        anim->setStartValue(w->pos());
        anim->setEndValue(nextWidgetNewPos);
        animgroup->addAnimation(anim);
      }
      goingToPage = index;
    } else {
      goingToPage = currentIndex();
    }
    QObject::connect(animgroup, &QParallelAnimationGroup::finished, this, &QSwipeView::onAnimationFinished);
    animgroup->start(QAbstractAnimation::DeleteWhenStopped);
  }
  return rval;
}

bool QSwipeView::gotoPrevPage() {
  return gotoPage(currentIndex() - 1);
}

bool QSwipeView::gotoNextPage() {
  return gotoPage(currentIndex() + 1);
}
