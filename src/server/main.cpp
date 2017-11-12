#include "SSLServer.h"
#include <QCoreApplication>
#include <QSslSocket>


int main(int argc, char* argv[]){

	QCoreApplication app{argc, argv};

	qDebug() << "Using openssl " << QSslSocket::sslLibraryBuildVersionString();

	SSLServer serv;
	serv.listen(QHostAddress::Any, 8888);

	return app.exec();
}
