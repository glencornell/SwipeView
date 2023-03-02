#include "qswipeviewplugin.hpp"
#include "qpageindicatorplugin.hpp"
#include "qswipeviewbundleplugin.hpp"

SwipeViewBundlePlugin::SwipeViewBundlePlugin(QObject *parent)
  : QObject(parent)
{
  widgets.append(new QSwipeViewPlugin(this));
  widgets.append(new QPageIndicatorPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> SwipeViewBundlePlugin::customWidgets() const
{
  return widgets;
}
