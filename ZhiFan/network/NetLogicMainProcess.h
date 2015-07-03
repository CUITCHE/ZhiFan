#ifndef NETLOGICMAINPROCESS_H
#define NETLOGICMAINPROCESS_H
/********************************************************************
	created:	2015/02/22
	created:	22:2:2015   13:22
	file base:	NetLogicMainProcess
	author:		CHE
	
	purpose:	网络通信处理模块
				处理客户端与服务端的通信逻辑，
				调用Transaction类处理
				[关于结束本类，建议直接使用delete操作]
*********************************************************************/
#include "NetCommunicationProtocol.h"
#include <QObject>
using namespace net;
class Error;
class Packet;
class QTcpSocket;
class Transaction;
class NetServerControl;
struct NetCommunicationModule;
typedef QPair<NetCommunicationProtocol, Packet*> AnyPacket;
class NetLogicMainProcess : public QObject
{
	Q_OBJECT

public:
	NetLogicMainProcess(NetServerControl *parent = 0);

	~NetLogicMainProcess();

	void write(const Packet *pck, QTcpSocket *sock)const;
protected slots:
	//处理客户端发来的数据
	void task(NetCommunicationModule &NCM);
protected:

	//可能会向客户端发送ServerBack包
	void sendMsgDependsOnError(const Error *err, QTcpSocket *sock);

	//可能会向客户端发送所需要的数据
	void sendDataClientNeeds(AnyPacket *any);
private:
	bool active;	//true，run() is runing,;false run() will be ending.
	bool permit;	//
	NetServerControl *m_socket;
	Transaction *transactionObject;
	AnyPacket *anyPacket = 0;
};

#endif // NETLOGICMAINPROCESS_H
