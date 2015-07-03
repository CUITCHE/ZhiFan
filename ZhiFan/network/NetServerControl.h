#ifndef NETSERVERCONTROL_H
#define NETSERVERCONTROL_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   20:29
	file base:	NetServerControl
	author:		CHE
	
	purpose:	����ͨ�Ž���ģ�飬
				��ʱ��Qt��װ���������������
				֮���������ٸ���������Чģʽ��
				�����п��ܲ���QQ��UDP+TCP�Ļ��
*********************************************************************/
#include <QObject>
#include <QList>
#include <QQueue>
#include <memory>
using namespace std;
class QTcpServer;
class QTcpSocket;
class QMutex;
//�ͻ��������˽�������Ҫ�����ݽṹ
struct NetCommunicationModule
{
	QTcpSocket *sock;
	QByteArray data;
};
class NetServerControl : public QObject
{
	Q_OBJECT

public:
	NetServerControl(QObject *parent = 0);
	~NetServerControl();

	//�Ƴ�ָ����socket
	void removeSocket(QTcpSocket *sock);

	//�ж��Ƿ������ݵ���
	bool isPendingClientData()const;

	//��sharedDataListȡ��һ������
	NetCommunicationModule getPendingData();
signals:
	void taskDataNeed(NetCommunicationModule &data);
protected:
	void doListen();
public slots:
	//�пͻ�������
	void newConnectionProcess();

	//�ͻ�������Ϣ���͹���
	void pendingRecieveData();

	//�ͻ��������˶Ͽ����ӵĴ���
	void onClientSocketDisconnect();
private:
	QTcpServer *serverSocket;		//����socket
	QList<QTcpSocket*> connections;		//�洢�������ӵ�socket
	QMutex *mutex;									//sharedDataList�Ļ�����
	QList<NetCommunicationModule> sharedDataList;	//�ͻ��˷��������ݣ��洢����˭������QTcpSocketָ��
};

#endif // NETSERVERCONTROL_H
