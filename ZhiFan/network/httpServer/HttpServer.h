#ifndef HTTPSERVER_H
#define HTTPSERVER_H
/*!
 * \file HttpServer.h
 *
 * \author CHE
 * \date ÁùÔÂ 2015
 *
 * http ·þÎñ¶Ë
 */
#include <QObject>
#include <QHostAddress>
class HttpServerPrivate;
class HttpRequestParser;
class QTcpSocket;

class HttpServer : public QObject
{
	Q_OBJECT

public:
	HttpServer(QObject *parent = 0);
	~HttpServer();
	bool listen(const QHostAddress &address = QHostAddress::Any, quint16 post = 80);
protected:
	HttpServerPrivate * const d_ptr;

private slots:
	void acceptConnection();
	void onReadyRead();
	void displayError(QAbstractSocket::SocketError);
private:
	Q_DECLARE_PRIVATE(HttpServer);
};

#endif // HTTPSERVER_H
