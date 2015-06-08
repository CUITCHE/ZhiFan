#ifndef ZhiFanPublishBriefOne_H__
#define ZhiFanPublishBriefOne_H__

/*!
 * \file ZhiFanPublishBriefOne.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * ZhiFanPublishBriefOne
 */
#include "Packet.h"
#include <QList>
#include <QDateTime>
/*
publishId：int：知返id
ownerId：int：发布者id
title：string（64）：标题
photo：stringBASE64-list：图片信息
lightEyes：bool：是否醒目
topTime：置顶的时间
briefDesc：string：描述信息

type：int：0招领，1寻找
responseNum：int：回答数
responseInfo：string（nchar）：简略的回答信息，点赞最多的
resposneApplaudNum：int：这条回答的点赞次数

*/
class ZhiFanPublishBriefOnePacket;
Q_DECLARE_METATYPE(ZhiFanPublishBriefOnePacket);
PACKET_DEFINITION_BEGIN(ZhiFanPublishBriefOne)
Q_OBJECT
PACKET_STRUCTION(ZhiFanPublishBriefOne)
operator QVariant()const{
	return QVariant::fromValue(*this);
}
//publishId：int：知返id
QT_MOC_MINE_DEFINITION(int, publishId, PublishId);
//ownerId：int：发布者id
QT_MOC_MINE_DEFINITION(int, ownerId, OwnerId);
//photo：stringBASE64-list：图片信息
QT_MOC_MINE_DEFINITION(QList<QVariant>, photo, Photo);
//briefDesc：string：简略的描述信息
QT_MOC_MINE_DEFINITION(QString, briefDesc, BriefDesc);
//title：string（64）：标题
QT_MOC_MINE_DEFINITION(QString, title, Title);
//lightEyes：bool：是否醒目
QT_MOC_MINE_DEFINITION(bool, lightEyes, LightEyes);
//topTime：置顶的时间
QT_MOC_MINE_DEFINITION(QDateTime, topTime, TopTime);

//type：int：0招领，1寻找
QT_MOC_MINE_DEFINITION(int, type, Type);
//responseNum：int：回答数
QT_MOC_MINE_DEFINITION(int, responseNum, ResponseNum);
//responseInfo：string（nchar）：简略的回答信息，点赞最多的
QT_MOC_MINE_DEFINITION(QString, responseInfo, ResponseInfo);
//resposneApplaudNum：int：这条回答的点赞次数
QT_MOC_MINE_DEFINITION(int, resposneApplaudNum, ResposneApplaudNum);


PACKET_DEFINITION_END
#endif // ZhiFanPublishBriefOne_H__
