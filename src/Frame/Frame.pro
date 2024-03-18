QT       += core
QT       -= gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include (../primary.pri)
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

LIBS += \
    -L$$MY_LIBDIR \
    -lPluginManager \
    -lXmlParse  \
#    -lXT_Logger \
    -lTinyXml2  \
    -lUtilityMethod \

SOURCES += \
    main.cpp
