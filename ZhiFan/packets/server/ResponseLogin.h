#ifndef ResponseLogin_H__
#define ResponseLogin_H__

/*!
 * \file ResponseLogin.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * For：登陆：Login：ResponseLogin
 */

#include "Packet.h"
/*
identification：bool：1验证，0未验证
IDCardSubstring：string：生日+后4位身份证号码，如果有
zfb：int：积分数量
userid：int：用户id

*/
PACKET_DEFINITION_BEGIN(ResponseLogin)
Q_OBJECT
PACKET_STRUCTION(ResponseLogin)
//identification：bool：1验证，0未验证
QT_MOC_MINE_DEFINITION(bool, identification, Identification);
//IDCardSubstring：string：生日+后4位身份证号码，如果有
QT_MOC_MINE_DEFINITION(QString, IDCardSubstring, IDCardSubstring);
//zfb：int：积分数量
QT_MOC_MINE_DEFINITION(int, zfb, Zfb);
//userid：int：用户id
QT_MOC_MINE_DEFINITION(int, userid, Userid);

PACKET_DEFINITION_END
#endif // ResponseLogin_H__
