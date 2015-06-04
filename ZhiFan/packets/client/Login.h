#ifndef Login_H__
#define Login_H__

/*!
 * \file Login.h
 *
 * \author CHE
 * \date ÁùÔÂ 2015
 *
 * µÇÂ¼
 */
#include "Packet.h"

PACKET_DEFINITION_BEGIN(Login)
Q_OBJECT
PACKET_STRUCTION(Login)

QT_MOC_MINE_DEFINITION(QString, mobile, Mobile);
QT_MOC_MINE_DEFINITION(QString, password, Password);

PACKET_DEFINITION_END
#endif // Login_H__
