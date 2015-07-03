#ifndef NETLOGICMAINPROCESS_H
#define NETLOGICMAINPROCESS_H
/********************************************************************
	created:	2015/02/22
	created:	22:2:2015   13:22
	file base:	NetLogicMainProcess
	author:		CHE
	
	purpose:	����ͨ�Ŵ���ģ��
				����ͻ��������˵�ͨ���߼���
				����Transaction�ദ��
				[���ڽ������࣬����ֱ��ʹ��delete����]
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
	//����ͻ��˷���������
	void task(NetCommunicationModule &NCM);
protected:

	//���ܻ���ͻ��˷���ServerBack��
	void sendMsgDependsOnError(const Error *err, QTcpSocket *sock);

	//���ܻ���ͻ��˷�������Ҫ������
	void sendDataClientNeeds(AnyPacket *any);
private:
	bool active;	//true��run() is runing,;false run() will be ending.
	bool permit;	//
	NetServerControl *m_socket;
	Transaction *transactionObject;
	AnyPacket *anyPacket = 0;
};

#endif // NETLOGICMAINPROCESS_H
