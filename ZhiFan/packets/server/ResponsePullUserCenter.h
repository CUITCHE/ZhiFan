#ifndef ResponsePullUserCenter_H__
#define ResponsePullUserCenter_H__

/*!
 * \file ResponsePullUserCenter.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * For：主动拉取用户中心推送：PullUserCenter：ResponsePullUserCenter
 */

#include "Packet.h"
/*
type：int：0普通系统消息推送，1所关注的知返有新的回答，2您的回答有新的评论，3您评论的回答有新的评论
id：int64：0没有id，其它id
briefmsg：string：信息摘要（id为0时，是详细信息）

*/
PACKET_DEFINITION_BEGIN(ResponsePullUserCenter)
Q_OBJECT
PACKET_STRUCTION(ResponsePullUserCenter)
//type：int：0普通系统消息推送，1所关注的知返有新的回答，2您的回答有新的评论，3您评论的回答有新的评论
QT_MOC_MINE_DEFINITION(int, type, Type);
//id：int64：0没有id，其它id
QT_MOC_MINE_DEFINITION(long long, id, Id);
//briefmsg：string：信息摘要（id为0时，是详细信息）
QT_MOC_MINE_DEFINITION(QString, briefmsg, Briefmsg);

PACKET_DEFINITION_END
#endif // ResponsePullUserCenter_H__
