#ifndef HTTPQUERYDATAOBJECT_H
#define HTTPQUERYDATAOBJECT_H
/*!
 * \file HttpQueryDataObject.h
 *
 * \author CHE
 * \date ���� 2015
 *
 * http�����еĲ�ѯ�ַ�����
 */
#include "Packet.h"

class HttpQueryDataObject : public Packet
{
	Q_OBJECT
public:
	HttpQueryDataObject(NetCommunicationProtocol _protocol = Empty, QObject *parent = 0)
		:Packet(_protocol,parent)
	{}
	~HttpQueryDataObject(){}

	QT_MOC_MINE_DEFINITION(QString, userid, Userid);
	QT_MOC_MINE_DEFINITION(QString, token, Token);
};

#endif // HTTPQUERYDATAOBJECT_H
