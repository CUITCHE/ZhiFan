#include "stdafx.h"
#include "HttpRequestParser.h"
struct HttpRequestParserPrivate
{
	bool vaild = true;
	QUrl *resourceUrl;
	QHash<QString, QString> *resourceEncodeQueryItems;
	QString *acceptType;
	QUrl *refererUrl;
	QHash<QString, QString> *refererEncodeQueryItems;
	HttpRequestParserPrivate()
		:resourceUrl(new QUrl)
		, resourceEncodeQueryItems(new  QHash<QString, QString>)
		, acceptType(new QString)
		, refererUrl(new QUrl)
		, refererEncodeQueryItems(new QHash<QString, QString>)
	{
	}
	void clear(){
		resourceUrl->clear();
		resourceEncodeQueryItems->clear();
		acceptType->clear();
		refererUrl->clear();
		refererEncodeQueryItems->clear();
		vaild = true;
	}
};
HttpRequestParser::HttpRequestParser(QObject *parent /*= 0*/) 
	: QObject(parent)
	, d_ptr(new HttpRequestParserPrivate)
{
}

HttpRequestParser::~HttpRequestParser()
{

}

bool HttpRequestParser::isVaild() const
{
	Q_D(const HttpRequestParser);
	return d->vaild && d->resourceUrl->isValid();
}

void HttpRequestParser::parse(const QString &raw)
{
	Q_D(HttpRequestParser);
	clear();
	d->vaild = (raw.startsWith("GET"));
	if (!d->vaild){
		return;
	}

	auto httpInfoList = raw.split("\r\n");
	parseHead(httpInfoList.takeFirst());
	parseHeader(httpInfoList);
}

void HttpRequestParser::clear()
{
	Q_D(HttpRequestParser);
	d->clear();
}

const QUrl* HttpRequestParser::getResource() const
{
	Q_D(const HttpRequestParser);
	return d->resourceUrl;
}

const QHash<QString, QString> &HttpRequestParser::getResourceQueryItems() const
{
	Q_D(const HttpRequestParser);
	return *d->resourceEncodeQueryItems;
}

void HttpRequestParser::parseHead(const QString &head)
{
	Q_D(HttpRequestParser);
	auto spiltString = head.split(' ');
	//获得路径信息
	QString tmpResourceAddr = spiltString.at(1);
	d->resourceUrl->setUrl(tmpResourceAddr);
	if (d->resourceUrl->isValid()){
		QString queryString = d->resourceUrl->query(QUrl::FullyDecoded);
		try{
			auto nodeParam = queryString.split('&');
			for (auto &val : nodeParam){
				QStringList tmp = val.split('=');
				if (tmp.size() == 2){
					d->resourceEncodeQueryItems->insert(tmp.at(0), tmp.at(1));
				}
			}
		}
		catch (...){
			d->vaild = false;
		}
	}
}

void HttpRequestParser::parseHeader(const QStringList &headerList)
{
	Q_D(HttpRequestParser);
	int ret = 1;
	for (auto &val : headerList){
		if (val.startsWith("Accept: ")){
			auto tmp = val.split(": ");
			try{
				*d->acceptType = tmp.at(1);
			}
			catch (...){
				d->vaild = false;
				return;
			}
			ret |= (1<<1);
		}
		else if (val.startsWith("Referer: ")){
			auto tmp = val.split(": ");
			try{
				d->refererUrl->setUrl(tmp.at(1));
			}
			catch (...){
				d->vaild = false;
			}
			ret |= (1<<2);
		}
		if (ret == 0x7){
			break;
		}
	}
	if (d->refererUrl->isValid()){
		QString queryString = d->refererUrl->query(QUrl::FullyDecoded);
		try{
			auto nodeParam = queryString.split('&');
			for (auto &val : nodeParam){
				QStringList tmp = val.split('=');
				if (tmp.size() == 2){
					d->refererEncodeQueryItems->insert(tmp.at(0), tmp.at(1));
				}
			}
		}
		catch (...){
			d->vaild = false;
		}
	}
}

const QUrl* HttpRequestParser::getReferer() const
{
	Q_D(const HttpRequestParser);
	return d->refererUrl;
}

const QHash<QString, QString>& HttpRequestParser::getRefererQueryItems() const
{
	Q_D(const HttpRequestParser);
	return *d->refererEncodeQueryItems;
}
