#include "stdafx.h"
#include "Terminal.h"
#include "DBModule.h"
#include "HttpServer.h"
#include "HttpRequestParser.h"
#include <QtWidgets/QApplication>

using namespace std;
void test(){
	auto ins = getInstance(DBModule);
	QByteArray out;
	ins->HttpUserNoticeCenter(1, "2", 1, out);
}
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//初始化数据库
	/*auto ins = getInstance(DBModule);
	ins->initConnect();
	//启动知返服务
	Terminal *object = new Terminal(&a);
	object->start();*/
	HttpServer *server = new HttpServer(&a);
	if (!server->listen(QHostAddress("127.0.0.1"))){
		qDebug() << "监听失败！";
	}

	test();
	/*HttpParser paser;
	paser.parse("GET /cgi-bin/tmpDraw.cgi?type=pie&color=green HTTP/1.1\n");
	if (paser.isVaild()){
		qDebug() << paser.getResourcePath();
		qDebug() << paser.getQueryItems();
	}*/
	
	return a.exec();
}
