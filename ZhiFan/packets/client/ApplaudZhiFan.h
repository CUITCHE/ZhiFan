#ifndef ApplaudZhiFan_H__
#define ApplaudZhiFan_H__

/*!
 * \file ApplaudZhiFan.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 赞同或反对知返的一个回答
 */
#include "Packet.h"
/*
userid：int：谁发起的赞同或反对
responseid：int64：回答的id
applaudoppose：bool：0赞同，1反对

*/
PACKET_DEFINITION_BEGIN(ApplaudZhiFan)
Q_OBJECT
PACKET_STRUCTION(ApplaudZhiFan)
//userid：int：谁发起的赞同或反对
QT_MOC_MINE_DEFINITION(int, userid, Userid);
//responseid：int64：回答的id
QT_MOC_MINE_DEFINITION(long long, responseid, Responseid);
//applaudoppose：bool：0赞同，1反对
QT_MOC_MINE_DEFINITION(bool, applaudoppose, Applaudoppose);

PACKET_DEFINITION_END
#endif // ApplaudZhiFan_H__
