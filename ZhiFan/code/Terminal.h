#ifndef Terminal_H__
#define Terminal_H__

/*!
 * \file Terminal.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 终端控制
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
	NetServerControl *serverSocket;		//服务socket，负责网络socket的创建
	NetLogicMainProcess *processThread;	//业务流程处理线程
};
#endif // Terminal_H__
