#ifndef PublishZhiFan_H__
#define PublishZhiFan_H__

/*!
 * \file PublishZhiFan.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 发布知返
 */

#include "Packet.h"
#include <QList>
#include <QDate>
/*发布知返：PublishZhiFan
userid：int：用户数据库id主键
type：int：0招领1寻找
title：string（64）：标题
photo：list（m 5）：图片描述
desc：string：描述文本
lostType：int：这个参数的值由服务端给出。例如：钱财，旋律，证件等，此处填写其对应的数据库主键id值
contactPlaceCode：string（64）：联系地点，由数据库的省市地区值组成，由逗号隔开
lostDate：date：物品遗失日期，如：2014-02-02，是一个QDate值
ostPlaceCodep：int：省code
lostPlaceCodec：int：市code
lostPlaceCoded：int：区code

lostPlaceDetail：string（128）：除上面外的详细地址
bills：int：悬赏积分
*/
PACKET_DEFINITION_BEGIN(PublishZhiFan)
Q_OBJECT
PACKET_STRUCTION(PublishZhiFan)
//userid：int：用户数据库id主键
QT_MOC_MINE_DEFINITION(int, userid, Userid);
//0招领1寻找
QT_MOC_MINE_DEFINITION(int, type, Type);
//标题
QT_MOC_MINE_DEFINITION(QString, title, Title);
//list（m 5）：图片描述
QT_MOC_MINE_DEFINITION(QList<QVariant>, photo, Photo);
//描述文本
QT_MOC_MINE_DEFINITION(QString, desc, Desc);
//这个参数的值由服务端给出。例如：钱财，旋律，证件等，此处填写其对应的数据库主键id值
QT_MOC_MINE_DEFINITION(int, lostType, LostType);
//contactPlaceCode：string（64）：联系地点，由数据库的省市地区值组成，由逗号隔开
QT_MOC_MINE_DEFINITION(QString, contactPlaceCode, ContactPlaceCode);
//lostDate：date：物品遗失日期，如：2014-02-02，是一个QDate值
QT_MOC_MINE_DEFINITION(QDate, lostDate, LostDate);
//lostPlaceCodep：int：省code
QT_MOC_MINE_DEFINITION(int, lostPlaceCodep, LostPlaceCodep);
//lostPlaceCodec：int：市code
QT_MOC_MINE_DEFINITION(int, lostPlaceCodec, LostPlaceCodec);
//lostPlaceCoded：int：区code
QT_MOC_MINE_DEFINITION(int, lostPlaceCoded, LostPlaceCoded);
//lostPlaceDetail：string（128）：除上面外的详细地址
QT_MOC_MINE_DEFINITION(QString, lostPlaceDetail, LostPlaceDetail);
//bills：int：悬赏积分
QT_MOC_MINE_DEFINITION(int, bills, Bills);


PACKET_DEFINITION_END

#endif // PublishZhiFan_H__
