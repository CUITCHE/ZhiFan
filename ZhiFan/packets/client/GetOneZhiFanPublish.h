#ifndef GetOneZhiFanPublish_H__
#define GetOneZhiFanPublish_H__
/*!
 * \file GetOneZhiFanPublish.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 获取知返发布内容（详细）
 */

#include "Packet.h"
/*
userid：int：用户id
published：int：知返id
*/
PACKET_DEFINITION_BEGIN(GetOneZhiFanPublish)
Q_OBJECT
PACKET_STRUCTION(GetOneZhiFanPublish)
//userid：int：用户id
QT_MOC_MINE_DEFINITION(int, userid, Userid);
//published：int：知返id
QT_MOC_MINE_DEFINITION(int, publishid, Publishid);


PACKET_DEFINITION_END
#endif // GetOneZhiFanPublish_H__
