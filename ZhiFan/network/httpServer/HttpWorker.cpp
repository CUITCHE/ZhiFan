#include "stdafx.h"
#include "HttpWorker.h"
#include "HttpRequestParser.h"
#include "HttpResponseHelper.h"
#include "DBModule.h"

struct HttpWorkerPrivate
{
	HttpRequestParser *parser = 0;
	HttpResponseHelper *response;
	HttpWorkerPrivate(QObject *parent = 0)
		:response(new HttpResponseHelper(parent))
	{}
	static QHash<QString, QString> s_contentTypes;
};
#define CONTENT_TYPE(fileSufix, contentType) {fileSufix, contentType}
QHash<QString, QString> HttpWorkerPrivate::s_contentTypes = {
	CONTENT_TYPE("", "text/plain"),
	CONTENT_TYPE("txt", "text/plain"),
	CONTENT_TYPE("html", "text/html; charset=utf-8"),
	CONTENT_TYPE("htm", "text/html; charset=utf-8"),
	CONTENT_TYPE("css", "text/css; charset=utf-8"),
	CONTENT_TYPE("js", "application/x-javascript; charset=utf-8"),
	CONTENT_TYPE("xml", "text/xml"),
	CONTENT_TYPE("xsl", "text/xml"),
	CONTENT_TYPE("jpg", "image/jpeg"),
	CONTENT_TYPE("png", "image/png"),
	CONTENT_TYPE("jpeg", "image/jpeg"),
	CONTENT_TYPE("bmp", "image/bmp"),
	CONTENT_TYPE("gif", "image/gif"),
	CONTENT_TYPE("tiff", "image/tiff"),
	CONTENT_TYPE("zip", "application/zip"),
	CONTENT_TYPE("pdf", "application/pdf"),
	CONTENT_TYPE("doc", "application/msword"),
	CONTENT_TYPE("xls", "application/vnd.ms-excel"),
	CONTENT_TYPE("ppt", "application/vnd.ms-powerpoint"),
	CONTENT_TYPE("swf", "application/x-shockwave-flash"),
	CONTENT_TYPE("wav", "audio/x-wav"),
	CONTENT_TYPE("avi", "video/x-msvideo"),
	CONTENT_TYPE("json", "application/json;charset=UTF-8")
};
#undef CONTENT_TYPE
HttpWorker::HttpWorker(QObject *parent)
	: QObject(parent)
	, d_ptr(new HttpWorkerPrivate(this))
{

}

HttpWorker::~HttpWorker()
{

}

void HttpWorker::setObject(QObject *object)
{
	Q_D(HttpWorker);
	d->parser = dynamic_cast<HttpRequestParser*>(object);
}

void HttpWorker::getResponseString(QByteArray &out)
{
	Q_D(HttpWorker);
	if (!d->parser){
		return;
	}
	d->response->clear();

	dispatch();
	out = d->response->generateHttpText();
}

void HttpWorker::dispatch()
{
	using WorkerType = decltype(&HttpWorker::accountMananger);

	static QHash<QString, WorkerType> s_htmlfragment = {
		{ "/account-manager", &HttpWorker::accountMananger }, 
		{ "/info-center", &HttpWorker::noticeCenter },
		{ "/published", &HttpWorker::myPublished },
		{ "/joined", &HttpWorker::myJoined },
		{ "/user-center.html", &HttpWorker::userCenter}
	};

	Q_D(HttpWorker);

	QString path = d->parser->getResource()->path();
	auto url = d->parser->getReferer();
	//做帐号验证
	QString userid;
	QString token;
	const QHash<QString,QString> *data;
	if (url->isValid()){
		//此时的查询串在referer中
		data = &d->parser->getRefererQueryItems();
		userid = data->value("userid", "");
		token = data->value("token", "");
		if (this->accountVerification(userid, token) == false){
			write403();
			return;
		}
	}
	else{
		data = &d->parser->getResourceQueryItems();
		userid = data->value("userid", "");
		token = data->value("token", "");
		if (this->accountVerification(userid, token) == false){
			write403();
			return;
		}
	}
	auto iter = s_htmlfragment.find(path);
	if (iter != s_htmlfragment.end()){
		auto func = iter.value();
		if (func){
			(this->*func)();
		}
	}
	else{
		//发送资源文件
		writeFile(path);
	}
}

void HttpWorker::userCenter()
{
	Q_D(HttpWorker);
	QFile file("." + d->parser->getResource()->path());
	if (file.open(QIODevice::ReadOnly)){
		d->response->setBody(file.readAll());
		QFileInfo info(file.fileName());
		d->response->setHeader(ContentType, d->s_contentTypes.value(info.suffix()));
		d->response->setHead(200);
	}
	else{
		write404();
	}
}

void HttpWorker::accountMananger()
{
	Q_D(HttpWorker);
	d->response->setHead(200);
	d->response->setHeader(ContentType, d->s_contentTypes.value("json"));
	QVariantMap dataMap;
	dataMap.insert("username", "文杨");
	dataMap.insert("gender", true);
	dataMap.insert("status", false);
	dataMap.insert("gold", 2048);
	dataMap.insert("mobile", "133***");
	dataMap.insert("success", true);
	auto data = QJsonDocument::fromVariant(dataMap).toJson();
	d->response->setBody(data);
}

void HttpWorker::noticeCenter()
{
	Q_D(HttpWorker);
	d->response->setHead(200);
	d->response->setHeader(ContentType, d->s_contentTypes.value("json"));
	auto ins = getInstance(DBModule);
	QByteArray out;
	ins->HttpUserNoticeCenter(1, "", 11, out);
	d->response->setBody(out);
}

void HttpWorker::myPublished()
{

}

void HttpWorker::myJoined()
{

}

bool HttpWorker::accountVerification(const QString &userid, const QString &token)
{
	return true;
}

void HttpWorker::write403()
{
	Q_D(HttpWorker);
	d->response->setHead(403);
	d->response->setHeader(ContentType, d->s_contentTypes.value("html"));
	d->response->setBody("<h1>403 Forbidden</h1>");
}

void HttpWorker::write404()
{
	Q_D(HttpWorker);
	d->response->setHead(404);
	d->response->setHeader(ContentType, d->s_contentTypes.value("html"));
	d->response->setBody("<h1>404 Not Found</h1>");
}

void HttpWorker::writeFile(const QString &path)
{
	Q_D(HttpWorker);
	QFile file("." + path);
	if (file.open(QIODevice::ReadOnly)){
		QFileInfo info(file.fileName());
		d->response->setHead(200);
		auto context = d->s_contentTypes.value(info.suffix(),"*/*");
		d->response->setHeader(ContentType, context);
		QByteArray data = file.readAll();
		d->response->setBody(data);
	}
	else{
		write404();
	}
}
