#ifndef PLUGINA_H
#define PLUGINA_H

#include <QObject>
#include <QtPlugin>
#include "PluginInterface/InterfacePlugin.h"

class PluginA : public QObject, public InterfacePlugin
{
    // programmer.json 插件的信息描述类
    Q_OBJECT
    Q_PLUGIN_METADATA(IID InterfacePlugin_iid FILE "programmer.json") // QT5.0 引入
    Q_INTERFACES(InterfacePlugin)
public:
    explicit PluginA(QObject *parent = 0);
    virtual  QString output(const QString &message) Q_DECL_OVERRIDE;
    virtual void initialize();
    void read();
    void tinyXml();
    void testUtilityMethod();
    void testDatabase();
};
#endif // PLUGINA_H
