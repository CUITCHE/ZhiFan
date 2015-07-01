#include "stdafx.h"
#include "Terminal.h"
#include "NetServerControl.h"
#include "NetLogicMainProcess.h"

Terminal::Terminal(QObject *parent /*= 0*/)
	:serverSocket(new NetServerControl(this))
{
	processThread = new NetLogicMainProcess(serverSocket);
}

Terminal::~Terminal()
{
	stop();
	delete processThread;
	delete serverSocket;
}

void Terminal::start()
{
	if (!processThread->isActive()){
		processThread->start();
	}
}

void Terminal::stop()
{
	if (processThread->isActive()){
		processThread->stop();
	}
}
