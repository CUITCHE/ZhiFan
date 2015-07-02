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
	//�ȴ�2s
	bool ret = this->wait(2 * 1000);
	if (ret == false){
		//ǿ�ƽ���
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

	//����ʼ
	static Error err;
	
	transactionObject->lock(pck, sock, &err);
	try{
		(transactionObject->*transactionObject->getTransactionMap()[(NetCommunicationProtocol)protocol])();
	}
	catch (...){
		qDebug() << "������ִ���Э��ţ�" << protocol << "Э�����ԣ�" << net::ProtocolToString(protocol);
		return;
	}
	//�������
	anyPacket = transactionObject->unlockForResponse();

	//����Error������ServerBackPacket AND �ͻ�����Ҫ������
	this->sendMsgDependsOnError(&err, sock);
}

void NetLogicMainProcess::write(const Packet *pck, QTcpSocket *sock) const
{
	auto data = pck->toJson();
	//��Զ��socket��������
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
	//��ͻ��˷�����������
	if (anyPacket && anyPacket->first != Empty){
		this->write(anyPacket->second, sock);
		delete anyPacket->second;
		anyPacket = nullptr;
	}
	
}