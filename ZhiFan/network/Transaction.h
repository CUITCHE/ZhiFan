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
#include "FunctionHashTable.h"
#include <QObject>
#include <QMap>
#include <unordered_map>
using namespace net;
using std::unordered_map;
class Packet;
class QTcpSocket;
class NetLogicMainProcess;
class Error;
class Transaction;

typedef void(Transaction::*FunctionType)(void);
typedef QPair<NetCommunicationProtocol, Packet*> AnyPacket;
class Transaction : public QObject
{
	Q_OBJECT

public:
	Transaction(QObject *parent);
	~Transaction();
	unordered_map<NetCommunicationProtocol, FunctionType>& getTransactionMap();
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
	AnyPacket* unlockForResponse();

	//************************************
	// Method:    userLogin
	// FullName:  Transaction::userLogin
	// Access:    public 
	// Returns:   void
	// Qualifier: �û���½�߼�����
	//************************************
	void userLogin();
	

	//************************************
	// Method:    userRegister
	// FullName:  Transaction::userRegister
	// Access:    public 
	// Returns:   void
	// Qualifier: �û�ע��
	//************************************
	void userRegister();

	
	//************************************
	// Method:    userIdentity
	// FullName:  Transaction::userIdentity
	// Access:    public 
	// Returns:   void
	// Qualifier: �û�ʵ����֤
	//************************************
	void userIdentity();


	//************************************
	// Method:    userPublishZhiFan
	// FullName:  Transaction::userPublishZhiFan
	// Access:    public 
	// Returns:   void
	// Qualifier: �û�����֪��
	//************************************
	void userPublishZhiFan();

	//************************************
	// Method:    userResponseZhiFan
	// FullName:  Transaction::userResponseZhiFan
	// Access:    public 
	// Returns:   void
	// Qualifier: �ش�һ��֪��
	//************************************
	void userResponseZhiFan();

	//************************************
	// Method:    userCommentResponse
	// FullName:  Transaction::userCommentResponse
	// Access:    public 
	// Returns:   void
	// Qualifier: ����һ���ش�
	//************************************
	void userCommentResponse();


	//************************************
	// Method:    userCompleteZhiFan
	// FullName:  Transaction::userCompleteZhiFan
	// Access:    public 
	// Returns:   void
	// Qualifier: ���֪��
	//************************************
	void userCompleteZhiFan();

	//************************************
	// Method:    userApplaudZhiFan
	// FullName:  Transaction::userApplaudZhiFan
	// Access:    public 
	// Returns:   void
	// Qualifier: ��ͬ�򷴶�֪����һ���ش�
	//************************************
	void userApplaudZhiFan();

	//************************************
	// Method:    userGetZhiFanPublishPageOfRange
	// FullName:  Transaction::userGetZhiFanPublishPageOfRange
	// Access:    public 
	// Returns:   void
	// Qualifier: ��ȡ֪���������ݣ���Ҫ��
	//************************************
	void userGetZhiFanPublishPageOfRange();

	//************************************
	// Method:    userGetOneZhiFanPublish
	// FullName:  Transaction::userGetOneZhiFanPublish
	// Access:    public 
	// Returns:   void
	// Qualifier:��ȡ֪���������ݣ���ϸ��
	//************************************
	void userGetOneZhiFanPublish();

	//************************************
	// Method:    userSearchZhiFan
	// FullName:  Transaction::userSearchZhiFan
	// Access:    public 
	// Returns:   void
	// Qualifier: ����֪��
	//************************************
	void userSearchZhiFan();
private:
	Packet *preparePacket;		//��ʱ��
	QTcpSocket *remoteSocket;	//��ʱԶ��socket�׽���
	AnyPacket waitPacket;		//���ظ�������
	Error *err;
	static unordered_map<NetCommunicationProtocol, FunctionType> transactionMap;
};

#endif // TRANSACTION_H
