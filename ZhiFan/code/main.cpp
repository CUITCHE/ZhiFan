#include "stdafx.h"
#include "Terminal.h"
#include "DBModule.h"
#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//初始化数据库
	auto ins = getInstance(DBModule);
	ins->initConnect();
	//启动知返服务
	Terminal *object = new Terminal(&a);
	object->start();
	return a.exec();
}
