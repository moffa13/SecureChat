#include "SSLServer.h"

#include <QSslSocket>

SSLServer::SSLServer(){

}

void SSLServer::incomingConnection(qintptr socketDescriptor){
	qDebug() << "new client";
	QSslSocket* socket = new QSslSocket{this};
	if(socket->setSocketDescriptor(socketDescriptor)){
		addPendingConnection(socket);
		socket->startServerEncryption();
	}else{
		delete socket;
	}
}
