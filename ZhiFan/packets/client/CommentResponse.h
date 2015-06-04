#ifndef CommentResponse_H__
#define CommentResponse_H__

/*!
 * \file CommentResponse.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 评论一个回答
 */
#include "Packet.h"
/*responseid：int64：回答的id
userid：int：评论者用户id
referuser：int：回复的用户id
context：string：用户评论的发表内容
*/
PACKET_DEFINITION_BEGIN(CommentResponse)
Q_OBJECT
PACKET_STRUCTION(CommentResponse)
//responseid：int64：回答的id
QT_MOC_MINE_DEFINITION(long long, responseid, Responseid);
//userid：int：评论者用户id
QT_MOC_MINE_DEFINITION(int, userid, Userid);
//referuser：int：回复的用户id
QT_MOC_MINE_DEFINITION(int, referuser, Referuser);
//context：string：用户评论的发表内容
QT_MOC_MINE_DEFINITION(QString, context, Context);

PACKET_DEFINITION_END
#endif // CommentResponse_H__
