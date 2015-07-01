#ifndef HTTPRESPONSEHELPER_H
#define HTTPRESPONSEHELPER_H
/*!
 * \file HttpResponseHelper.h
 *
 * \author CHE
 * \date ���� 2015
 *
 * Э��������Ӧ��ͷ�������������Ľϴ󣬽�����ʹ��
 */
#include <QObject>

class HttpResponseHelperPrivate;

enum KnownHeader
{
	CacheControl,
	ContentEncoding,
	ContentLanguage,
	ContentLength,
	ContentType,
	Date,
	Location,
	//Request
	Host,
	Connection,
	Accept,
	UserAgent,
	Referer,
	AcceptEncoding,
	AcceptLanguage
};

class HttpResponseHelper : public QObject
{
	Q_OBJECT

public:
	HttpResponseHelper(QObject *parent = 0);
	~HttpResponseHelper();
	/*
	 @brief ����http������
	*/
	QByteArray generateHttpText()const;

	/*
	 @brief ����Ҫ���ã�ֻ��Ҫ����һ�Σ�Ĭ��Ϊ HTTP/1.1
	*/
	void setHttpVersion(const QString &version);

	/*
	 @brief ���������Ϣ���汾�Ų��ᱻ���
	*/
	void clear();
	/*
	 @brief ����header
	 */
	void setHeader(KnownHeader header, const QString &value);

	/*
	 @brief ��������ͷ
	 @param status ״̬��
	*/
	void setHead(int status);

	/*
	 @brief ��������context
	*/
	void setBody(const QByteArray &body);

protected:
	HttpResponseHelperPrivate *const d_ptr;
	static const QString& headerconvert(KnownHeader header);
	QString getDateForFormate()const;
private:
	Q_DECLARE_PRIVATE(HttpResponseHelper);
};

#endif // HTTPRESPONSEHELPER_H
