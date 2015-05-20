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
			qDebug() << "�������ݿ�ʧ��" << trycount << "�Σ�5�������������......";
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
		auto ins = ___get<SettingHelper>();
		databaseInfo = const_cast<SettingInfo*>(ins->getSettingInfo());
	}
	MSSQLConnectionHelper::initConnection(*databaseInfo);
}

void DBModule::testQuery() const
{
	QString sql = "insert into ytalk_user(mailAddress,password) values('dsfew',43231243)";
	MSSQLConnectionHelper::execDML(sql);
}

bool DBModule::accountValidate(const QString &email, const QString &validateCode) const
{
	//֮����ܻ���������md5ֵ���ж�
	QDateTime curTime = QDateTime::currentDateTime();
	auto ret = MSSQLConnectionHelper::execQuery("select identifydate from ytalk_user where mailAddress = ? AND identifycode = ?",email, validateCode);
	if (!ret.next()){
		return false;
	}
	auto date = ret.value("identifydate").toDateTime();
	if (curTime < date){
		return true;
	}
	return false;
}

bool DBModule::userLogin(const QString &email, const QString &pwd, int &result) const
{
	auto ret = MSSQLConnectionHelper::execQuery("select active from ytalk_user where mailAddress = ? AND password = ?", email, pwd);
	result = 0;
	if (!ret.next()){
		result = 2;
		return false;
	}
	bool active = ret.value("active").toBool();
	if (active == false){
		result = 1;
		return false;
	}
	return true;
}

bool DBModule::userReg(const QString &email, const QString &pwd, const QDateTime &timeReg, const QString &whereReg) const
{
	if (userExist(email) == false){
		return false;
	}
	auto ret = MSSQLConnectionHelper::execDML("insert into ytalk_user(mailAddress,password,registerDate,registerWhere) values(?,?,?,?)",
		email, pwd, timeReg, whereReg);

	return ret == 1 ? true : false;
}

bool DBModule::userExist(const QString &email) const
{
	QString sql = QString().arg(email);
	auto ret = MSSQLConnectionHelper::execDML("select id from ytalk_user where mailAddress = ?", email);

	return ret == 1 ? true : false;
}
