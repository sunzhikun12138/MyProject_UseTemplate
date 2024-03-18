#include "UtilityMethod/UtilityMethod.h"
#include <QCoreApplication>
#include <QSettings>

UtilityMethod *UtilityMethod::getInstance()
{
    static UtilityMethod instance;
    return &instance;
}

QVariant UtilityMethod::getAppConfig(const QString &strGroup, const QString &strKey)
{
    QString strFilePath = QCoreApplication::applicationDirPath() + "/../res/app.ini";
    QSettings settings(strFilePath,QSettings::IniFormat);
    settings.beginGroup(strGroup);
    return settings.value(strKey);
}

void UtilityMethod::setAppConfig(const QString &strGroup, const QString &strKey, const QVariant &value)
{
    QString strFilePath = QCoreApplication::applicationDirPath() + "/../res/app.ini";
    QSettings settings(strFilePath,QSettings::IniFormat);
    settings.beginGroup(strGroup);
    settings.setValue(strKey,value);
    settings.endGroup();
}

UtilityMethod::UtilityMethod()
{
}
