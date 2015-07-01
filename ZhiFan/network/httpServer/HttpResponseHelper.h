#ifndef HTTPRESPONSEHELPER_H
#define HTTPRESPONSEHELPER_H
/*!
 * \file HttpResponseHelper.h
 *
 * \author CHE
 * \date 七月 2015
 *
 * 协助生成响应报头，本工具类消耗较大，建议多次使用
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
	 @brief 生成http请求报文
	*/
	QByteArray generateHttpText()const;

	/*
	 @brief 若需要设置，只需要设置一次，默认为 HTTP/1.1
	*/
	void setHttpVersion(const QString &version);

	/*
	 @brief 清除缓存信息，版本号不会被清除
	*/
	void clear();
	/*
	 @brief 设置header
	 */
	void setHeader(KnownHeader header, const QString &value);

	/*
	 @brief 设置请求头
	 @param status 状态码
	*/
	void setHead(int status);

	/*
	 @brief 设置正文context
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
