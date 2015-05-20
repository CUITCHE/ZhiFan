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
class Packet;
class QMutex;
class QTcpSocket;
class NetLogicMainProcess;
class Transaction : public QObject
{
	Q_OBJECT

public:
	Transaction(NetLogicMainProcess *parent);
	~Transaction();

	//************************************
	// Method:    lock
	// FullName:  Transaction::lock
	// Access:    public 
	// Returns:   void
	// Qualifier: ������Ҫ�����Packetָ�룬�����������̣����������������
	// Parameter: Packet * pct Ϊ��һ������׼�����������
	// Parameter: QTcpSocket * sock ����sock�������˷���
	//************************************
	void lock(Packet *pct, QTcpSocket *sock);

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
	// Returns:   bool ���Ƿ���true
	// Qualifier: �û���½�߼�����
	//************************************
	bool userLogin();
private:
	Packet *preparePacket;		//��ʱ��
	QTcpSocket *remoteSocket;	//��ʱԶ��socket�׽���
	const NetLogicMainProcess *netLogicMainProcess;
	QMutex *prepareMutex;
};

#endif // TRANSACTION_H
