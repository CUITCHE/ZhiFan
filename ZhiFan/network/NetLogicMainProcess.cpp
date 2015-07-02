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
NetLogicMainProcess::NetLogicMainProcess(NetServerControl *parent)
	: QThread(parent)
	, m_socket(parent)
	, active(false)
	, permit(false)
	, transactionObject(new Transaction(this))
{
	connect(this, &QThread::finished, this, [&](){active = false; });
}

NetLogicMainProcess::~NetLogicMainProcess()
{
	if (isActive() == false){
		return;
	}
	stop();
}

void NetLogicMainProcess::start()
{
	permit = true;
	QThread::start();
}

void NetLogicMainProcess::stop()
{
	permit = false;
	//等待2s
	bool ret = this->wait(2 * 1000);
	if (ret == false){
		//强制结束
		this->terminate();
	}
}

bool NetLogicMainProcess::isActive() const
{
	return active == true;
}

void NetLogicMainProcess::run()
{
	active = true;
	NetCommunicationModule NCM;
	forever{
		if (permit == false){
			break;
		}
		if (m_socket->isPendingClientData() == false){
			__surrenderconsole__
			continue;
		}
		NCM = m_socket->getPendingData();
		this->task(NCM);
	}
	active = false;
}

void NetLogicMainProcess::task(const NetCommunicationModule &NCM)
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
	pck->write(data);

	//事务开始
	static Error err;
	
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
	auto data = pck->toJson();
	//向远程socket发送数据
	sock->write(data);
}

void NetLogicMainProcess::sendMsgDependsOnError(const Error *err, QTcpSocket *sock)
{
	if (*err == 0){
		return;
	}
	static ServerBackPacket *pck = new ServerBackPacket;
	pck->setMsg(*err);
	this->write(pck, sock);
	//向客户端发送所需数据
	if (anyPacket && anyPacket->first != Empty){
		this->write(anyPacket->second, sock);
		delete anyPacket->second;
		anyPacket = nullptr;
	}
	
}