#ifndef TRANSACTION_H
#define TRANSACTION_H
/********************************************************************
	created:	2015/03/19
	created:	19:3:2015   11:51
	file base:	Transaction
	author:		CHE
	
	purpose:	事务处理类
				调用数据库接口，处理服务端与数据库
				处理服务端与客户端的事务逻辑交互。【implement】
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
	// Qualifier: 传入需要处理的Packet指针，进入事务流程，并对事务进行上锁
	// Parameter: Packet * pct 为下一个事务准备请求包内容
	// Parameter: QTcpSocket * sock 来自sock，请求了服务。
	//************************************
	void lock(Packet *pct, QTcpSocket *sock, Error *e);

	//************************************
	// Method:    unlock
	// FullName:  Transaction::unlock
	// Access:    public 
	// Returns:   void
	// Qualifier: 解锁事务，可以进行下一个事务
	//************************************
	void unlock();

	//************************************
	// Method:    userLogin
	// FullName:  Transaction::userLogin
	// Access:    public 
	// Returns:   void
	// Qualifier: 用户登陆逻辑处理
	//************************************
	void userLogin();
private:
	Packet *preparePacket;		//临时包
	QTcpSocket *remoteSocket;	//临时远程socket套接字
	Error *err;
	static FunctionHashTable<NetCommunicationProtocol, FunctionType> transactionMap;
};

#endif // TRANSACTION_H
