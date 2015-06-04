#ifndef PullUserCenter_H__
#define PullUserCenter_H__

/*!
 * \file PullUserCenter.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 主动拉取用户中心推送
 */

#include "Packet.h"
/*
userid：int：用户id
type：int：0普通系统消息推送，1所关注的知返有新的回答，2您的回答有新的评论，3您评论的回答有新的评论
*/
PACKET_DEFINITION_BEGIN(PullUserCenter)
Q_OBJECT
PACKET_STRUCTION(PullUserCenter)
//userid：int：用户id
QT_MOC_MINE_DEFINITION(int, userid, Userid);
//type：int：0普通系统消息推送，1所关注的知返有新的回答，2您的回答有新的评论，3您评论的回答有新的评论
QT_MOC_MINE_DEFINITION(int, type, Type);

PACKET_DEFINITION_END
#endif // PullUserCenter_H__
