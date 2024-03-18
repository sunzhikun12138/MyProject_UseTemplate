TEMPLATE        = lib           #表示这个makefile是一个lib的makefile
CONFIG         += plugin        #应用程序是一个插件
TARGET          = PluginA       #生成插件的名称

QT += sql

include (../primary.pri)

HEADERS += \
    PluginA.h

SOURCES += \
    PluginA.cpp \

DISTFILES += \
    programmer.json \

LIBS += \
    -L$$MY_LIBDIR \
    -lTinyXml2 \
#    -lXT_Logger \
    -lUtilityMethod \
#    -lDatabaseManager
