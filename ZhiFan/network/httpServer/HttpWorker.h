#ifndef HTTPWORKER_H
#define HTTPWORKER_H
/*!
 * \file HttpWorker.h
 *
 * \author CHE
 * \date ���� 2015
 *
 * ����http����
 */
#include <QObject>

class HttpWorkerPrivate;

__interface IHttpHtml
{
	/*
	@brief �û�����ҳ�棬��һ��tabҳ
	*/
	void userCenter();

	/*
	@brief �ʺŹ������
	*/
	void accountMananger();

	/*
	@brief ֪ͨ����
	*/
	void noticeCenter();

	/*
	@brief �ҷ�����֪��
	*/
	void myPublished();

	/*
	@brief �Ҳ������֪�����ش���ģ����޹��ģ�
	*/
	void myJoined();
};

class HttpWorker : public QObject, public IHttpHtml
{
	Q_OBJECT

public:
	HttpWorker(QObject *parent = 0);
	~HttpWorker();

	/*
	 @brief �������HttpRequestParser���͵�ָ�룬���Ѿ�����������HttpRequestParser
	*/
	void setObject(QObject *object);

	/*
	 @brief ���������񣬽����ɵ��ַ�������
	*/
	void getResponseString(QByteArray &out);
protected:
	HttpWorkerPrivate *const d_ptr;
	/*
	@brief �û�����ҳ�棬��һ��tabҳ
	*/
	void userCenter();

	/*
	@brief �ַ�����
	*/
	void dispatch();

	/*
	@brief �ʺŹ������
	*/
	void accountMananger();

	/*
	@brief ֪ͨ����
	*/
	void noticeCenter();

	/*
	@brief �ҷ�����֪��
	*/
	void myPublished();

	/*
	@brief �Ҳ������֪�����ش���ģ����޹��ģ�
	*/
	void myJoined();
private:
	Q_DECLARE_PRIVATE(HttpWorker);
	/*
	@brief �ʺ���֤������֤�ʺ��Ƿ����ߣ�����֤token�Ƿ���ȷ
	@return �ɹ�����true
	*/
	bool accountVerification(const QString &userid, const QString &token);

	/*
	@brief д403 Forbidden
	*/
	void write403();

	/*
	@brief д404 Not Found html
	*/
	void write404();

	/*
	@brief �����ļ�
	*/
	void writeFile(const QString &path);
};

#endif // HTTPWORKER_H
