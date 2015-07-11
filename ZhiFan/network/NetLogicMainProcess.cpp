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
		qDebug() << "�Ƿ�Э��ţ�" << protocol;
	}
	pck->write(data);

	//����ʼ
	static Error err;
	err.opt() = protocol;
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
	QByteArray data = pck->toJson();
	//��Զ��socket��������
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
	//��ͻ��˷�����������
	if (anyPacket && anyPacket->first != Empty){
		this->write(anyPacket->second, sock);
		delete anyPacket->second;
		anyPacket->second = 0;
		anyPacket = nullptr;
	}
	
}