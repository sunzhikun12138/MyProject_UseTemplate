#include "DatabaseManager/DatabaseManager.h"
#include "UtilityMethod/UtilityMethod.h"
//#include "XT_Logger/XT_Logger.h"
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
DatabaseManager *DatabaseManager::getInstance()
{
    static DatabaseManager instance;
    return &instance;
}

bool DatabaseManager::add(const QString &strSql)
{
    QSqlQuery query;
    return query.exec(strSql);
}

bool DatabaseManager::update(const QString &strSql)
{
    QSqlQuery query;
    return query.exec(strSql);
}

bool DatabaseManager::remove(const QString &strSql)
{
    QSqlQuery query;
    return query.exec(strSql);
}

QList<QMap<QString, QVariant>> DatabaseManager::query(const QString &strSql)
{
    QList<QMap<QString, QVariant>> result;
    QSqlQuery query;
    if(!query.exec(strSql))
    {
        return result;
    }
    while(query.next())
    {
        QMap<QString,QVariant> map;
        for (int i = 0; i < query.record().count(); i++)
        {
           QString fieldName = query.record().fieldName(i);
           QVariant value = query.record().value(i);
           map[fieldName] = value;
        }
        result.append(map);
    }
    return result;
}

DatabaseManager::DatabaseManager()
{
    QString strDebug;
    m_Db = QSqlDatabase::addDatabase("QMYSQL");
    QString strHostName = UtilityMethod::getInstance()->getAppConfig("Database","HostIP").toString();
    QString strUserName = UtilityMethod::getInstance()->getAppConfig("Database","UserName").toString();
    QString strPassWd = UtilityMethod::getInstance()->getAppConfig("Database","PassWd").toString();
    QString strDBName = UtilityMethod::getInstance()->getAppConfig("Database","DBName").toString();
    m_Db.setHostName(strHostName);
    m_Db.setDatabaseName(strDBName);
    m_Db.setUserName(strUserName);
    m_Db.setPassword(strPassWd);
    if(!m_Db.open())
    {
        strDebug = "Database open failed!";
//        XT_LOG_WRITE(XT::Error,strDebug);
//        XT_LOG_WRITE(XT::Error,m_Db.lastError().text());
        qDebug()<<strDebug;
        qDebug()<<m_Db.lastError().text();
        return;
    }
    strDebug = "Database open success!";
//    XT_LOG_WRITE(XT::Info,strDebug);
    qDebug()<<strDebug;
}

DatabaseManager::~DatabaseManager()
{
    m_Db.close();
}
