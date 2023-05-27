#pragma once

#include <QWidget>
#include "qcompositeswipeview_priv.hpp"

class QCompositeSwipeView : public QWidget {
  Q_OBJECT

  // This acts like a QStackedWidget:
  Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentChanged STORED false);
  Q_PROPERTY(int count READ count STORED false);

  // This also acts like a QSwipeView:
  Q_PROPERTY(int animationSpeed READ animationSpeed WRITE animationSpeed STORED false);
  Q_PROPERTY(int swipeVelocity READ swipeVelocity WRITE swipeVelocity STORED false);
  Q_PROPERTY(bool swipeVertical READ swipeVertical WRITE swipeVertical STORED false);
public:
  explicit QCompositeSwipeView(QWidget *parent = nullptr);
  ~QCompositeSwipeView();

  int addWidget(QWidget *child);
  int insertWidget(int index, QWidget *w);
  void removeWidget(QWidget *w);

  QWidget *currentWidget() const;
  int currentIndex() const;

  int indexOf(QWidget *) const;
  QWidget *widget(int) const;
  int count() const;

  void animationSpeed(int animationSpeed_);
  int animationSpeed() const;
  void swipeVelocity(int swipeVelocity_);
  int swipeVelocity() const;
  void swipeVertical(bool swipeVertical_);
  bool swipeVertical() const;

public Q_SLOTS:
  void setCurrentIndex(int index);
  void setCurrentWidget(QWidget *w);

Q_SIGNALS:
  void currentChanged(int);
  void widgetRemoved(int index);

private:
  QCompositeSwipeView_Priv *ui { nullptr };
};
