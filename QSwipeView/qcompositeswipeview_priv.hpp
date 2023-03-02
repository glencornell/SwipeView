#pragma once

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSwipeView>
#include <QPageIndicator>

class QCompositeSwipeView_Priv : public QWidget {
  Q_OBJECT
public:
  explicit QCompositeSwipeView_Priv(QWidget *parent = nullptr);
  ~QCompositeSwipeView_Priv() = default;

  QVBoxLayout *vbox { nullptr };
  QSwipeView *swipeView { nullptr };
  QHBoxLayout *hbox { nullptr };
  QPageIndicator *pageIndicator { nullptr };
};

