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
	return: 0创建成功，-1帐号已存在
	*/
	int registerUser(const RegisterPacket *packet);

	/*
	登陆：Login
	mobile：string：手机号，客户端作标准检查
	password：string：密码，MD5
	ResponseLoginPacket：返回登陆完成后的用户信息
	return 0成功，-1失败
	*/
	int loginUser(const LoginPacket *packet, ResponseLoginPacket *&response);

	/*
	实名认证：Identity
	id：int：主键
	mobile：string：手机号
	IDCard：string：身份证号，客户端要作身份证号的校验
	actname：string：身份证上面对应的姓名
	return 0成功，-1失败帐号不存在
	*/
	int identityUser(const IdentityPacket *packet);

	/*
	发布知返：PublishZhiFan
	userid：int：用户数据库id主键
	type：int：0招领1寻找
	title：string（64）：标题
	photo：list（m 5）：图片描述
	desc：string：描述文本
	lostType：int：这个参数的值由服务端给出。例如：钱财，旋律，证件等，此处填写其对应的数据库主键id值
	contactPlaceCode：string（64）：联系地点，由数据库的省市地区值组成，由逗号隔开
	lostDate：date：物品遗失日期，如：2014-02-02，是一个QDate值
	lostPlaceCodep：int：省code
	lostPlaceCodec：int：市code
	lostPlaceCoded：int：区code
	lostPlaceDetail：string（128）：除上面外的详细地址
	bills：int：悬赏积分
	return 0成功，-1用户不存在，-2发布失败
	*/
	int publishZhiFanUser(const PublishZhiFanPacket *packet);

	/*
	回答一个知返：ResponseZhiFan
	userid：int：回答的用户
	publishid：int：某个知返发布id
	context：string：用户发表的内容
	return： 0成功，-1用户不存在，-2知返不存在，-3回答失败，-4用户记录失败
	*/
	int responseZhiFanUser(const ResponseZhiFanPacket *packet);

	/*
	评论一个回答：CommentResponse
	responseid：int64：回答的id
	userid：int：评论者用户id
	referuser：int：回复的用户id
	context：string：用户评论的发表内容
	return：0成功，-1用户不存在，-2数据库插入失败
			-3关注表插入失败,-4不存在这样的回答
	*/
	int commentResponseUser(const CommentResponsePacket *packet);

	/*
	完成知返：CompleteZhiFan【有待商量】
	publish：int：某个知返的发布id
	targetid：int： 外键用户
	type：int：以什么方式完成。0回答，1毛遂自荐
	bills：int：悬赏积分
	return 0成功，-1用户不存在,-2知返不存在
	*/
	int completeZhiFanUser(const CompleteZhiFanPacket *packet);

	/*
	赞同或反对知返的一个回答：ApplaudZhiFan
	userid：int：谁发起的赞同或反对
	responseid：int64：回答的id
	applaudoppose：bool：0赞同，1反对
	return：0成功，-1用户不存在，-2赞同或反对操作失败， -3回答不存在
			-4不能重复此操作多次，-5赞同记录表插入失败
	*/
	int applaudZhiFanUser(const ApplaudZhiFanPacket *packet);

	/*
	获取知返发布内容（扼要）：GetZhiFanPublishPageOfRange
	userid：int：用户id
	upperLimit：int：闭区间 ]
	lowerLimit：int：开区间 )
	return 0成功，-1用户不存在，-2参数逻辑错误，-3数据库无法完成分页操作
	*/
	int getZhiFanPublishPageOfRangeUser(const GetZhiFanPublishPageOfRangePacket *packet, ResponseGetZhiFanPublishPageOfRangePacket *&response);

	/*
	获取知返的详细内容（详细）：GetOneZhiFanPublish
	userid：int：用户id
	publishid：int：知返id
	return 0成功，-1用户不存在
	*/
	int getOneZhiFanPublishUser(const GetOneZhiFanPublishPacket *packet, ResponseGetOneZhiFanPublishPacket *&response);

	/*
	搜索知返：SearchZhiFan
	userid：int：用户id
	codep：int：省code（为0表示null，下同）
	codec：int：市code
	coded：int：区code
	keyword：string：搜索关键字（不包含空格）
	upperLimit：int：闭区间 ]
	lowerLimit：int：开区间 )
	return 0成功，-1用户不存在
	*/
	int searchZhiFanUser(const SearchZhiFanPacket *packet, ResponseSearchZhiFanPacket *&response);

	/*
	主动拉取用户中心推送：PullUserCenter：
	userid：int：用户id
	type：int：0普通系统消息推送，1所关注的知返有新的回答，2您的回答有新的评论，3您评论的回答有新的评论
	return 0成功，-1用户不存在
	*/
	int pullUserCenterUser(const PullUserCenterPacket *packet);

	/*HTTP接口*/

	/**
	@brief 个人信息
	@param userid 用户id
	@param token token信息
	@return 0成功，-1用户验证错误
	*/
	int HttpUserInfo(const int userid, const QString &token, QVariantMap &out);

	/**
	@brief 申请认证
	@param userid 用户id
	@param token token信息
	@return 0成功，-1用户验证错误
	*/
	int HttpUserIdentity(const int userid, const QString &token, const QString &name, const QString &idcard, QVariantMap &out);

	/**
	@brief 通知中心，每次发送5条消息，会包含所有信息
	@param userid 用户id
	@param token token信息
	@param pageNum 当前第几页消息
	@return 0成功，-1用户验证错误
	*/
	int HttpUserNoticeCenter(const int userid, const QString &token, int pageNum, QByteArray &out);

protected:
	void briefZhiFanAnalysis(QSqlQuery &query, const Range &range, ResponseGetZhiFanPublishPageOfRangePacket *response_dispatch);
private:
	DBModule(QObject *parent = 0);
	~DBModule();
private:
	SettingInfo *databaseInfo;		//指针指向SettingHelper的数据成员，这里不做内存管理
};

#endif // DBMODULE_H
