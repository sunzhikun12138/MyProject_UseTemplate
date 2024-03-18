#include "XmlParse/XmlParse.h"
#include "TinyXml2/tinyxml2.h"
//#include "XT_Logger/XT_Logger.h"
#include <QCoreApplication>
#include <QDebug>
using namespace tinyxml2;

XmlParse *XmlParse::getInstance()
{
    static XmlParse instance;
    return &instance;
}

PluginsInfoObj XmlParse::parsePluginsXml()
{
    PluginsInfoObj infoObj;
    QString strFileName = QCoreApplication::applicationDirPath() + "/../res/plugins.xml";
    XMLDocument doc;
    QString strDebug;
    XMLError err = doc.LoadFile(strFileName.toStdString().c_str());
    if(XML_SUCCESS != err)
    {
        strDebug = QString::fromLocal8Bit("xml解析失败:") + XMLDocument::ErrorIDToName(err);
//        XT_LOG_WRITE(XT::Warning,strDebug);
        qDebug()<<strDebug;
        return infoObj;
    }
    infoObj.bIsEnable = true;
    XMLElement *pPluginsEle = doc.FirstChildElement("plugins");
    if(pPluginsEle)
    {
        infoObj.m_strPluginsPath = pPluginsEle->Attribute("path");
    }
    XMLElement *pEle = pPluginsEle->FirstChildElement("plugin");
    while(pEle)
    {
        QString strId = pEle->Attribute("id");
        infoObj.m_nPluginsCnt++;
        infoObj.m_mapPluginId2Name.insert(strId,pEle->Attribute("name"));
        bool bIsVis = QString::fromLocal8Bit(pEle->Attribute("visible")) != QString::fromLocal8Bit("0");
        infoObj.m_mapPluginId2Vis.insert(strId,bIsVis);
        pEle = pEle->NextSiblingElement("plugin");
    }
    return infoObj;
}

XmlParse::XmlParse()
{
}
