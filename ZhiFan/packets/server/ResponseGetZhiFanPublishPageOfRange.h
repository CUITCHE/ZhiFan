#ifndef ResponseGetZhiFanPublishPageOfRange_H__
#define ResponseGetZhiFanPublishPageOfRange_H__

/*!
 * \file ResponseGetZhiFanPublishPageOfRange.h
 *
 * \author CHE
 * \date ���� 2015
 *
 * For����ȡ֪���������ݣ���Ҫ����GetZhiFanPublishPageOfRange��ResponseGetZhiFanPublishPageOfRange
 */

#include "Packet.h"

PACKET_DEFINITION_BEGIN(ResponseGetZhiFanPublishPageOfRange)
Q_OBJECT
PACKET_STRUCTION(ResponseGetZhiFanPublishPageOfRange)

QT_MOC_MINE_DEFINITION(QString, mobile, Mobile);
QT_MOC_MINE_DEFINITION(QString, password, Password);

PACKET_DEFINITION_END

#endif // ResponseGetZhiFanPublishPageOfRange_H__
