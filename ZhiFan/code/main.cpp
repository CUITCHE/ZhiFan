#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "DBModule.h"
#include "ResponseSearchZhiFan.h"
#include <ResponseGetZhiFanPublishPageOfRange.h>
using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	auto ins = getInstance(DBModule);
	ins->initConnect();
	auto ret = ins->registerUser("12", "1564");
	return a.exec();
}
