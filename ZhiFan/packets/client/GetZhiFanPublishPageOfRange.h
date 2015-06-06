#ifndef GetZhiFanPublishPageOfRange_H__
#define GetZhiFanPublishPageOfRange_H__

/*!
 * \file GetZhiFanPublishPageOfRange.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 获取知返发布内容（扼要）：GetZhiFanPublishPageOfRange
 */


#include "Packet.h"
/*
userid：int：用户id
upperLimit：int：闭区间 ]
lowerLimit：int：开区间 )

*/
PACKET_DEFINITION_BEGIN(GetZhiFanPublishPageOfRange)
Q_OBJECT
PACKET_STRUCTION(GetZhiFanPublishPageOfRange)
//userid：int：用户id
QT_MOC_MINE_DEFINITION(int, userid, Userid);
//upperLimit：int：闭区间 ]
QT_MOC_MINE_DEFINITION(int, upperLimit, UpperLimit);
//lowerLimit：int：开区间 )
QT_MOC_MINE_DEFINITION(int, lowerLimit, LowerLimit);

PACKET_DEFINITION_END
#endif // GetZhiFanPublishPageOfRange_H__
