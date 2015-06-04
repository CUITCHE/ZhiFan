#ifndef Register_H__
#define Register_H__

/*!
 * \file Register.h
 *
 * \author CHE
 * \date ÁùÔÂ 2015
 *
 * ×¢²á
 */

#include "Packet.h"

PACKET_DEFINITION_BEGIN(Register)
Q_OBJECT
PACKET_STRUCTION(Register)

QT_MOC_MINE_DEFINITION(QString, mobile, Mobile);
QT_MOC_MINE_DEFINITION(QString, password, Password);

PACKET_DEFINITION_END

#endif // Register_H__
