#ifndef EXCHANGEMSGMANAGER_H
#define EXCHANGEMSGMANAGER_H

#include <QString>

class ExchangeMsgManager
{
public:
    static ExchangeMsgManager *getInstance(int nType = 0);
    //客户端发送数据
    int sendMsg(const QString &strContent);

private:
    ExchangeMsgManager(int nType = 0);
    ~ExchangeMsgManager();
    void initServer();
    void initClient();

protected:
    virtual void notify(const QString &strContent);

private:
    void *m_pContext;
    void *m_pSocket;
};

#endif // EXCHANGEMSGMANAGER_H
