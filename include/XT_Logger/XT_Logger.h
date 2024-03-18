#ifndef XT_LOGGER_H
#define XT_LOGGER_H
#include <QString>
#include <QFile>

#define XT_LOG_WRITE(level,text)  XT_Logger::getInstance()->logWrite(level,text);
namespace XT {
    enum LevelType
    {
        Debug,
        Info,
        Warning,
        Error
    };
}

class XT_Logger
{
public:
    static XT_Logger *getInstance();
    void setLogFile(const QString &strFilePath);
    void logWrite(XT::LevelType level,const QString &strText);
private:
    explicit XT_Logger();
    ~XT_Logger();
    QString getLevelStrByType(XT::LevelType level);

private:
    QFile *m_pFile;
    QString m_strFileName;
};

#endif // XT_LOGGER_H
