#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "PluginInterface/InterfacePlugin.h"
#include "../PluginManager/PluginManager.h"
#include "../PluginManager/PluginInterface.h"
#include "XmlParse/XmlParse.h"
//#include "XT_Logger/XT_Logger.h"
#include "UtilityMethod/UtilityMethod.h"
#include <QDate>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //初始化日志
    QString strFilePath = UtilityMethod::getInstance()->getAppConfig("Common","LogFilePath").toString();
    strFilePath = QCoreApplication::applicationDirPath() + "/" + strFilePath;
    if(strFilePath.endsWith("/"))
    {
        strFilePath = strFilePath + QCoreApplication::applicationName() + QDate::currentDate().toString("yyyyMMdd") + ".log";
    }
    else
    {
        strFilePath = strFilePath + "/" + QCoreApplication::applicationName() + QDate::currentDate().toString("yyyyMMdd") + ".log";
    }
//    XT_Logger::getInstance()->setLogFile(strFilePath);
    //读取plugins.xml文件中配置的需要加载的插件
    QString strDebug;
    PluginsInfoObj stPluginInfo = XmlParse::getInstance()->parsePluginsXml();
    if(!stPluginInfo.bIsEnable)
    {
        strDebug = QString::fromLocal8Bit("无插件加载,退出程序!!!");
//        XT_LOG_WRITE(XT::Debug,strDebug);
        qDebug()<<strDebug;
        return 0;
    }
    //加载所有已经配置过的插件
    QDir path = QDir(qApp->applicationDirPath());
    QString strPluginPath = QCoreApplication::applicationDirPath() + "/" + stPluginInfo.m_strPluginsPath;
    path.cd(strPluginPath);
    foreach (QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
        QString strFileBaseName = info.baseName();
#ifdef __unix
        if(strFileBaseName.startsWith("lib"))
        {
            strFileBaseName = strFileBaseName.mid(3);
        }
#endif
        QString strPluginId = stPluginInfo.m_mapPluginId2Name.key(strFileBaseName,"");
        if(strPluginId == "" || !stPluginInfo.m_mapPluginId2Vis.value(strPluginId))
        {
            continue;
        }
        QPluginLoader pluginLoader(info.absoluteFilePath());
        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
            // 获取元数据（名称、版本、依赖）
            QJsonObject json = pluginLoader.metaData().value("MetaData").toObject();
            qDebug() << "********** MetaData **********";
            qDebug() << json.value("author").toVariant();
            qDebug() << json.value("date").toVariant();
            qDebug() << json.value("name").toVariant();
            qDebug() << json.value("version").toVariant();
            qDebug() << json.value("dependencies").toArray().toVariantList();
            QString strDebug = QString("pluginName:") + json.value("name").toString();
//            XT_LOG_WRITE(XT::Debug,strDebug);
            qDebug()<<strDebug;
            //访问感兴趣的接口
            InterfacePlugin *app = qobject_cast<InterfacePlugin*>(plugin);
            if (app)
            {
                app->initialize();
            }
        }
    }

//    PluginsManager::instance()->loadAllPlugins();//插件管理器 加载所有插件
//    auto plugins=PluginsManager::instance()->allPlugins();
//    foreach(auto plugin,plugins)
//    {
//        PluginInterface *app = qobject_cast<PluginInterface*>(plugin->instance());
//        if (app)
//        {
//            QMap<QString,QVariant> data;
//            data.insert("0001",10000);
//            app->setInitData(data);
//        }
//    }


//    PluginsManager::instance()->unloadAllPlugins();
    return a.exec();
}
