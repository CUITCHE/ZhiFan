#ifndef SearchZhiFan_H__
#define SearchZhiFan_H__

/*!
 * \file SearchZhiFan.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 搜索知返
 */

#include "Packet.h"
/*
userid：int：用户id
codep：int：省code（为0表示null，下同）
codec：int：市code
coded：int：区code
keyword：string：搜索关键字（不包含空格）
upperLimit：int：闭区间 ]
lowerLimit：int：开区间 )

*/
PACKET_DEFINITION_BEGIN(SearchZhiFan)
Q_OBJECT
PACKET_STRUCTION(SearchZhiFan)

//userid：int：用户id
QT_MOC_MINE_DEFINITION(int, userid, Userid);
//codep：int：省code（为0表示null，下同）
QT_MOC_MINE_DEFINITION(int, codep, Codep);
//codec：int：市code
QT_MOC_MINE_DEFINITION(int, codec, Codec);
//coded：int：区code
QT_MOC_MINE_DEFINITION(int, coded, Coded);
//keyword：string：搜索关键字（不包含空格）
QT_MOC_MINE_DEFINITION(QString, keyword, Keyword);
//upperLimit：int：闭区间 ]
QT_MOC_MINE_DEFINITION(int, upperLimit, UpperLimit);
//lowerLimit：int：开区间 )
QT_MOC_MINE_DEFINITION(int, lowerLimit, LowerLimit);


PACKET_DEFINITION_END
#endif // SearchZhiFan_H__
