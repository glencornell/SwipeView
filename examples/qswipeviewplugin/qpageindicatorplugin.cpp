#include <QPageIndicator>
#include <QtPlugin>
#include "qpageindicatorplugin.hpp"

QPageIndicatorPlugin::QPageIndicatorPlugin(QObject *parent)
  : QObject(parent)
{
}

void QPageIndicatorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (initialized)
    return;

  initialized = true;
}

bool QPageIndicatorPlugin::isInitialized() const
{
  return initialized;
}

QWidget *QPageIndicatorPlugin::createWidget(QWidget *parent)
{
  return new QPageIndicator(parent);
}

QString QPageIndicatorPlugin::name() const
{
  return { "QPageIndicator" };
}

QString QPageIndicatorPlugin::group() const
{
  return { "Display Widgets" };
}

QIcon QPageIndicatorPlugin::icon() const
{
  return QIcon(":/images/icons8-dots-loading-64.png");
}

QString QPageIndicatorPlugin::toolTip() const
{
  return { "Active page indicator" };
}

QString QPageIndicatorPlugin::whatsThis() const
{
  return { "QPageIndicator indicates the active page in a container of multiple pages." };
}

bool QPageIndicatorPlugin::isContainer() const
{
  return false;
}

QString QPageIndicatorPlugin::domXml() const
{
  return {};
}

QString QPageIndicatorPlugin::includeFile() const
{
  return { "QPageIndicator" };
}
