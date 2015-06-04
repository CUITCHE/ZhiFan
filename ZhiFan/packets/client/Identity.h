#ifndef Identity_H__
#define Identity_H__

/*!
 * \file Identity.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 实名认证
 */

#include "Packet.h"

PACKET_DEFINITION_BEGIN(Identity)
Q_OBJECT
PACKET_STRUCTION(Identity)

QT_MOC_MINE_DEFINITION(int, id, Id);
QT_MOC_MINE_DEFINITION(QString, mobile, Mobile);
//身份证号，客户端要作身份证号的校验
QT_MOC_MINE_DEFINITION(QString, IDCard, IDCard);
//身份证上面对应的姓名
QT_MOC_MINE_DEFINITION(QString, actname, Actname);

PACKET_DEFINITION_END

#endif // Identity_H__
