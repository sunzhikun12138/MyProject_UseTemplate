#include "XT_Logger/XT_Logger.h"
#include <iostream>

XT_Logger *XT_Logger::getInstance()
{
    static XT_Logger instance;
    return &instance;
}

void XT_Logger::setLogFile(const QString &strFilePath)
{
    m_strFileName = strFilePath;
    if(m_pFile)
    {
        m_pFile->close();
        delete m_pFile;
        m_pFile = NULL;
    }
    m_pFile = new QFile(m_strFileName);
    m_pFile->open(QIODevice::Text|QIODevice::WriteOnly|QIODevice::Append);
}

void XT_Logger::logWrite(XT::LevelType level, const QString &strText)
{
    QString strFormatText = QString::fromLocal8Bit("[%1] [%2:%3] [%4]:%5\n")
            .arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)
            .arg(getLevelStrByType(level)).arg(strText);
    m_pFile->write(strFormatText.toLocal8Bit());
    std::cout<<strFormatText.toLocal8Bit().data();
}

XT_Logger::XT_Logger() : m_pFile(NULL)
{
}

XT_Logger::~XT_Logger()
{
    m_pFile->close();
    delete m_pFile;
    m_pFile = NULL;
}

QString XT_Logger::getLevelStrByType(XT::LevelType level)
{
    QString strText = "";
    switch(level)
    {
    case XT::Debug:
        strText = "Debug";
        break;
    case XT::Info:
        strText = "Info";
        break;
    case XT::Warning:
        strText = "Warning";
        break;
    case XT::Error:
        strText = "Error";
        break;
    default:
        strText = "Unkown";
        break;
    }
    return strText;
}
