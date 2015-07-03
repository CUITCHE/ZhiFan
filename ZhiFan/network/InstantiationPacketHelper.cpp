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
#define Case(V) pck = new V##Packet;break;
Packet* InstantiationPacketHelper::getPacketByProtocol(const int protocol)
{
	Packet *pck = nullptr;
	switch ((net::NetCommunicationProtocol)protocol)
	{
	case Register:
		pck = new RegisterPacket;
		break;
	case Login:
		pck = new LoginPacket;
		break;
	case Identity:
		pck = new IdentityPacket;
		break;
	case PublishZhiFan:
		pck = new PublishZhiFanPacket;
		break;
	case ResponseZhiFan:
		pck = new ResponseZhiFanPacket;
		break;
	case CommentResponse:
		pck = new CommentResponsePacket;
		break;
	case CompleteZhiFan:
		pck = new CompleteZhiFanPacket;
		break;
	case ApplaudZhiFan:
		pck = new ApplaudZhiFanPacket;
		break;
	case GetZhiFanPublishPageOfRange:
		pck = new GetZhiFanPublishPageOfRangePacket;
		break;
	case GetOneZhiFanPublish:
		pck = new GetOneZhiFanPublishPacket;
		break;
	case  SearchZhiFan:
		pck = new SearchZhiFanPacket;
		break;
	case  PullUserCenter:
		pck = new PullUserCenterPacket;
		break;
	case  ServerBack:
		pck = new ServerBackPacket;
		break;
	case  ResponseLogin:
		pck = new ResponseLoginPacket;
		break;
	case  ResponsePullUserCenter:
		pck = new ResponsePullUserCenterPacket;
		break;
	case  ResponseGetZhiFanPublishPageOfRange:
		pck = new ResponseGetZhiFanPublishPageOfRangePacket;
		break;
	case  ResponseSearchZhiFan:
		pck = new ResponseSearchZhiFanPacket;
		break;
	case  ZhiFanPublishOne:
		pck = new ZhiFanPublishOnePacket;
		break;
	default:
		break;
	}
	return pck;
}
#undef Case
namespace net{
	Packet* get(const int protocol)
	{
		return InstantiationPacketHelper::getPacketByProtocol(protocol);
	}
}
