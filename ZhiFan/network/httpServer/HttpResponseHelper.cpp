#include "stdafx.h"
#include "HttpResponseHelper.h"

struct HttpResponseHelperPrivate
{
	static QHash<int, QString> status_reason_hash;
	QString *httpVersion = 0;	//默认是HTTP/1.1，故此指针默认为0
	QByteArray *head;
	QHash<QString, QString> *headers;
	QByteArray *body;
	HttpResponseHelperPrivate()
		:head(new QByteArray)
		,headers(new QHash<QString,QString>)
		, body(new QByteArray)
	{
	}
	void clear()
	{
		body->clear();
		head->clear();
		headers->clear();
	}
};
const char *DefaultHttpVersion = "HTTP/1.1";
#pragma region status

#define STATUS_CODE(num, reason) {num,reason}

QHash<int, QString> HttpResponseHelperPrivate::status_reason_hash = {
STATUS_CODE(100, "Continue"),
STATUS_CODE(101, "Switching Protocols"),
STATUS_CODE(102, "Processing"),			// RFC 2518) obsoleted by RFC 4918
STATUS_CODE(200, "OK"),
STATUS_CODE(201, "Created"),
STATUS_CODE(202, "Accepted"),
STATUS_CODE(203, "Non-Authoritative Information"),
STATUS_CODE(204, "No Content"),
STATUS_CODE(205, "Reset Content"),
STATUS_CODE(206, "Partial Content"),
STATUS_CODE(207, "Multi-Status"),		// RFC 4918
STATUS_CODE(300, "Multiple Choices"),
STATUS_CODE(301, "Moved Permanently"),
STATUS_CODE(302, "Moved Temporarily"),
STATUS_CODE(303, "See Other"),
STATUS_CODE(304, "Not Modified"),
STATUS_CODE(305, "Use Proxy"),
STATUS_CODE(307, "Temporary Redirect"),
STATUS_CODE(400, "Bad Request"),
STATUS_CODE(401, "Unauthorized"),
STATUS_CODE(402, "Payment Required"),
STATUS_CODE(403, "Forbidden"),
STATUS_CODE(404, "Not Found"),
STATUS_CODE(405, "Method Not Allowed"),
STATUS_CODE(406, "Not Acceptable"),
STATUS_CODE(407, "Proxy Authentication Required"),
STATUS_CODE(408, "Request Time-out"),
STATUS_CODE(409, "Conflict"),
STATUS_CODE(410, "Gone"),
STATUS_CODE(411, "Length Required"),
STATUS_CODE(412, "Precondition Failed"),
STATUS_CODE(413, "Request Entity Too Large"),
STATUS_CODE(414, "Request-URI Too Large"),
STATUS_CODE(415, "Unsupported Media Type"),
STATUS_CODE(416, "Requested Range Not Satisfiable"),
STATUS_CODE(417, "Expectation Failed"),
STATUS_CODE(418, "I\"m a teapot"),			// RFC 2324
STATUS_CODE(422, "Unprocessable Entity"),	// RFC 4918
STATUS_CODE(423, "Locked"),					// RFC 4918
STATUS_CODE(424, "Failed Dependency"),		// RFC 4918
STATUS_CODE(425, "Unordered Collection"),	// RFC 4918
STATUS_CODE(426, "Upgrade Required"),		// RFC 2817
STATUS_CODE(500, "Internal Server Error"),
STATUS_CODE(501, "Not Implemented"),
STATUS_CODE(502, "Bad Gateway"),
STATUS_CODE(503, "Service Unavailable"),
STATUS_CODE(504, "Gateway Time-out"),
STATUS_CODE(505, "HTTP Version not supported"),
STATUS_CODE(506, "Variant Also Negotiates"),	// RFC 2295
STATUS_CODE(507, "Insufficient Storage"),		// RFC 4918
STATUS_CODE(509, "Bandwidth Limit Exceeded"),
STATUS_CODE(510, "Not Extended"),				// RFC 2774
};
#undef STATUS_CODE
#pragma endregion status
HttpResponseHelper::HttpResponseHelper(QObject *parent)
	: QObject(parent)
	,d_ptr(new HttpResponseHelperPrivate)
{

}

HttpResponseHelper::~HttpResponseHelper()
{

}

QByteArray HttpResponseHelper::generateHttpText()const
{
	Q_D(const HttpResponseHelper);
	QByteArray text = *d->head;
	text.append("\n");
	(*d->headers)[headerconvert(Date)] = getDateForFormate();
	(*d->headers)[headerconvert(CacheControl)] = "no-cache";
	auto keys = d->headers->keys();
	for (auto &val : keys) {
		if (val.isEmpty()){
			continue;
		}
		text.append(val).append(": ").append(d->headers->value(val)).append("\n");
	}
	text.append("\n");
	text.append(*d->body);
	return text;
}

const QString& HttpResponseHelper::headerconvert(KnownHeader header)
{
	static const QString headerTranslate[] = { "Cache-Control", "Content-Encoding", "Content-Language", "Content-Length",
		"Content-Type", "Date", "Location", "Host", "Connection", "Accept", "User-Agent", "Referer", 
		"Accept-Encoding", "Accept-Language" };
	
	return headerTranslate[header];
}

void HttpResponseHelper::setHttpVersion(const QString &version)
{
	Q_D(HttpResponseHelper);
	if (d->httpVersion == 0){
		d->httpVersion = new QString(version);
	}
	else{
		*d->httpVersion = version;
	}
}

void HttpResponseHelper::clear()
{
	Q_D(HttpResponseHelper);
	d->clear();
}

void HttpResponseHelper::setHeader(KnownHeader header, const QString &value)
{
	Q_D(HttpResponseHelper);
	(*d->headers)[headerconvert(header)] = value;
}

void HttpResponseHelper::setHead(int status)
{
	Q_D(HttpResponseHelper);
	d->head->append(d->httpVersion ? *d->httpVersion : DefaultHttpVersion).append(" ")
		.append(QByteArray::number(status)).append(" ").append(d->status_reason_hash.value(status, "No Content"));
}

void HttpResponseHelper::setBody(const QByteArray &body)
{
	Q_D(HttpResponseHelper);
	*d->body = body;
}

QString HttpResponseHelper::getDateForFormate()const
{
	QString strFormat = "ddd, dd MMM yyyy hh:mm:ss G'M'T";
	QLocale loc = QLocale(QLocale::English, QLocale::UnitedStates);
	QDateTime curTime = QDateTime::currentDateTimeUtc();
	strFormat = loc.toString(curTime, strFormat);
	return strFormat;
}
