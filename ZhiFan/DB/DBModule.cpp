#include "stdafx.h"
#include "DBModule.h"
#include "SettingHelper.h"
#include <QDateTime>
PREPARE_INSTANCE_DEFINITION(DBModule);

DBModule::DBModule(QObject *parent)
	:QThread(parent)
	, databaseInfo(nullptr)
{
}

DBModule::~DBModule()
{

}

void DBModule::initConnect()
{
	//�������ļ��ж�ȡ���ݿ�������Ϣ
	auto ins = getInstance(SettingHelper);
	databaseInfo = const_cast<SettingInfo*>(ins->getSettingInfo());
	QSqlError::ErrorType errorType;
	qDebug() << "****************���ݿ����ģ���ʼ��****************";
	qDebug() << "Ĭ������:";
	qDebug() << "���ݿ��������ַ:" << databaseInfo->getDBServerName();
	qDebug() << "���ݿ�������˿�:" << databaseInfo->getDBServerPort();
	qDebug() << "���ݿ�����:" << databaseInfo->getDBDatabaseName();
	qDebug() << "���ݿ��û���:" << databaseInfo->getDBUserName();
	qDebug() << "���ݿ�����:" << databaseInfo->getDBPassword();
	int trycount = -1;
	do 
	{
		++trycount;
		errorType = MSSQLConnectionHelper::initConnection(*databaseInfo);
		if (trycount > 0){
			qDebug() << "�������ݿ�ʧ��" << trycount + 1 << "�Σ�5�������������......";
			QThread::msleep(5 * 1000);
		}
	} while (errorType != QSqlError::NoError);
}

void DBModule::disconnect()
{
	MSSQLConnectionHelper::closeConnection();
}

void DBModule::reconnect()
{
	disconnect();
	if (databaseInfo == nullptr){
		auto ins = getInstance(SettingHelper);
		databaseInfo = const_cast<SettingInfo*>(ins->getSettingInfo());
	}
	MSSQLConnectionHelper::initConnection(*databaseInfo);
}
