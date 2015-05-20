#ifndef MSSQLCONNECTIONHELPER_H
#define MSSQLCONNECTIONHELPER_H
/********************************************************************
	created:	2015/02/19
	created:	19:2:2015   12:21
	file base:	MSSQLConnectionHelper
	author:		CHE
	
	purpose:	����odbc���ӵ�MSSQL
				������prepareģʽ�����಻�������ݳ�Ա������prepareģʽ
				������׸
*********************************************************************/
#include "SettingInfo.h"
#include <QtSql/QSql>
#include <QSqlQuery>
#include <QSqlError>

class MSSQLConnectionHelper
{
public:
	MSSQLConnectionHelper() = delete;
	~MSSQLConnectionHelper() = delete;
	//���ӵ����ݿ�
	static QSqlError::ErrorType initConnection(const SettingInfo &info);

	//�Ͽ����ݿ�����
	static void closeConnection();

	//ִ��sql��䲢�����еĽ����
	template<typename... Args>
	static const QSqlQuery execQuery(const QString &execSql, const Args&... args)
	{
		QSqlQuery query;
		query.prepare(execSql);
		execSql_impl(query, args...);
		execQuery(query);
		return query;
	}

	//ִ��sql��䲢�����е�����������Ӱ����������磺select,update,delete,insert��
	template<typename... Args>
	static int execDML(const QString &execSql, const Args&... args)
	{
		QSqlQuery query;
		query.prepare(execSql);
		execSql_impl(query, args...);
		return execDML(query);
	}

	//ִ��sql��䲢���ؽ����������
	template<typename... Args>
	inline static int execScalar(const QString &execSql, const Args&... args)
	{
		QSqlQuery query;
		query.prepare(execSql);
		execSql_impl(query, args...);
		return execScalar(query);
	}
protected:
	//[ģ��] ��sql�����Ӳ���
	static void execSql_impl(QSqlQuery &query){}
	template<typename SqlType, typename... Args>
	static void execSql_impl(QSqlQuery &query, const SqlType &d, const Args& ...args){
		query.addBindValue(d);
		execSql_impl(query, args...);
	}

	//ִ��sql��䲢�����еĽ����
	static void execQuery(QSqlQuery &query);

	//ִ��sql��䲢�����е�����������Ӱ����������磺select,update,delete,insert��
	static int execDML(QSqlQuery &query);

	//ִ��sql��䲢���ؽ����������
	static int execScalar(QSqlQuery &query);

private:
	//��������Ƿ���open״̬��open����true
	static bool checkDB();
};

#endif // MSSQLCONNECTIONHELPER_H
