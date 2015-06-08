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
		//获取知返发布内容（扼要）
		GetZhiFanPublishPageOfRange,
		//获取一个知返内容的（详细）
		GetOneZhiFanPublish,
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
		ResponseSearchZhiFan,
		//For：获取知返的详细内容（详细）：GetOneZhiFanPublish：ResponseGetOneZhiFanPublish
		ResponseGetOneZhiFanPublish,
		//知返内容包（扼要）：ZhiFanPublishBriefOne
		ZhiFanPublishBriefOne,
		//知返内容包
		ZhiFanPublishOne,

		//max
		MAX = ZhiFanPublishOne

	};
#define Case(V) case V: return #V
	static const char *ProtocolToString(unsigned int val){
		switch (val)
		{
			Case(Empty);
			Case(Test);
			Case(Register);
			Case(Login);
			Case(Identity);
			Case(PublishZhiFan);
			Case(ResponseZhiFan);
			Case(CommentResponse);
			Case(CompleteZhiFan);
			Case(ApplaudZhiFan);
			Case(GetZhiFanPublishPageOfRange);
			Case(GetOneZhiFanPublish);
			Case(SearchZhiFan);
			Case(PullUserCenter);
			Case(ServerBack);
			Case(ResponseLogin);
			Case(ResponsePullUserCenter);
			Case(ResponseGetZhiFanPublishPageOfRange);
			Case(ResponseSearchZhiFan);
			Case(ZhiFanPublishOne);
		default:
			break;
		}
		return "Not exists";
	}
#undef Case

#define Case(V) case V:return V
	static NetCommunicationProtocol protocol_cast(unsigned int val){
		switch (val)
		{
			Case(Empty);
			Case(Test);
			Case(Register);
			Case(Login);
			Case(Identity);
			Case(PublishZhiFan);
			Case(ResponseZhiFan);
			Case(CommentResponse);
			Case(CompleteZhiFan);
			Case(ApplaudZhiFan);
			Case(GetZhiFanPublishPageOfRange);
			Case(GetOneZhiFanPublish);
			Case(SearchZhiFan);
			Case(PullUserCenter);
			Case(ServerBack);
			Case(ResponseLogin);
			Case(ResponsePullUserCenter);
			Case(ResponseGetZhiFanPublishPageOfRange);
			Case(ResponseSearchZhiFan);
			Case(ZhiFanPublishOne);
		default:
			break;
		}
		return Empty;
	}
#undef Case
	const int MAX_PROTOCOL = MAX;
}

#endif // NetCommunicationProtocol_H__
