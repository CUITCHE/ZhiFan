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
#include <QThread>
using namespace net;
class Error;
class Packet;
class QTcpSocket;
class Transaction;
class NetServerControl;
struct NetCommunicationModule;
typedef QPair<NetCommunicationProtocol, Packet*> AnyPacket;
class NetLogicMainProcess : public QThread
{
	Q_OBJECT

public:
	NetLogicMainProcess(NetServerControl *parent = 0);

	//��������̣߳���δ����������ȴ�2s��֮������δ������ǿ�ƽ���
	~NetLogicMainProcess();

	//ʹactive=true��Ȼ�����QThread��start
	void start();

	//��active=false�����ϲ����wait�������ȴ��߳��˳���֮���ǿ���˳�������terminate
	void stop();

	//��������ͨ�Ŵ���ģ��Ļ״̬��return true if it is active;
	bool isActive()const;

	void write(const Packet *pck, QTcpSocket *sock)const;
protected:
	//��д�̺߳���
	void run();

	//����ͻ��˷���������
	void task(const NetCommunicationModule &NCM);

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
