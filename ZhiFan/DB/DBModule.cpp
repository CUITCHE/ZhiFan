#include "stdafx.h"
#include "DBModule.h"
#include "SettingHelper.h"
#include "packets.h"
#include <QDateTime>
#include <QJsonDocument>
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
	//从配置文件中读取数据库的相关信息
	auto ins = getInstance(SettingHelper);
	databaseInfo = const_cast<SettingInfo*>(ins->getSettingInfo());
	QSqlError::ErrorType errorType;
	qDebug() << "****************数据库服务模块初始化****************";
	qDebug() << "默认配置:";
	qDebug() << "数据库服务器地址:" << databaseInfo->getDBServerName();
	qDebug() << "数据库服务器端口:" << databaseInfo->getDBServerPort();
	qDebug() << "数据库名称:" << databaseInfo->getDBDatabaseName();
	qDebug() << "数据库用户名:" << databaseInfo->getDBUserName();
	qDebug() << "数据库密码:" << databaseInfo->getDBPassword();
	int trycount = -1;
	do
	{
		++trycount;
		errorType = MSSQLConnectionHelper::initConnection(*databaseInfo);
		if (trycount > 0){
			qDebug() << "连接数据库失败" << trycount + 1 << "次，5秒后尝试重新连接......";
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
return 0成功，-1用户不存在，-2发布失败
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
return： 0成功，-1用户不存在，-2知返不存在，-3回答失败，-4用户记录失败
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
return：0成功，-1用户不存在，-2数据库插入失败
-3关注表插入失败,-4不存在这样的回答
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
return 0成功，-1用户不存在,-2知返不存在
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
return：0成功，-1用户不存在，-2赞同或反对操作失败， -3回答不存在
-4不能重复此操作多次，-5赞同记录表插入失败
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
return 0成功，-1用户不存在，-2参数逻辑错误，-3数据库无法完成分页操作
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
	//记录数据从数据库返回的范围
	Range rangeq{ range.getLeft(), range.getRight() + briefList.size() };
	bool hasNext = false;
	if (query.nextResult()){
		if (query.next()){
			hasNext = query.value("hasNext").toBool();
		}
	}
	//取得知返被点赞最高的评论，及其内容
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

int DBModule::HttpUserInfo(const int userid, const QString &token, QVariantMap &out)
{
	const static QString sql = "exec httpuserinfo ?,?";
	int error = -777;
	auto query = MSSQLConnectionHelper::execProcedure(sql, userid, token);
	error = query.boundValue("ret").toInt();
	if (query.next()){
		QString vname = query.value("name").toString();
		QString vIDcard = query.value("IDcard").toString();
		bool videntification = query.value("identification").toBool();
		int vzfb = query.value("zfb").toInt();
		QString vaccount = query.value("account").toString();
		out.clear();
		out.insert("username", vname);
		out.insert("gender", vIDcard.size() ? vIDcard.at(5) == 1 : 0);
		out.insert("status", videntification);
		out.insert("gold", vzfb);
		out.insert("mobile", vaccount.left(4) + "***");
	}
	return -1;
}

int DBModule::HttpUserIdentity(const int userid, const QString &token, const QString &name, const QString &idcard, QVariantMap &out)
{
	IdentityPacket * packet = new IdentityPacket;
	packet->setId(userid);
	packet->setMobile(token);//这个作为密码
	packet->setIDCard(idcard);
	packet->setActname(name);
	int ret = this->identityUser(packet);
	out.clear();
	out.insert("status", ret == 0 ? true : false);
	out.insert("msg", ret == 0 ? "验证失败" : "验证成功，请等待审核");
	return ret;
}

int DBModule::HttpUserNoticeCenter(const int userid, const QString &token, int pageNum, QByteArray &out)
{
	int ret = 0;

	QJsonArray array;
	QJsonObject object;
	object.insert("title", "与您欣赏一篇文章");
	object.insert("context", "帝高阳之苗裔兮，朕皇考曰伯庸。\n"
		"摄提贞于孟陬兮，惟庚寅吾以降。\n皇览揆余初度兮，肇锡余以嘉名：\n"
		"名余曰正则兮，字余曰灵均。\n纷吾既有此内美兮，又重之以修能。\n");
	array.append(object);

	QJsonObject ob2;
	ob2.insert("title", "再与您欣赏一篇文章");
	ob2.insert("context", "关关雎鸠，在河之洲。窈窕淑女，君子好逑。\n"
		"参差荇菜，左右流之。窈窕淑女，寤寐求之。\n求之不得，寤寐思服。悠哉悠哉，辗转反侧。\n"
		"参差荇菜，左右采之。窈窕淑女，琴瑟友之。\n参差荇菜，左右芼之。窈窕淑女，钟鼓乐之。\n");

	array.append(ob2);
	

	QJsonDocument json(array);
	out = json.toJson();
	qDebug() << out;
	return ret;
}
