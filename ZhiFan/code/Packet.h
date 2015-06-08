#ifndef PAKCET_H
#define PAKCET_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   15:36
	file base:	Packet
	author:		CHE
	
	purpose:	包类的基础类，需要定义其它包类，需要继承此类
				通过wite() 把数据写入到数据成员
				通过read() 把数据序列化成json
*********************************************************************/
#include "AbstractParseJson.h"
#include "NetCommunicationProtocol.h"
using namespace net;
class QVariant;
class Packet : public AbstractParseJson
{
	Q_OBJECT

	QT_MOC_MINE_DEFINITION(int, protocol, Protocol);
public:
	Packet(NetCommunicationProtocol _protocol = Empty, QObject *parent = 0);
	static int Protocol(const QVariantMap &json);
	virtual ~Packet();
};

#ifdef PACKET_STRUCTION
#undef PACKET_STRUCTION
#endif // PACKET_STRUCTION
#define PACKET_STRUCTION(ProrocolName) \
	public:\
	ProrocolName##Packet(NetCommunicationProtocol _protocol = net::ProrocolName):Packet(_protocol){}\
	~ProrocolName##Packet()override{}

#ifdef PACKET_DEFINITION_BEGIN
#undef PACKET_DEFINITION_BEGIN
#endif
#define PACKET_DEFINITION_BEGIN(ProrocolName)\
	class ProrocolName##Packet :public Packet {

#ifdef PACKET_DEFINITION_END
#undef PACKET_DEFINITION_END
#endif
#define PACKET_DEFINITION_END };
//包类声明Demo
/*
PACKET_DEFINITION_BEGIN(UserLogin)		;用户登陆包类声明起始
Q_OBJECT								;这个是Qt框架的东西，为了能调用和实现整个包类的序列化，必加
PACKET_STRUCTION(UserLogin)				;用户登录包类构造函数，UserLogin这个是来自命名空间net的NetCommunicationProtocol枚举值

QT_MOC_MINE_DEFINITION(QString, mailAddress, MailAddress);		;包类变量声明，依次是：类型，变量名，get-set方法名（详见QT_MOC_MINE_DEFINITION的定义）
QT_MOC_MINE_DEFINITION(QString, password, Password);

PACKET_DEFINITION_END					;用户登录包类声明结束
*/
#endif // PAKCET_H
