#include "stdafx.h"
#include "DBModule.h"
#include "SettingHelper.h"
#include "packets.h"
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

int DBModule::registerUser(const RegisterPacket *packet)
{
	const static QString sql = "exec spregister ?,?,?";
	int error = -777;
	auto ret = MSSQLConnectionHelper::execProcedure(sql, packet->getMobile(), packet->getPassword());
	
	error = ret.boundValue("ret").toInt();
	return error;
}

int DBModule::loginUser(const LoginPacket *packet, ResponseLoginPacket *&response)
{
	const static QString sql = "exec splogin ?,?,?";
	int error = -777;
	auto ret = MSSQLConnectionHelper::execProcedure(sql, packet->getMobile(), packet->getPassword());
	error = ret.boundValue("ret").toInt();

	if (ret.next()){
		bool videntity = ret.value("identification").toBool();
		QString vidcard = ret.value("IDcard").toString();
		int vzfb = ret.value("zfb").toInt();
		int vuserid = ret.value("id").toInt();
		response = new ResponseLoginPacket;
		response->setIdentification(videntity);
		response->setIDCardSubstring(vidcard);
		response->setZfb(vzfb);
		response->setUserid(vuserid);
	}
	return error;
}

int DBModule::identityUser(const IdentityPacket *packet)
{
	const static QString sql = "exec spidentify ?,?,?,?,?";
	int error = -777;
	auto ret = MSSQLConnectionHelper::execProcedure(sql, packet->getId(), packet->getMobile(),
		packet->getIDCard(), packet->getActname());
	error = ret.boundValue("ret").toInt();

	return error;
}
/*
return 0�ɹ���-1�û������ڣ�-2����ʧ��
*/
int DBModule::publishZhiFanUser(const PublishZhiFanPacket *packet)
{
	const static QString sql = "exec sppublishzhifan ?,?,?,?,?,?,?,?,?,?,?,?,?,?";
	int error = -777;
	auto query = MSSQLConnectionHelper::execProcedure(sql, packet->getUserid(), packet->getType(), packet->getTitle(),
		packet->getPhoto(), packet->getDesc(), packet->getLostType(), packet->getContactPlaceCode(), packet->getLostDate(),
		packet->getLostPlaceCodep(), packet->getLostPlaceCodec(), packet->getLostPlaceCoded(), packet->getLostPlaceDetail(),
		packet->getBills());
	error = query.boundValue("ret").toInt();

	return error;
}
/*
return�� 0�ɹ���-1�û������ڣ�-2֪�������ڣ�-3�ش�ʧ�ܣ�-4�û���¼ʧ��
*/
int DBModule::responseZhiFanUser(const ResponseZhiFanPacket *packet)
{
	const static QString sql = "exec spresponsezhifan ?,?,?,?";
	int error = -777;
	auto query = MSSQLConnectionHelper::execProcedure(sql, packet->getUserid(), packet->getPublishid(), packet->getContext());
	error = query.boundValue("ret").toInt();

	return error;
}
/*
return��0�ɹ���-1�û������ڣ�-2���ݿ����ʧ��
-3��ע�����ʧ��,-4�����������Ļش�
*/
int DBModule::commentResponseUser(const CommentResponsePacket *packet)
{
	const static QString sql = "exec spresponsezhifan ?,?,?,?,?";
	int error = -777;
	auto query = MSSQLConnectionHelper::execProcedure(sql, packet->getResponseid(), packet->getUserid(),
		packet->getReferuser(), packet->getContext());
	error = query.boundValue("ret").toInt();

	return error;
}
/*
return 0�ɹ���-1�û�������,-2֪��������
*/
int DBModule::completeZhiFanUser(const CompleteZhiFanPacket *packet)
{
	const static QString sql = "exec spcomplete ?,?,?,?,?";
	int error = -777;
	auto query = MSSQLConnectionHelper::execProcedure(sql, packet->getPublish(), packet->getTargeted(),
		packet->getType(), packet->getBills());
	error = query.boundValue("ret").toInt();

	return error;
}
/*
return��0�ɹ���-1�û������ڣ�-2��ͬ�򷴶Բ���ʧ�ܣ� -3�ش𲻴���
-4�����ظ��˲�����Σ�-5��ͬ��¼�����ʧ��
*/
int DBModule::applaudZhiFanUser(const ApplaudZhiFanPacket *packet)
{
	const static QString sql = "exec spapplaudzhifan ?,?,?,?";
	int error = -777;
	auto query = MSSQLConnectionHelper::execProcedure(sql, packet->getResponseid(), packet->getUserid(),
		packet->getApplaudoppose());
	error = query.boundValue("ret").toInt();

	return error;
}
/*
return 0�ɹ���-1�û������ڣ�-2�����߼�����-3���ݿ��޷���ɷ�ҳ����
*/
int DBModule::getZhiFanPublishPageOfRangeUser(const GetZhiFanPublishPageOfRangePacket *packet, ResponseGetZhiFanPublishPageOfRangePacket *&response)
{
	const static QString sql = "exec spbriefpublishpageofrange ?,?,?,?";
	int error = -777;

	auto query = MSSQLConnectionHelper::execProcedure(sql, packet->getUserid(), packet->getUpperLimit(),
		packet->getLowerLimit());
	error = query.boundValue("ret").toInt();

	if (error != 0){
		return error;
	}
	response = new ResponseGetZhiFanPublishPageOfRangePacket;
	briefZhiFanAnalysis(query, { packet->getUpperLimit(), packet->getLowerLimit() }, response);
	return error;
}

int DBModule::getOneZhiFanPublishUser(const GetOneZhiFanPublishPacket *packet, ResponseGetOneZhiFanPublishPacket *&response)
{
	const static QString sql = "exec sponezhifanpublish ?,?,?";
	int error = -777;
	auto query = MSSQLConnectionHelper::execProcedure(sql, packet->getUserid(), packet->getPublishid());
	error = query.boundValue("ret").toInt();
	if (query.next()){
		QDateTime vpublishDate = query.value("publishdate").toDateTime();
		int vlostType = query.value("losttype").toInt();
		QDate vlostDate = query.value("lostdate").toDate();
		int vlostplacecodep = query.value("lostplacecodep").toInt();
		int vlostplacecodec = query.value("lostplacecodec").toInt();
		int vlostplacecoded = query.value("lostplacecoded").toInt();
		QString vlostplacedetail = query.value("lostplacedetail").toString();
		int vbills = query.value("bills").toInt();
		response = new ResponseGetOneZhiFanPublishPacket;
		response->setPublishdate(vpublishDate);
		response->setLostType(vlostType);
		response->setLostDate(vlostDate);
		response->setLostPlaceCodep(vlostplacecodep);
		response->setLostPlaceCodec(vlostplacecodec);
		response->setLostPlaceCoded(vlostplacecoded);
		response->setLostPlacedetail(vlostplacedetail);
		response->setBills(vbills);
	}

	return error;
}

int DBModule::searchZhiFanUser(const SearchZhiFanPacket *packet, ResponseSearchZhiFanPacket *&response)
{
	const static QString sql = "exec spsearchzhifan ?,?,?,?,?,?,?,?";
	int error = -777;
	auto query = MSSQLConnectionHelper::execProcedure(sql, packet->getUserid(), packet->getCodep(), packet->getCodec(),
		packet->getCoded(), packet->getKeyword(), packet->getUpperLimit(), packet->getLowerLimit());
	
	response = new ResponseSearchZhiFanPacket;
	briefZhiFanAnalysis(query, { packet->getUpperLimit(), packet->getLowerLimit() }, response);

	return error;
}

void DBModule::briefZhiFanAnalysis(QSqlQuery &query, const Range &range, ResponseGetZhiFanPublishPageOfRangePacket *response_dispatch)
{
	static ZhiFanPublishBriefOnePacket tmpPtr;
	QList<ZhiFanPublishBriefOnePacket> briefList;
	while (query.next()){
		int vid = query.value("id").toInt();
		int vowner = query.value("owner").toInt();
		QString vtitle = query.value("title").toString();
		QString vphoto = query.value("photo").toString();
		bool vlightEyes = query.value("lighteyes").toBool();
		QDateTime vtop = query.value("top").toDateTime();
		QString vdesc = query.value("desc").toString();
		bool vtype = query.value("type").toBool();
		QList<QVariant> photolist;
		{
			auto _list = vphoto.split(',');
			QStringList::iterator iter = _list.begin() - 1;
			QStringList::iterator end = _list.end();
			while (++iter != end){
				photolist.push_back(*iter);
			}
		}
		tmpPtr.setPublishId(vid);
		tmpPtr.setOwnerId(vowner);
		tmpPtr.setTitle(vtitle);
		tmpPtr.setPhoto(photolist);
		tmpPtr.setLightEyes(vlightEyes);
		tmpPtr.setTopTime(vtop);
		tmpPtr.setBriefDesc(vdesc);
		tmpPtr.setType(vtype);

		briefList.push_back(tmpPtr);
	}
	//��¼���ݴ����ݿⷵ�صķ�Χ
	Range rangeq{ range.getLeft(), range.getRight() + briefList.size() };
	bool hasNext = false;
	if (query.nextResult()){
		if (query.next()){
			hasNext = query.value("hasNext").toBool();
		}
	}
	//ȡ��֪����������ߵ����ۣ���������
	if (briefList.size() > 0){
		const static QString sql = "exec spmaxofresponse ?,?,?";
		int error = -777;
		QList<ZhiFanPublishBriefOnePacket>::iterator iter = briefList.begin() - 1,
			end = briefList.end();
		while (++iter != end){
			auto query = MSSQLConnectionHelper::execProcedure(sql, iter->getPublishId(), 0);
			iter->setResponseNum(0);
			iter->setResposneApplaudNum(0);
			if (query.next()){
				int vtatol = query.value("total").toInt();
				int vappluad = query.value("applaudnum").toInt();
				QString vcontext = query.value("context").toString();
				iter->setResponseNum(vtatol);
				iter->setResposneApplaudNum(vappluad);
				iter->setResponseInfo(vcontext);
			}
		}
	}
	response_dispatch->setPublishList(briefList);
	response_dispatch->setRange(rangeq);
	response_dispatch->setHasNext(hasNext);
}
