#include "stdafx.h"
#include "Terminal.h"
#include "DBModule.h"
#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//��ʼ�����ݿ�
	auto ins = getInstance(DBModule);
	ins->initConnect();
	//����֪������
	Terminal *object = new Terminal(&a);
	object->start();
	return a.exec();
}
