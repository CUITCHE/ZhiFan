#include "stdafx.h"
#include "NetServerControl.h"
#include <QTcpSocket>
#include <algorithm>
#include <QMutex>
#include <QTcpServer>
using namespace std;
NetServerControl::NetServerControl(QObject *parent)
	: QObject(parent)
	, serverSocket(new QTcpServer(this))
	, mutex(new QMutex)
{
	doListen();
}

NetServerControl::~NetServerControl()
{
	delete mutex;
}

void NetServerControl::newConnectionProcess()
{
	QTcpSocket *sock = serverSocket->nextPendingConnection();
	connect(sock, &QTcpSocket::readyRead, this, &NetServerControl::pendingRecieveData);
	connect(sock, &QAbstractSocket::disconnected, this, &NetServerControl::onClientSocketDisconnect);
	
	connections.push_back(sock);
}

void NetServerControl::doListen()
{
	auto ins = getInstance(SettingHelper);
	auto ip = ins->getValue("serverIp").toString();
	auto port = ins->getValue("serverPort").toInt();
	bool ret = serverSocket->listen(QHostAddress(ip),port);
	if (ret == false){
		qDebug() << "监听失败";
		__debugbreak();
		return;
	}
	qDebug() << "服务启动成功！！！！！";
	qDebug() << "服务IP地址：" << ip;
	qDebug() << "服务端口：" << port;
	connect(serverSocket, &QTcpServer::newConnection, this, &NetServerControl::newConnectionProcess);
}

void NetServerControl::pendingRecieveData()
{
	QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
	if (sock == nullptr){
		qDebug() << "接收错误的tcp socket sender";
		__debugbreak();
		return;
	}
	auto dataRaw = sock->readAll();
	NetCommunicationModule data{ sock, dataRaw };
	emit taskDataNeed(data);
}

void NetServerControl::removeSocket(QTcpSocket *sock)
{
	connections.removeOne(sock);
}

void NetServerControl::onClientSocketDisconnect()
{
	QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
	if (sock == nullptr){
		qDebug() << "接收错误的tcp socket sender";
		return;
	}
	this->removeSocket(sock);
	sock->deleteLater();
}

bool NetServerControl::isPendingClientData() const
{
	return !sharedDataList.isEmpty();
}

NetCommunicationModule NetServerControl::getPendingData()
{
	QMutexLocker locker(mutex);
	return sharedDataList.takeFirst();
}
