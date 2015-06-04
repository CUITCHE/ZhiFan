#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "DBModule.h"
#include "ServerBackPacket.h"
using namespace std;
void debuggerTest(){
	int *p = new int(0);
	delete p;
	delete p;
}
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	auto ins = getInstance(DBModule);
	ins->initConnect();
	debuggerTest();
	return a.exec();
}
