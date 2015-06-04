#ifndef ResponseZhiFan_H__
#define ResponseZhiFan_H__

/*!
 * \file ResponseZhiFan.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 回答一个知返
 */

#include "Packet.h"
/*userid：int：回答的用户
publishid：int：某个知返发布id
context：string：用户发表的内容
*/
PACKET_DEFINITION_BEGIN(ResponseZhiFan)
Q_OBJECT
PACKET_STRUCTION(ResponseZhiFan)

QT_MOC_MINE_DEFINITION(int, userid, Userid);
QT_MOC_MINE_DEFINITION(int, publishid, Publishid);
QT_MOC_MINE_DEFINITION(QString, context, Context);

PACKET_DEFINITION_END
#endif // ResponseZhiFan_H__
