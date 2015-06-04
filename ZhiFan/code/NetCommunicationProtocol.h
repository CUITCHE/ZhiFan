#ifndef NetCommunicationProtocol_H__
#define NetCommunicationProtocol_H__

/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   15:29
	file base:	NetCommunicationProtocol
	author:		CHE

	purpose:	网络通信协议
	主要是pakcet包协议的定义
	*********************************************************************/
#define Case(V) case V: return #V
namespace net{
	enum NetCommunicationProtocol :unsigned int{
		Empty,
		Test,
		//客户端协议
		//注册
		Register,
		//登录
		Login,
		//实名认证
		Identity,
		//发布知返
		PublishZhiFan,
		//回答一个知返
		ResponseZhiFan,
		//平路一个回答
		CommentResponse,
		//完成知返
		CompleteZhiFan,
		//赞同或反对知返的一个回答
		ApplaudZhiFan,
		//获取知返发布内容
		GetZhiFanPublishPageOfRange,
		//搜索知返
		SearchZhiFan,
		//拉取用户中心推送
		PullUserCenter,

		//服务端协议

		//操作确认返回
		ServerBack,
		//For：登陆：Login：ResponseLogin
		ResponseLogin,
		//For：主动拉取用户中心推送：PullUserCenter：ResponsePullUserCenter
		ResponsePullUserCenter,
		//For：获取知返发布内容：GetZhiFanPublishPageOfRange：ResponseGetZhiFanPublishPageOfRange
		ResponseGetZhiFanPublishPageOfRange,
		//For：搜索知返：SearchZhiFan：ResponseSearchZhiFan
		ResponseSearchZhiFan

	};
	static const char *ProtocolToString(unsigned int val){
		switch (val)
		{
			Case(Empty);
			Case(Test);
			Case(Identity);
			Case(PublishZhiFan);
			Case(ResponseZhiFan);
			Case(CommentResponse);
			Case(CompleteZhiFan);
			Case(ApplaudZhiFan);
			Case(GetZhiFanPublishPageOfRange);
			Case(SearchZhiFan);
			Case(PullUserCenter);
			Case(ServerBack);
			Case(ResponseLogin);
			Case(ResponsePullUserCenter);
			Case(ResponseGetZhiFanPublishPageOfRange);
			Case(ResponseSearchZhiFan);
		default:
			break;
		}
		return "Not exists";
	}
	const int MAX_PROTOCOL = ServerBack;
}
#undef Case
#endif // NetCommunicationProtocol_H__
