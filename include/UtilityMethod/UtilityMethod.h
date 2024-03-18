#ifndef UTILITYMETHOD_H
#define UTILITYMETHOD_H

#include <QVariant>

class UtilityMethod
{
public:
    static UtilityMethod *getInstance();
    QVariant getAppConfig(const QString &strGroup,const QString &strKey);
    void setAppConfig(const QString &strGroup,const QString &strKey,const QVariant &value);
private:
    UtilityMethod();
};

#endif // UTILITYMETHOD_H
