#ifndef DBMODULE_H
#define DBMODULE_H
/********************************************************************
	created:	2015/02/19
	created:	19:2:2015   13:01
	file base:	DBModule
	author:		CHE
	
	purpose:	对数据库操作控制，利用prepare模式。把DBModule类
				改写为面向对象的类模式，而取消了静态调用操作
*********************************************************************/
#include "MSSQLConnectionHelper.h"
#include "Error.h"
#include <QThread>
class QDateTime;
class DBModule: QThread
{
	PREPARE_INSTANCE_DECLARE(DBModule)
public:
	//初始化数据库连接
	void initConnect();

	//关闭数据库连接
	void disconnect();

	//重新连接数据库
	void reconnect();

	/*
	注册：Register
	mobile：string：手机号，客户端作标准检查
	password：string：密码，MD5
	*/
	int registerUser(const QString &mobile, const QString &password);
private:
	DBModule(QObject *parent = 0);
	~DBModule();
private:
	SettingInfo *databaseInfo;		//指针指向SettingHelper的数据成员，这里不做内存管理
};

#endif // DBMODULE_H
