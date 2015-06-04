#ifndef TRANSACTION_H
#define TRANSACTION_H
/********************************************************************
	created:	2015/03/19
	created:	19:3:2015   11:51
	file base:	Transaction
	author:		CHE
	
	purpose:	��������
				�������ݿ�ӿڣ��������������ݿ�
				����������ͻ��˵������߼���������implement��
*********************************************************************/
#include <QObject>
#include <QMap>
#include "FunctionHashTable.h"
using namespace net;
class Packet;
class QTcpSocket;
class NetLogicMainProcess;
class Error;
class Transaction;

typedef void(Transaction::*FunctionType)(void);
class Transaction : public QObject
{
	Q_OBJECT

public:
	Transaction(QObject *parent);
	~Transaction();
	FunctionHashTable<NetCommunicationProtocol, FunctionType>& getTransactionMap();
	//************************************
	// Method:    lock
	// FullName:  Transaction::lock
	// Access:    public 
	// Returns:   void
	// Qualifier: ������Ҫ�����Packetָ�룬�����������̣����������������
	// Parameter: Packet * pct Ϊ��һ������׼�����������
	// Parameter: QTcpSocket * sock ����sock�������˷���
	//************************************
	void lock(Packet *pct, QTcpSocket *sock, Error *e);

	//************************************
	// Method:    unlock
	// FullName:  Transaction::unlock
	// Access:    public 
	// Returns:   void
	// Qualifier: �������񣬿��Խ�����һ������
	//************************************
	void unlock();

	//************************************
	// Method:    userLogin
	// FullName:  Transaction::userLogin
	// Access:    public 
	// Returns:   void
	// Qualifier: �û���½�߼�����
	//************************************
	void userLogin();
private:
	Packet *preparePacket;		//��ʱ��
	QTcpSocket *remoteSocket;	//��ʱԶ��socket�׽���
	Error *err;
	static FunctionHashTable<NetCommunicationProtocol, FunctionType> transactionMap;
};

#endif // TRANSACTION_H
