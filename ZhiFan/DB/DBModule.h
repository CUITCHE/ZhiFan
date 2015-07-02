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
#include "Error.h"
#include <QThread>

class ApplaudZhiFanPacket;
class CommentResponsePacket;
class CompleteZhiFanPacket;
class GetOneZhiFanPublishPacket;
class GetZhiFanPublishPageOfRangePacket;
class IdentityPacket;
class LoginPacket;
class PublishZhiFanPacket;
class PullUserCenterPacket;
class RegisterPacket;
class ResponseZhiFanPacket;
class SearchZhiFanPacket;

class ResponseGetOneZhiFanPublishPacket;
class ResponseGetZhiFanPublishPageOfRangePacket;
class ResponseLoginPacket;
class ResponsePullUserCenterPacket;
class ResponseSearchZhiFanPacket;
class ZhiFanPublishBriefOnePacket;
class ZhiFanPublishOnePacket;

class QSqlQuery;
class Range;
typedef QMap<QString, QVariant> QVariantMap;
class QByteArray;

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

	/*
	ע�᣺Register
	mobile��string���ֻ��ţ��ͻ�������׼���
	password��string�����룬MD5
	return: 0�����ɹ���-1�ʺ��Ѵ���
	*/
	int registerUser(const RegisterPacket *packet);

	/*
	��½��Login
	mobile��string���ֻ��ţ��ͻ�������׼���
	password��string�����룬MD5
	ResponseLoginPacket�����ص�½��ɺ���û���Ϣ
	return 0�ɹ���-1ʧ��
	*/
	int loginUser(const LoginPacket *packet, ResponseLoginPacket *&response);

	/*
	ʵ����֤��Identity
	id��int������
	mobile��string���ֻ���
	IDCard��string�����֤�ţ��ͻ���Ҫ�����֤�ŵ�У��
	actname��string�����֤�����Ӧ������
	return 0�ɹ���-1ʧ���ʺŲ�����
	*/
	int identityUser(const IdentityPacket *packet);

	/*
	����֪����PublishZhiFan
	userid��int���û����ݿ�id����
	type��int��0����1Ѱ��
	title��string��64��������
	photo��list��m 5����ͼƬ����
	desc��string�������ı�
	lostType��int�����������ֵ�ɷ���˸��������磺Ǯ�ƣ����ɣ�֤���ȣ��˴���д���Ӧ�����ݿ�����idֵ
	contactPlaceCode��string��64������ϵ�ص㣬�����ݿ��ʡ�е���ֵ��ɣ��ɶ��Ÿ���
	lostDate��date����Ʒ��ʧ���ڣ��磺2014-02-02����һ��QDateֵ
	lostPlaceCodep��int��ʡcode
	lostPlaceCodec��int����code
	lostPlaceCoded��int����code
	lostPlaceDetail��string��128���������������ϸ��ַ
	bills��int�����ͻ���
	return 0�ɹ���-1�û������ڣ�-2����ʧ��
	*/
	int publishZhiFanUser(const PublishZhiFanPacket *packet);

	/*
	�ش�һ��֪����ResponseZhiFan
	userid��int���ش���û�
	publishid��int��ĳ��֪������id
	context��string���û����������
	return�� 0�ɹ���-1�û������ڣ�-2֪�������ڣ�-3�ش�ʧ�ܣ�-4�û���¼ʧ��
	*/
	int responseZhiFanUser(const ResponseZhiFanPacket *packet);

	/*
	����һ���ش�CommentResponse
	responseid��int64���ش��id
	userid��int���������û�id
	referuser��int���ظ����û�id
	context��string���û����۵ķ�������
	return��0�ɹ���-1�û������ڣ�-2���ݿ����ʧ��
			-3��ע�����ʧ��,-4�����������Ļش�
	*/
	int commentResponseUser(const CommentResponsePacket *packet);

	/*
	���֪����CompleteZhiFan���д�������
	publish��int��ĳ��֪���ķ���id
	targetid��int�� ����û�
	type��int����ʲô��ʽ��ɡ�0�ش�1ë���Լ�
	bills��int�����ͻ���
	return 0�ɹ���-1�û�������,-2֪��������
	*/
	int completeZhiFanUser(const CompleteZhiFanPacket *packet);

	/*
	��ͬ�򷴶�֪����һ���ش�ApplaudZhiFan
	userid��int��˭�������ͬ�򷴶�
	responseid��int64���ش��id
	applaudoppose��bool��0��ͬ��1����
	return��0�ɹ���-1�û������ڣ�-2��ͬ�򷴶Բ���ʧ�ܣ� -3�ش𲻴���
			-4�����ظ��˲�����Σ�-5��ͬ��¼�����ʧ��
	*/
	int applaudZhiFanUser(const ApplaudZhiFanPacket *packet);

	/*
	��ȡ֪���������ݣ���Ҫ����GetZhiFanPublishPageOfRange
	userid��int���û�id
	upperLimit��int�������� ]
	lowerLimit��int�������� )
	return 0�ɹ���-1�û������ڣ�-2�����߼�����-3���ݿ��޷���ɷ�ҳ����
	*/
	int getZhiFanPublishPageOfRangeUser(const GetZhiFanPublishPageOfRangePacket *packet, ResponseGetZhiFanPublishPageOfRangePacket *&response);

	/*
	��ȡ֪������ϸ���ݣ���ϸ����GetOneZhiFanPublish
	userid��int���û�id
	publishid��int��֪��id
	return 0�ɹ���-1�û�������
	*/
	int getOneZhiFanPublishUser(const GetOneZhiFanPublishPacket *packet, ResponseGetOneZhiFanPublishPacket *&response);

	/*
	����֪����SearchZhiFan
	userid��int���û�id
	codep��int��ʡcode��Ϊ0��ʾnull����ͬ��
	codec��int����code
	coded��int����code
	keyword��string�������ؼ��֣��������ո�
	upperLimit��int�������� ]
	lowerLimit��int�������� )
	return 0�ɹ���-1�û�������
	*/
	int searchZhiFanUser(const SearchZhiFanPacket *packet, ResponseSearchZhiFanPacket *&response);

	/*
	������ȡ�û��������ͣ�PullUserCenter��
	userid��int���û�id
	type��int��0��ͨϵͳ��Ϣ���ͣ�1����ע��֪�����µĻش�2���Ļش����µ����ۣ�3�����۵Ļش����µ�����
	return 0�ɹ���-1�û�������
	*/
	int pullUserCenterUser(const PullUserCenterPacket *packet);

	/*HTTP�ӿ�*/

	/**
	@brief ������Ϣ
	@param userid �û�id
	@param token token��Ϣ
	@return 0�ɹ���-1�û���֤����
	*/
	int HttpUserInfo(const int userid, const QString &token, QVariantMap &out);

	/**
	@brief ������֤
	@param userid �û�id
	@param token token��Ϣ
	@return 0�ɹ���-1�û���֤����
	*/
	int HttpUserIdentity(const int userid, const QString &token, const QString &name, const QString &idcard, QVariantMap &out);

	/**
	@brief ֪ͨ���ģ�ÿ�η���5����Ϣ�������������Ϣ
	@param userid �û�id
	@param token token��Ϣ
	@param pageNum ��ǰ�ڼ�ҳ��Ϣ
	@return 0�ɹ���-1�û���֤����
	*/
	int HttpUserNoticeCenter(const int userid, const QString &token, int pageNum, QByteArray &out);

protected:
	void briefZhiFanAnalysis(QSqlQuery &query, const Range &range, ResponseGetZhiFanPublishPageOfRangePacket *response_dispatch);
private:
	DBModule(QObject *parent = 0);
	~DBModule();
private:
	SettingInfo *databaseInfo;		//ָ��ָ��SettingHelper�����ݳ�Ա�����ﲻ���ڴ����
};

#endif // DBMODULE_H
