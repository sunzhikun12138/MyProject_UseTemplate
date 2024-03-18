#include "PluginA.h"
#include <QtDebug>
#include "pugixml.hpp"
#include <fstream>
#include "TinyXml2/tinyxml2.h"
#include <QCoreApplication>
//#include "XT_Logger/XT_Logger.h"
#include "UtilityMethod/UtilityMethod.h"
//#include "DatabaseManager/DatabaseManager.h"

PluginA::PluginA(QObject *parent) :
    QObject(parent)
{
    qDebug()<<QString::fromLocal8Bit("插件A构造函数");
}

QString PluginA::output(const QString &message)
{
    qDebug() << message + QString::fromLocal8Bit("插件A加载成功");
    return message;
}

void PluginA::initialize()
{
    qDebug()<<QString::fromLocal8Bit("插件A初始化函数");
    //read();
    //tinyXml();
    //testUtilityMethod();
//    XT_Logger::getInstance()->setLogFile("./111222333.txt");
//    testDatabase();
}

void PluginA::read()
{
    pugi::xml_document doc;
    if (doc.load_file("111.xml",pugi::parse_default,pugi::encoding_utf8))
    {
        pugi::xml_node root_node = doc.child("Root");
        pugi::xml_node students_node = root_node.child("students");
        // 分别读取每个学生信息
        for (pugi::xml_node student_node = students_node.child("student");
            student_node;
            student_node = student_node.next_sibling("student"))
        {
            pugi::xml_node name_node = student_node.child("name");
            printf("name : %s\n",name_node.first_child().value());
            pugi::xml_node sex_node = student_node.child("sex");
            printf("sex: %s\n",sex_node.first_child().value());
        }
    }
}

void PluginA::tinyXml()
{
//    XT_Logger::getInstance()->logWrite(XT::Warning,QString::fromLocal8Bit("开始解析Xml文件"));
    QString strFileName = QCoreApplication::applicationDirPath() + "/../res/plugins.xml";
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError err = doc.LoadFile(strFileName.toStdString().c_str());
    if(tinyxml2::XML_SUCCESS != err)
    {
        qDebug()<<QString::fromLocal8Bit("xml解析失败:")<<err;
        return;
    }
    tinyxml2::XMLElement *pPluginsEle = doc.FirstChildElement("plugins");
    if(pPluginsEle)
    {
        qDebug()<<"pluginpath:"<<pPluginsEle->Attribute("path");
    }
    tinyxml2::XMLElement *pEle = pPluginsEle->FirstChildElement("plugin");
    while(pEle)
    {
        qDebug()<<"pluginName:"<<pEle->Attribute("name");
        qDebug()<<"visible:"<<pEle->Attribute("visible");
        pEle = pEle->NextSiblingElement("plugin");
    }
}

void PluginA::testUtilityMethod()
{
    qDebug()<<"HostIP:"<<UtilityMethod::getInstance()->getAppConfig("Database","HostIP").toString();
    qDebug()<<"UserName:"<<UtilityMethod::getInstance()->getAppConfig("Database","UserName").toString();
    qDebug()<<"Passwd:"<<UtilityMethod::getInstance()->getAppConfig("Database","PassWd").toString();
    UtilityMethod::getInstance()->setAppConfig("Common","AppName","Frame");
    UtilityMethod::getInstance()->setAppConfig("Database","plugin","2000");
}

void PluginA::testDatabase()
{
//    QString strSql = QString::fromLocal8Bit("insert into T_USER_STUDENT values('777','王五',22);");
//    DatabaseManager::getInstance()->add(strSql);
//    QString strSql = "select * from T_USER_STUDENT;";
//    QList<QMap<QString,QVariant>> res = DatabaseManager::getInstance()->query(strSql);
}
