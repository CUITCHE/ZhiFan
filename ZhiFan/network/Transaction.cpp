#include "stdafx.h"
#include "Transaction.h"
#include "DBModule.h"
#include "packets.h"
#include "NetLogicMainProcess.h"
#include <QTcpSocket>
#include <QHostAddress>
#define TransMapGenerate(_protocol_) {net::_protocol_, &Transaction::##user##_protocol_}
unordered_map<NetCommunicationProtocol, FunctionType> Transaction::transactionMap = {
	TransMapGenerate(Register),
	TransMapGenerate(Login),
	TransMapGenerate(Identity),
	TransMapGenerate(PublishZhiFan),
	TransMapGenerate(ResponseZhiFan),
	TransMapGenerate(CommentResponse),
	TransMapGenerate(CompleteZhiFan),
	TransMapGenerate(ApplaudZhiFan),
	TransMapGenerate(GetZhiFanPublishPageOfRange),
	TransMapGenerate(GetOneZhiFanPublish),
	TransMapGenerate(SearchZhiFan)
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
	remoteSocket = sock;
	preparePacket = pct;
	err = e;
	
}

AnyPacket* Transaction::unlockForResponse()
{
	preparePacket = nullptr;
	remoteSocket = nullptr;
	err = nullptr;
	return waitPacket.second ? &waitPacket : nullptr;
}

unordered_map<NetCommunicationProtocol, FunctionType>& Transaction::getTransactionMap()
{
	return transactionMap;
}

void Transaction::userLogin()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<LoginPacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	ResponseLoginPacket *response = 0;
	*err = ins->loginUser(pck, response);
	if (*err==0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "��½,�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "��½,ʧ��!";
	}
	waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = response;
}

void Transaction::userRegister()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<RegisterPacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	*err = ins->registerUser(pck);
	if (*err==0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "ע��,�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "ע��,ʧ��!";
	}
	//waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = nullptr;
}

void Transaction::userIdentity()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<IdentityPacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	*err = ins->identityUser(pck);
	if (*err==0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "ʵ����֤,�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "ʵ����֤,ʧ��!";
	}
	//waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = nullptr;
}

void Transaction::userPublishZhiFan()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<PublishZhiFanPacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	*err = ins->publishZhiFanUser(pck);
	if (*err==0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "����֪��,�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "����֪��,ʧ��!";
	}
	//waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = nullptr;
}

void Transaction::userResponseZhiFan()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<ResponseZhiFanPacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	*err = ins->responseZhiFanUser(pck);
	if (*err==0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "�ش�һ��֪��,�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "�ش�һ��֪��,ʧ��!";
	}
	//waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = nullptr;
}

void Transaction::userCommentResponse()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<CommentResponsePacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	*err = ins->commentResponseUser(pck);
	if (*err==0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "����һ���ش�,�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "����һ���ش�,ʧ��!";
	}
	//waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = nullptr;
}

void Transaction::userCompleteZhiFan()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<CompleteZhiFanPacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	*err = ins->completeZhiFanUser(pck);
	if (*err==0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "���֪��,�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "���֪��,ʧ��!";
	}
	//waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = nullptr;
}

void Transaction::userApplaudZhiFan()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<ApplaudZhiFanPacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	*err = ins->applaudZhiFanUser(pck);
	if (*err == 0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< (pck->getApplaudoppose() ? "����" : "��ͬ") << ",�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< (pck->getApplaudoppose() ? "����" : "��ͬ") << ",ʧ��!";
	}
	//waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = nullptr;
}

void Transaction::userGetZhiFanPublishPageOfRange()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<GetZhiFanPublishPageOfRangePacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	ResponseGetZhiFanPublishPageOfRangePacket *response = 0;
	*err = ins->getZhiFanPublishPageOfRangeUser(pck, response);
	if (*err==0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "��ȡ֪���������ݣ���Ҫ��,�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort() 
			<< "��ȡ֪���������ݣ���Ҫ��,ʧ��!";
	}
	waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = response;
}

void Transaction::userGetOneZhiFanPublish()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<GetOneZhiFanPublishPacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	ResponseGetOneZhiFanPublishPacket *response = 0;
	*err = ins->getOneZhiFanPublishUser(pck, response);
	if (*err == 0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort()
			<< "��ȡ֪���������ݣ���ϸ��,�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort()
			<< "��ȡ֪���������ݣ���ϸ��,ʧ��!";
	}
	waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = response;
}

void Transaction::userSearchZhiFan()
{
	if (!preparePacket){
		return;
	}
	auto pck = dynamic_cast<SearchZhiFanPacket*>(preparePacket);
	auto ins = getInstance(DBModule);
	ResponseSearchZhiFanPacket *response = 0;
	*err = ins->searchZhiFanUser(pck, response);
	if (*err == 0){
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort()
			<< "����֪��,�ɹ�!";
	}
	else{
		qDebug() << remoteSocket->localAddress().toString() << ":" << remoteSocket->localPort()
			<< "����֪��,ʧ��!";
	}
	waitPacket.first = protocol_cast(preparePacket->getProtocol());
	waitPacket.second = response;
}


