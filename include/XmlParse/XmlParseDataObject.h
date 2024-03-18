#ifndef XMLPARSEDATAOBJECT_H
#define XMLPARSEDATAOBJECT_H
#include <QString>
#include <QMap>
//解析plugins.xml文件
struct PluginsInfoObj
{
    PluginsInfoObj()
    {
        m_strPluginsPath = QString();
        m_nPluginsCnt = 0;
        m_mapPluginId2Name = QMap<QString,QString>();
        m_mapPluginId2Vis = QMap<QString,bool>();
        bIsEnable = false;
    }
    //插件加载dll所在路径
    QString m_strPluginsPath;
    //配置文件中配置插件的个数
    int m_nPluginsCnt;
    //插件名称列表
    QMap<QString,QString> m_mapPluginId2Name;
    //插件是否可见（是否需要加载）
    QMap<QString,bool> m_mapPluginId2Vis;
    //该结构体是否可用
    bool bIsEnable;
};

#endif // XMLPARSEDATAOBJECT_H
