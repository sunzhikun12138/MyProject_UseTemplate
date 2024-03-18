TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    Frame \                 #主程序框架(server/client)
    PluginManager \         #插件管理(server/client)
#    XT_Logger \             #自定义日志库
    TinyXml2 \              #轻量级xml文件解析
    XmlParse \              #自定义xml文件解析库，基于TinyXml2
    PluginA \               #测试插件
#    DatabaseManager \       #数据库管理（增删改查）
    UtilityMethod \         #通用方法
    ExchangeMsgManager  \   #前后端交互库

