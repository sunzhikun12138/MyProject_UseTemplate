#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QVariant>
#include <QtSql/QSqlDatabase>
class DatabaseManager
{
public:
    static DatabaseManager* getInstance();
    //添加操作
    bool add(const QString &strSql);
    //更新操作
    bool update(const QString &strSql);
    //删除操作
    bool remove(const QString &strSql);
    //查询操作
    QList<QMap<QString,QVariant>> query(const QString &strSql);
    ~DatabaseManager();
private:
    DatabaseManager();


private:
    QSqlDatabase m_Db;
};

#endif // DATABASEMANAGER_H
