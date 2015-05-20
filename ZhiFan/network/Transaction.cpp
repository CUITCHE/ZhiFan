#include "stdafx.h"
#include "Transaction.h"
#include "DBModule.h"
#include "packets.h"
#include "NetLogicMainProcess.h"
#include <QMutex>
#include <QTcpSocket>
Transaction::Transaction(NetLogicMainProcess *parent)
	: QObject(parent->parent())
	, preparePacket(nullptr)
	, remoteSocket(nullptr)
	, prepareMutex(new QMutex)
	, netLogicMainProcess(parent)
{

}

Transaction::~Transaction()
{

}

void Transaction::lock(Packet *pct, QTcpSocket *sock)
{
	prepareMutex->lock();
	///�Ӵ��뼶���ϱ�֤preparePacket��Ψһ�ԡ�debug��
	Q_ASSERT(preparePacket == nullptr && remoteSocket == nullptr);
	remoteSocket = sock;
	preparePacket = pct;
}

void Transaction::unlock()
{
	preparePacket = nullptr;
	remoteSocket = nullptr;
	prepareMutex->unlock();
}

bool Transaction::userLogin()
{
	auto pck = dynamic_cast<UserLoginPacket *>(preparePacket);
	QString mail = pck->getMailAddress();
	QString pwd = pck->getPassword();
	auto d = getInstance(DBModule);
	int result = 0;
	bool ret = d->userLogin(mail, pwd, result);
	ServerBackPacket *pck2 = new ServerBackPacket;
	pck2->setOperator(pck->getProtocol());
	if (ret == false){
		pck2->setResult(result);
		switch (result)
		{
		case 1:
			pck2->setReason("�����ʺ���δ����");
			break;
		case 2:
			pck2->setReason("�ʺŻ��������");
			break;
		}
	}
	else {
		pck2->setResult(0);
	}
	netLogicMainProcess->write(pck2, remoteSocket);
	return true;
}
