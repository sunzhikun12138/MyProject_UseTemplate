#include "ExchangeMsgManager/ExchangeMsgManager.h"
#include "zmq/zmq.h"
#include "UtilityMethod/UtilityMethod.h"

ExchangeMsgManager *ExchangeMsgManager::getInstance(int nType)
{
    static ExchangeMsgManager instance(nType);
    return &instance;
}

int ExchangeMsgManager::sendMsg(const QString &strContent)
{
    int nSize;
    zmq_msg_t msg;
    zmq_msg_init_size(&msg, 5);
    memcpy(zmq_msg_data(&msg), strContent.toStdString().c_str(), strlen(strContent.toStdString().c_str()));
    nSize = zmq_msg_send(&msg, m_pSocket, 0);
    zmq_msg_close(&msg);
    return nSize;
}

ExchangeMsgManager::ExchangeMsgManager(int nType)
    :m_pContext(NULL),m_pSocket(NULL)
{
    switch(nType)
    {
    case 0:
        initServer();
        break;
    case 1:
        initClient();
        break;
    }
}

ExchangeMsgManager::~ExchangeMsgManager()
{
    if(m_pSocket)
    {
        zmq_close(m_pSocket);
        m_pSocket = NULL;
    }
    if(m_pContext)
    {
        zmq_ctx_destroy(m_pContext);
        m_pContext = NULL;
    }
}

void ExchangeMsgManager::initServer()
{
    //创建上下文
    m_pContext = zmq_ctx_new();
    //创建、绑定套接字
    m_pSocket = zmq_socket(m_pContext,ZMQ_REP);
    QString strListenUrl = UtilityMethod::getInstance()->getAppConfig("MsgExchange","ListenUrl").toString();
    zmq_bind(m_pSocket,strListenUrl.toStdString().c_str());
    int nSize = 0;
    //循环接收数据
    while(1)
    {
        zmq_msg_t msg;
        zmq_msg_init(&msg);
        nSize = zmq_msg_recv(&msg, m_pSocket, 0);
        if(-1 == nSize) continue;
        QString strContent = QString::fromLocal8Bit((char*)zmq_msg_data(&msg));
        notify(strContent);
        zmq_msg_close(&msg);
    }
}

void ExchangeMsgManager::initClient()
{
    //创建上下文
    m_pContext = zmq_ctx_new();
    //创建套接字、连接服务器
    QString strListenUrl = UtilityMethod::getInstance()->getAppConfig("MsgExchange","ServerUrl").toString();
    m_pSocket = zmq_socket(m_pContext, ZMQ_REQ);
    zmq_connect(m_pSocket, strListenUrl.toStdString().c_str());
}

void ExchangeMsgManager::notify(const QString &strContent)
{

}
