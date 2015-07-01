#ifndef HTTPPARSER_H
#define HTTPPARSER_H
/*!
 * \file HttpRequestParser.h
 *
 * \author CHE
 * \date ���� 2015
 *
 * ����HTTP�����ַ���
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
	 @brief: ��Ч����true
	*/
	bool isVaild()const;

	/*
	 @brief: ���ص�ǰurl
	*/
	const QUrl* getResource()const;

	/*
	 @brief: ���ؽ���������
	*/
	const QHash<QString, QString>& getResourceQueryItems()const;

	/*
	 @brief ��������url
	*/
	const QUrl* getReferer()const;

	/*
	 *  @brief �������õ�ַ������
	*/
	const QHash<QString, QString>& getRefererQueryItems()const;
protected:
	HttpRequestParserPrivate * const d_ptr;
	/*
	@brief ����httpͷ
	*/
	void parseHead(const QString &head);
	/*
	@brief ����header
	*/
	void parseHeader(const QStringList &headerList);
private:
	/*
	@brief: ��ջ��棬���Զ��ʹ����
	*/
	void clear();

private:
	Q_DECLARE_PRIVATE(HttpRequestParser);
};

#endif // HTTPPARSER_H
