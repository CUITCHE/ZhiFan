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
	delete processThread;
	delete serverSocket;
}
