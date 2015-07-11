#include "stdafx.h"
#include "NetLogicMainProcess.h"
#include "defs.h"
#include "Packet.h"
#include "Transaction.h"
#include "NetServerControl.h"
#include "InstantiationPacketHelper.h"
#include "Error.h"
#include "ServerBackPacket.h"
#include <QTcpSocket>
#include <thread>
NetLogicMainProcess::NetLogicMainProcess(NetServerControl *parent)
	: QObject(parent)
	, m_socket(parent)
	, active(false)
	, permit(false)
	, transactionObject(new Transaction(this))
{
	connect(m_socket, &NetServerControl::taskDataNeed, this, &NetLogicMainProcess::task);
}

NetLogicMainProcess::~NetLogicMainProcess()
{
}

void NetLogicMainProcess::task(NetCommunicationModule &NCM)
{
	QTcpSocket *sock = NCM.sock;
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(NCM.data, &error);
	if (error.error != QJsonParseError::NoError){
		qDebug() << "json parse error! in" << __FUNCSIG__;
		qDebug() << "data of recieving is :\"" << NCM.data << "\"";
		return;
	}
	QVariantMap data = jsonDocument.toVariant().toMap();
	int protocol = Packet::Protocol(data);
	auto pck = net::get(protocol);
	if (!pck){
		qDebug() << "非法协议号：" << protocol;
	}
	pck->write(data);

	//事务开始
	static Error err;
	err.opt() = protocol;
	transactionObject->lock(pck, sock, &err);
	try{
		(transactionObject->*transactionObject->getTransactionMap()[(NetCommunicationProtocol)protocol])();
	}
	catch (...){
		qDebug() << "事务出现错误！协议号：" << protocol << "协议语言：" << net::ProtocolToString(protocol);
		return;
	}
	//事务结束
	anyPacket = transactionObject->unlockForResponse();

	//处理Error，发送ServerBackPacket AND 客户端需要的数据
	this->sendMsgDependsOnError(&err, sock);
}

void NetLogicMainProcess::write(const Packet *pck, QTcpSocket *sock) const
{
	QByteArray data = pck->toJson();
	//向远程socket发送数据
	int index = 0;

	sock->write(data);
}

void NetLogicMainProcess::sendMsgDependsOnError(const Error *err, QTcpSocket *sock)
{
	static ServerBackPacket *pck = new ServerBackPacket;
	pck->setMsg(*err);
	pck->setOperator(err->opt());
	pck->setStatus(*err);
	this->write(pck, sock);
	//向客户端发送所需数据
	if (anyPacket && anyPacket->first != Empty){
		this->write(anyPacket->second, sock);
		delete anyPacket->second;
		anyPacket->second = 0;
		anyPacket = nullptr;
	}
	
}