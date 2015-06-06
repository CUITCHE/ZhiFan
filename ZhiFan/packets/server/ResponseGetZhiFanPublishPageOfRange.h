#ifndef ResponseGetZhiFanPublishPageOfRange_H__
#define ResponseGetZhiFanPublishPageOfRange_H__

/*!
 * \file ResponseGetZhiFanPublishPageOfRange.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * For：获取知返发布内容（扼要）：GetZhiFanPublishPageOfRange：ResponseGetZhiFanPublishPageOfRange
 */

#include "ZhiFanPublishBriefOne.h"
#include "Range.h"

Q_DECLARE_METATYPE(QList<ZhiFanPublishBriefOnePacket>);
PACKET_DEFINITION_BEGIN(ResponseGetZhiFanPublishPageOfRange)
Q_OBJECT
PACKET_STRUCTION(ResponseGetZhiFanPublishPageOfRange)

//publishList：list< ZhiFanPublishOne >：小于等于 Range
QT_MOC_MINE_DEFINITION(QList<ZhiFanPublishBriefOnePacket>, publishList, PublishList);
//range：Range：范围值
QT_MOC_MINE_DEFINITION(Range, range, Range);
//hasNext：bool：还有后续内容
QT_MOC_MINE_DEFINITION(bool, hasNext, HasNext);

PACKET_DEFINITION_END

#endif // ResponseGetZhiFanPublishPageOfRange_H__
