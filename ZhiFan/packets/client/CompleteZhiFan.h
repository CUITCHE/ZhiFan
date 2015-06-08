#ifndef CompleteZhiFan_H__
#define CompleteZhiFan_H__

/*!
 * \file CompleteZhiFan.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 完成知返
 */

#include "Packet.h"
/*
publish：int：某个知返的发布id
targeted：string：多个参与的用户id，以逗号隔开
type：int：以什么方式完成。0回答，1毛遂自荐
bills：int：悬赏积分
*/
PACKET_DEFINITION_BEGIN(CompleteZhiFan)
Q_OBJECT
PACKET_STRUCTION(CompleteZhiFan)
//publish：int：某个知返的发布id
QT_MOC_MINE_DEFINITION(int, publish, Publish);
//targeted：string：多个参与的用户id，以逗号隔开
QT_MOC_MINE_DEFINITION(QString, targeted, Targeted);
//type：int：以什么方式完成。0回答，1毛遂自荐
QT_MOC_MINE_DEFINITION(int, type, Type);
//bills：int：悬赏积分
QT_MOC_MINE_DEFINITION(int, bills, Bills);
PACKET_DEFINITION_END
#endif // CompleteZhiFan_H__
