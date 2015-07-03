#ifndef Terminal_H__
#define Terminal_H__

/*!
 * \file Terminal.h
 *
 * \author CHE
 * \date ���� 2015
 *
 * �ն˿���
 */
#include <QObject>
class NetServerControl;
class NetLogicMainProcess;
class Terminal: public QObject
{
public:
	Terminal(QObject *parent = 0);
	~Terminal();
private:
	NetServerControl *serverSocket;		//����socket����������socket�Ĵ���
	NetLogicMainProcess *processThread;	//ҵ�����̴����߳�
};
#endif // Terminal_H__
