#ifndef HTTPPARSER_H
#define HTTPPARSER_H
/*!
 * \file HttpRequestParser.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 解析HTTP请求字符串
 */
#include "HttpResponseHelper.h"

class HttpRequestParserPrivate;
class QUrl;

class HttpRequestParser : public QObject
{
	Q_OBJECT

public:
	HttpRequestParser(QObject *parent = 0);
	~HttpRequestParser();
	void parse(const QString &dataRaw);
	/*
	 @brief: 有效返回true
	*/
	bool isVaild()const;

	/*
	 @brief: 返回当前url
	*/
	const QUrl* getResource()const;

	/*
	 @brief: 返回解码后的请求串
	*/
	const QHash<QString, QString>& getResourceQueryItems()const;

	/*
	 @brief 返回引用url
	*/
	const QUrl* getReferer()const;

	/*
	 *  @brief 返回引用地址的请求串
	*/
	const QHash<QString, QString>& getRefererQueryItems()const;
protected:
	HttpRequestParserPrivate * const d_ptr;
	/*
	@brief 分析http头
	*/
	void parseHead(const QString &head);
	/*
	@brief 分析header
	*/
	void parseHeader(const QStringList &headerList);
private:
	/*
	@brief: 清空缓存，可以多次使用它
	*/
	void clear();

private:
	Q_DECLARE_PRIVATE(HttpRequestParser);
};

#endif // HTTPPARSER_H
