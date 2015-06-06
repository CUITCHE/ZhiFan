#ifndef ZhiFanPublishOne_H__
#define ZhiFanPublishOne_H__

/*!
 * \file ZhiFanPublishOne.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 知返内容包：ZhiFanPublishOne
 */

#include "Packet.h"
#include <QDateTime>
#include <QList>
/*
publishId：int：知返的主键
ownerId：int：发布者id
publishdate：datetime：发布日期
lostType：int：知返类型
contactPlaceCode：string（64）：联系地点，失物，由数据库的省市地区值组成，由逗号隔开
lostDate：date：物品遗失时间
lostPlaceCodep：int：省code
lostPlaceCodec：int：市code
lostPlaceCoded：int：区code
lostPlacedetail：string（128）：详细地址
bills：int：悬赏积分


*/
class ZhiFanPublishOnePacket;
Q_DECLARE_METATYPE(ZhiFanPublishOnePacket);
PACKET_DEFINITION_BEGIN(ZhiFanPublishOne)
Q_OBJECT
PACKET_STRUCTION(ZhiFanPublishOne)
operator QVariant()const{
	return QVariant::fromValue(*this);
}
//publishId：int：知返的主键
QT_MOC_MINE_DEFINITION(int, publishId, PublishId);
//ownerId：int：发布者id
QT_MOC_MINE_DEFINITION(int, ownerId, OwnerId);

//publishdate：datetime：发布日期
QT_MOC_MINE_DEFINITION(QDateTime, publishdate, Publishdate);

//lostType：int：知返类型
QT_MOC_MINE_DEFINITION(int, lostType, LostType);
//contactPlaceCode：string（64）：联系地点，失物，由数据库的省市地区值组成，由逗号隔开
QT_MOC_MINE_DEFINITION(QString, contactPlaceCode, ContactPlaceCode);
//lostDate：date：物品遗失时间
QT_MOC_MINE_DEFINITION(QDate, lostDate, LostDate);
//lostPlaceCodep：int：省code
QT_MOC_MINE_DEFINITION(int, lostPlaceCodep, LostPlaceCodep);
//lostPlaceCodec：int：市code
QT_MOC_MINE_DEFINITION(int, lostPlaceCodec, LostPlaceCodec);
//lostPlaceCoded：int：区code
QT_MOC_MINE_DEFINITION(int, lostPlaceCoded, LostPlaceCoded);
//lostPlacedetail：string（128）：详细地址
QT_MOC_MINE_DEFINITION(QString, lostPlacedetail, LostPlacedetail);
//bills：int：悬赏积分
QT_MOC_MINE_DEFINITION(int, bills, Bills);
PACKET_DEFINITION_END
#endif // ZhiFanPublishOne_H__
