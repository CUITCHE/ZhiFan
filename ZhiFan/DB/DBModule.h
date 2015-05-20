#ifndef DBMODULE_H
#define DBMODULE_H
/********************************************************************
	created:	2015/02/19
	created:	19:2:2015   13:01
	file base:	DBModule
	author:		CHE
	
	purpose:	�����ݿ�������ƣ�����prepareģʽ����DBModule��
				��дΪ����������ģʽ����ȡ���˾�̬���ò���
*********************************************************************/
#include "MSSQLConnectionHelper.h"
#include <QThread>
class QDateTime;
class DBModule: QThread
{
	PREPARE_INSTANCE_DECLARE(DBModule)
public:
	//��ʼ�����ݿ�����
	void initConnect();

	//�ر����ݿ�����
	void disconnect();

	//�����������ݿ�
	void reconnect();

	//test function
	void testQuery()const;

	//�ʺ���֤����
	bool accountValidate(const QString &email, const QString &validateCode) const;

	//�û���½
	//result: 0�޴���1�ʺ�δ���2�ʺŻ����벻��
	//ֻ�з���ֵΪfalse��resultֵ��������
	bool userLogin(const QString &email, const QString &pwd, int &result)const;

	//�û�ע��
	bool userReg(const QString &email, const QString &pwd, const QDateTime &timeReg, const QString &whereReg)const;

	//�û��Ƿ����
	bool userExist(const QString &email)const;
private:
	DBModule(QObject *parent = 0);
	~DBModule();
private:
	SettingInfo *databaseInfo;		//ָ��ָ��SettingHelper�����ݳ�Ա�����ﲻ���ڴ����
};

#endif // DBMODULE_H
