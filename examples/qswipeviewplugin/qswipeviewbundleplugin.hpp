#pragma once

#include <QtDesigner/QDesignerCustomWidgetCollectionInterface>
#include <QtCore/QObject>

class SwipeViewBundlePlugin : public QObject, public QDesignerCustomWidgetCollectionInterface
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface");
  Q_INTERFACES( QDesignerCustomWidgetCollectionInterface );
public:
  explicit MyWidgetDesignerFactoryCollection( QObject* parent = 0 );

  QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
  QList<QDesignerCustomWidgetInterface*> widgets;
};
