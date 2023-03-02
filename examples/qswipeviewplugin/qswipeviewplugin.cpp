#include <QSwipeView>
#include <QtPlugin>
#include "qswipeviewplugin.hpp"

QSwipeViewPlugin::QSwipeViewPlugin(QObject *parent)
  : QObject(parent)
{
}

void QSwipeViewPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (initialized)
    return;

  initialized = true;
}

bool QSwipeViewPlugin::isInitialized() const
{
  return initialized;
}

QWidget *QSwipeViewPlugin::createWidget(QWidget *parent)
{
  return new QSwipeView(parent);
}

QString QSwipeViewPlugin::name() const
{
  return { "QSwipeView" };
}

QString QSwipeViewPlugin::group() const
{
  return { "Containers" };
}

QIcon QSwipeViewPlugin::icon() const
{
  return QIcon(":/images/icons8-swipe-64.png");
}

QString QSwipeViewPlugin::toolTip() const
{
  return { "Swipe through stack" };
}

QString QSwipeViewPlugin::whatsThis() const
{
  return { "QSwipeView extends QStackedWidget by allowing one to swipe (up/down, left/right) through the stack." };
}

bool QSwipeViewPlugin::isContainer() const
{
  return true;
}

QString QSwipeViewPlugin::domXml() const
{
  return {};
}

QString QSwipeViewPlugin::includeFile() const
{
  return { "QSwipeView" };
}
