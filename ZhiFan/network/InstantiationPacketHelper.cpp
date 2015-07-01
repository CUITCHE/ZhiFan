#include "stdafx.h"
#include "InstantiationPacketHelper.h"
#include "packets.h"

using namespace net;

InstantiationPacketHelper::InstantiationPacketHelper()
{

}

InstantiationPacketHelper::~InstantiationPacketHelper()
{

}

Packet* InstantiationPacketHelper::getPacketByProtocol(const int protocol)
{
#define Case(V) pck = new V##Packet;break;
	Packet *pck = nullptr;
	switch (protocol)
	{
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
#undef Case
	return pck;
}
namespace net{
	Packet* get(const int protocol)
	{
		return InstantiationPacketHelper::getPacketByProtocol(protocol);
	}
}
