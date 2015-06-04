#ifndef PublishZhiFan_H__
#define PublishZhiFan_H__

/*!
 * \file PublishZhiFan.h
 *
 * \author CHE
 * \date ���� 2015
 *
 * ����֪��
 */

#include "Packet.h"
#include <QList>
#include <QDate>
/*����֪����PublishZhiFan
userid��int���û����ݿ�id����
type��int��0����1Ѱ��
title��string��64��������
photo��list��m 5����ͼƬ����
desc��string�������ı�
lostType��int�����������ֵ�ɷ���˸��������磺Ǯ�ƣ����ɣ�֤���ȣ��˴���д���Ӧ�����ݿ�����idֵ
contactPlaceCode��string��64������ϵ�ص㣬�����ݿ��ʡ�е���ֵ��ɣ��ɶ��Ÿ���
lostDate��date����Ʒ��ʧ���ڣ��磺2014-02-02����һ��QDateֵ
lostPlaceCode��string��64������Ʒ��ʧ�ĵ�ַcode
lostPlaceDetail��string��128���������������ϸ��ַ
bills��int�����ͻ���
*/
PACKET_DEFINITION_BEGIN(PublishZhiFan)
Q_OBJECT
PACKET_STRUCTION(PublishZhiFan)
//userid��int���û����ݿ�id����
QT_MOC_MINE_DEFINITION(int, userid, Userid);
//0����1Ѱ��
QT_MOC_MINE_DEFINITION(int, type, Type);
//����
QT_MOC_MINE_DEFINITION(QString, title, Title);
//list��m 5����ͼƬ����
QT_MOC_MINE_DEFINITION(QList<QString>, photo, Photo);
//�����ı�
QT_MOC_MINE_DEFINITION(QString, desc, Desc);
//���������ֵ�ɷ���˸��������磺Ǯ�ƣ����ɣ�֤���ȣ��˴���д���Ӧ�����ݿ�����idֵ
QT_MOC_MINE_DEFINITION(int, lostType, LostType);
//contactPlaceCode��string��64������ϵ�ص㣬�����ݿ��ʡ�е���ֵ��ɣ��ɶ��Ÿ���
QT_MOC_MINE_DEFINITION(QString, contactPlaceCode, ContactPlaceCode);
//lostDate��date����Ʒ��ʧ���ڣ��磺2014-02-02����һ��QDateֵ
QT_MOC_MINE_DEFINITION(QDate, lostDate, LostDate);
//lostPlaceCode��string��64������Ʒ��ʧ�ĵ�ַcode
QT_MOC_MINE_DEFINITION(QString, lostPlaceCode, LostPlaceCode);
//lostPlaceDetail��string��128���������������ϸ��ַ
QT_MOC_MINE_DEFINITION(QString, lostPlaceDetail, LostPlaceDetail);
//bills��int�����ͻ���
QT_MOC_MINE_DEFINITION(int, bills, Bills);


PACKET_DEFINITION_END

#endif // PublishZhiFan_H__
