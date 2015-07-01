#include "stdafx.h"
#include "HttpServer.h"
#include "HttpRequestParser.h"
#include "HttpWorker.h"
#include <QTcpServer>
#include <QTcpSocket>


using HttpRequestDataType = QPair < QTcpSocket*, QString >;

struct HttpServerPrivate
{
	HttpServerPrivate(QObject *parent = 0)
		:tcpServer(new QTcpServer(parent))
		//, mutex(new QMutex)
		, requestQueue(new QList < HttpRequestDataType >)
		, worker(new HttpWorker(parent))
		, parser(new HttpRequestParser(parent))
	{}
	QTcpServer *tcpServer;
	//QMutex *mutex;
	QList<HttpRequestDataType> *requestQueue;
	HttpWorker *worker;
	HttpRequestParser *parser;
};

HttpServer::HttpServer(QObject *parent)
	: QObject(parent)
	, d_ptr(new HttpServerPrivate(this))
{
}

HttpServer::~HttpServer()
{

}


bool HttpServer::listen(const QHostAddress &address /*= QHostAddress::Any*/, quint16 post /*= 8080*/)
{
	Q_D(HttpServer);
	connect(d->tcpServer, &QTcpServer::newConnection, this, &HttpServer::acceptConnection);
	return d->tcpServer->listen(address, post);
}

void HttpServer::acceptConnection()
{
	Q_D(HttpServer);
	QTcpSocket *serverConnect = d->tcpServer->nextPendingConnection();
	connect(serverConnect, &QTcpSocket::readyRead, this, &HttpServer::onReadyRead);
	connect(serverConnect, static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &HttpServer::displayError);
}

void HttpServer::onReadyRead()
{
	QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());
	if (!socket){
		return;
	}
	Q_D(HttpServer);
	QByteArray dataRaw = socket->readAll();
	qDebug() << dataRaw;
	
	d->parser->parse(dataRaw);
	if (d->parser->isVaild()){
		d->worker->setObject(d->parser);
		QByteArray out;
		d->worker->getResponseString(out);
		socket->write(out);
		//qDebug() << "Response: \n" << out;
	}
	else{
		//无效的http请求字符串
		socket->write("HTTP/1.1 403 Forbidden");
	}
	socket->close();
	socket->deleteLater();
}

void HttpServer::displayError(QAbstractSocket::SocketError)
{

}