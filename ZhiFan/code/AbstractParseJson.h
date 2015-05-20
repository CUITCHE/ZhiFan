#ifndef ABSTRACTPARSEJSON_H
#define ABSTRACTPARSEJSON_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   15:23
	file base:	AbstractParseJson
	author:		CHE
	
	purpose:	ֻҪ�̳д��࣬������԰��Լ������ݳ�Ա���л���
				�γ�json���У�keyΪ���ݳ�Ա����
*********************************************************************/
#include "defs.h"
#include <QObject>
#include <QJsonDocument>
class AbstractParseJson : public QObject
{
	Q_OBJECT

public:
	AbstractParseJson(QObject *parent = 0);
	virtual ~AbstractParseJson();
	//��QObjectת����QVariant��
	void qobject2qvariant(QVariantMap &variant);

	//��QVariant�洢��QObject���е����ݳ�Ա��ȥ��
	void qvariant2qobject(const QVariantMap &variant);

	//��ȡָ�����ݳ�Ա��property
	QVariant getValue(const char *key) const;

	//����ָ�����ݳ�Ա��property
	void setValue(const char *key, const QVariant &val);

	//�����л�json��������ȡ���ݣ�ʵ��������ĳ�Ա
	void write(const QVariantMap &val);

	//��ȡ���ݳ�Ա�����л�Ϊjson����
	QVariantMap read();
};

#endif // ABSTRACTPASERJSON_H
