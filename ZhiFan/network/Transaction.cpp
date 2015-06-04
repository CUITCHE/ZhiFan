#include "stdafx.h"
#include "Transaction.h"
#include "DBModule.h"
#include "packets.h"
#include "NetLogicMainProcess.h"
#include <QTcpSocket>
#define TransMapGenerate(_protocol_) {net::_protocol_, &Transaction::##user##_protocol_}
FunctionHashTable<NetCommunicationProtocol, FunctionType> Transaction::transactionMap = {
	TransMapGenerate(Login)
};
#undef TransMapGenerate
Transaction::Transaction(QObject *parent)
	: QObject(parent->parent())
	, preparePacket(nullptr)
	, remoteSocket(nullptr)
{

}

Transaction::~Transaction()
{

}

void Transaction::lock(Packet *pct, QTcpSocket *sock, Error *e)
{

	///从代码级别上保证preparePacket的唯一性【debug】
	Q_ASSERT(preparePacket == nullptr && remoteSocket == nullptr);
	remoteSocket = sock;
	preparePacket = pct;
	err = e;
}

void Transaction::unlock()
{
	preparePacket = nullptr;
	remoteSocket = nullptr;
	err = nullptr;
}

void Transaction::userLogin()
{
	
}

FunctionHashTable<NetCommunicationProtocol, FunctionType>& Transaction::getTransactionMap()
{
	return transactionMap;
}
