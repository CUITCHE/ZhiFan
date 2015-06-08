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
	AnyPacket* unlockForResponse();

	//************************************
	// Method:    userLogin
	// FullName:  Transaction::userLogin
	// Access:    public 
	// Returns:   void
	// Qualifier: 用户登陆逻辑处理
	//************************************
	void userLogin();
	

	//************************************
	// Method:    userRegister
	// FullName:  Transaction::userRegister
	// Access:    public 
	// Returns:   void
	// Qualifier: 用户注册
	//************************************
	void userRegister();

	
	//************************************
	// Method:    userIdentity
	// FullName:  Transaction::userIdentity
	// Access:    public 
	// Returns:   void
	// Qualifier: 用户实名认证
	//************************************
	void userIdentity();


	//************************************
	// Method:    userPublishZhiFan
	// FullName:  Transaction::userPublishZhiFan
	// Access:    public 
	// Returns:   void
	// Qualifier: 用户发布知返
	//************************************
	void userPublishZhiFan();

	//************************************
	// Method:    userResponseZhiFan
	// FullName:  Transaction::userResponseZhiFan
	// Access:    public 
	// Returns:   void
	// Qualifier: 回答一个知返
	//************************************
	void userResponseZhiFan();

	//************************************
	// Method:    userCommentResponse
	// FullName:  Transaction::userCommentResponse
	// Access:    public 
	// Returns:   void
	// Qualifier: 评论一个回答
	//************************************
	void userCommentResponse();


	//************************************
	// Method:    userCompleteZhiFan
	// FullName:  Transaction::userCompleteZhiFan
	// Access:    public 
	// Returns:   void
	// Qualifier: 完成知返
	//************************************
	void userCompleteZhiFan();

	//************************************
	// Method:    userApplaudZhiFan
	// FullName:  Transaction::userApplaudZhiFan
	// Access:    public 
	// Returns:   void
	// Qualifier: 赞同或反对知返的一个回答
	//************************************
	void userApplaudZhiFan();

	//************************************
	// Method:    userGetZhiFanPublishPageOfRange
	// FullName:  Transaction::userGetZhiFanPublishPageOfRange
	// Access:    public 
	// Returns:   void
	// Qualifier: 获取知返发布内容（扼要）
	//************************************
	void userGetZhiFanPublishPageOfRange();

	//************************************
	// Method:    userGetOneZhiFanPublish
	// FullName:  Transaction::userGetOneZhiFanPublish
	// Access:    public 
	// Returns:   void
	// Qualifier:获取知返发布内容（详细）
	//************************************
	void userGetOneZhiFanPublish();

	//************************************
	// Method:    userSearchZhiFan
	// FullName:  Transaction::userSearchZhiFan
	// Access:    public 
	// Returns:   void
	// Qualifier: 搜索知返
	//************************************
	void userSearchZhiFan();
private:
	Packet *preparePacket;		//临时包
	QTcpSocket *remoteSocket;	//临时远程socket套接字
	AnyPacket waitPacket;		//返回给调用者
	Error *err;
	static unordered_map<NetCommunicationProtocol, FunctionType> transactionMap;
};

#endif // TRANSACTION_H
