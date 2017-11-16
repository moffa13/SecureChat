#include "SSLServer.h"
#include <QSslSocket>

SSLServer::SSLServer(){

}

SSLServer::SSLServer(const QSslCertificate &serverCertificate, const QSslKey &privateKey) :
	_serverCertificate(serverCertificate),
	_privateKey(privateKey)
{}

void SSLServer::setPrivateKey(QSslKey const& privateKey){
	_privateKey = privateKey;
}

void SSLServer::setServerCertificate(QSslCertificate const& serverCertificate){
	_serverCertificate = serverCertificate;
}

QSslSocket *SSLServer::nextPendingConnection()
{
	return static_cast<QSslSocket *>(QTcpServer::nextPendingConnection());
}

void SSLServer::incomingConnection(qintptr socketDescriptor){
	qDebug() << "new client";
	QSslSocket* socket = new QSslSocket{this};
	connect(socket, static_cast<void (QSslSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), [socket](QAbstractSocket::SocketError error){
		qDebug() << error << socket->error() << socket->errorString();
	});

	connect(socket, &QSslSocket::peerVerifyError, [](const QSslError & error){
		qDebug() << "Cannot verify server identity " << error;
	});

	connect(socket, static_cast<void(QSslSocket::*)(const QList<QSslError> &errors)>(&QSslSocket::sslErrors), [](const QList<QSslError> &errors){
		QSslError const& first = errors.first();
		qDebug() << "onSslErrors: " << first.errorString() << endl;
	});

	connect(socket, &QSslSocket::stateChanged, [](QAbstractSocket::SocketState state){
		qDebug() << state;
	});

	connect(socket, &QSslSocket::encrypted, [](){
		qDebug() << "Connection encrypted";
	});
	if(socket->setSocketDescriptor(socketDescriptor)){
		addPendingConnection(socket);
		if(!_privateKey.isNull())
			socket->setPrivateKey(_privateKey);
		if(!_serverCertificate.isNull())
			socket->setLocalCertificate(_serverCertificate);
		socket->setProtocol(QSsl::SslV3);
		socket->setPeerVerifyMode(QSslSocket::VerifyNone);
		socket->startServerEncryption();
	}else{
		delete socket;
	}
}
